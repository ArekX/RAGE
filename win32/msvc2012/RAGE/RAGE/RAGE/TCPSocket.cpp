/*
Copyright (c) 2013 Aleksandar Panic

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#include "TCPSocket.h"


namespace RAGE
{
	namespace Network
	{
		TCPSocket::TCPSocket(void)
		{
			#ifdef WIN32

			int err = WSAStartup(MAKEWORD(2, 1), &wsaData);

			if (err != 0)
			{
				rb_raise(rb_eException, "Socket Error: WSA Initialization failed. Error Code: %d", err);
				return;
			}

			#endif

			main_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (main_sock == INVALID_SOCKET)
			{
				rb_raise(rb_eException, "Socket Error: Socket initialization failed. Erroc Code: %d", WSAGetLastError());
				return;
			}

			connected = false;
			disposed = false;

			blocking_mode = 0;
			
			timeout.tv_sec = 0;
			timeout.tv_usec = 0;

			ip_address_type = AF_INET;
		}

		void TCPSocket::tcp_create(u_short port)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (connected)
				tcp_shutdown(SD_BOTH);

			connection.sin_family = AF_INET;
			connection.sin_addr.s_addr = htonl(INADDR_ANY);
			connection.sin_port = htons(port);
			
			if (bind(main_sock, (SOCKADDR*)&connection, sizeof(connection)) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, "Socket Error: Socket server initialization failed. Erroc Code: %d", WSAGetLastError());
				return;
			}

			if (listen(main_sock, SOMAXCONN) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, "Socket Error: Socket listen failed. Erroc Code: %d", WSAGetLastError());
				return;
			}

			is_server = true;
			connected = true; 
			working_sock = INVALID_SOCKET;

			tcp_set_blocking(true);
		}

		void TCPSocket::tcp_connect(char *ip, u_short port)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (connected)
				tcp_shutdown(SD_BOTH);

			struct hostent *hst;

			if ((hst = gethostbyname(ip)) == NULL)
			{
				rb_raise(rb_eException, "Socket Error: Cannot resolve host name.");
				return;
			}

			connection.sin_family = ip_address_type;
			connection.sin_addr.s_addr = *((unsigned long*)hst->h_addr);
			connection.sin_port = htons(port);

			int result = connect(main_sock, (SOCKADDR*)&connection, sizeof(connection));
			if (result == SOCKET_ERROR)
			{
				rb_raise(rb_eException, "Socket Error: Socket connection failed. Error Code: %d", WSAGetLastError());
				return;
			}

			connected = true;
			working_sock = main_sock;
			is_server = false;
		}

		int TCPSocket::tcp_send(char* data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (!connected)
			{
				rb_raise(rb_eException, "Socket Error: Socket data sending failed. Not connected to any host.");
				return 0;
			}

			int sent = send(working_sock, data, (int)strlen(data), 0);

			if (sent == SOCKET_ERROR)
			{
				rb_raise(rb_eException, "Socket Error: Socket data sending failed. Error Code: %d", WSAGetLastError());
				return 0;
			}

			return sent;
		}

		char* TCPSocket::tcp_receive_all(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			if (!connected)
			{
				rb_raise(rb_eException, "Socket Error: Cannot receive data. Not connected to any host.");
				return NULL;
			}

			char buffer[TCP_SOCKET_MAX_BUFFER] = {0};
			char *end_string = (char*)al_malloc(sizeof(char));
			int result = 0;
			int add_iterator = 0;
			int new_count = 1;

			end_string[0] = 0;

			do
			{
				result = recv(working_sock, buffer, TCP_SOCKET_MAX_BUFFER, 0);

				if ((new_count + result) > new_count)
				{
					new_count += result;
					end_string = (char*)al_realloc(end_string, sizeof(char) * new_count);
				}

				for (int i = 0; i < result; i++)
					end_string[add_iterator++] = buffer[i];

			} while(result > 0);

			end_string[add_iterator] = 0;

			return end_string;
		}

		char* TCPSocket::tcp_receive(int buffer_size)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			

			if (!connected)
			{
				rb_raise(rb_eException, "Socket Error: Cannot receive data. Not connected to any host.");
				return NULL;
			}

			if (buffer_size == 0)
				buffer_size = TCP_SOCKET_MAX_BUFFER;

			char *buffer = new char[buffer_size + 1];

			memset(buffer, 0, buffer_size);

			recv(working_sock, buffer, buffer_size, 0);

			return buffer;
		}

		void TCPSocket::tcp_set_blocking(bool blocking)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (blocking)
				blocking_mode = 1;
			else
				blocking_mode = 0;

			ioctlsocket(main_sock, FIONBIO, &blocking_mode);
		}

		bool TCPSocket::tcp_get_blocking(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return (blocking_mode == 1);
		}

		void TCPSocket::tcp_set_timeout(int seconds)
		{
			RAGE_CHECK_DISPOSED(disposed);

			timeout.tv_sec = seconds;

			if (setsockopt(main_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)))
			{
				rb_raise(rb_eException, "Socket Error: Cannot set timeout.");
				return;
			}
		}

		int TCPSocket::tcp_get_timeout(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return timeout.tv_sec;
		}

			
		int TCPSocket::tcp_get_ip_type(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return ip_address_type;
		}

		void TCPSocket::tcp_set_ip_type(int new_type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			ip_address_type = new_type;
		}

		void TCPSocket::tcp_shutdown(int what)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (!connected)
			{
				rb_raise(rb_eException, "Socket Error: Cannot disconnect. Not connected to any host.");
				return;
			}

			if (shutdown(main_sock, what) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, "Socket Error: Disconnect failed. Error Code: %d", WSAGetLastError());
				return;
			}
		}

		void TCPSocket::tcp_accept(void)
		{
			int addr_len = sizeof(accept_connection);

			working_sock = accept(working_sock, (SOCKADDR*)&accept_connection, &addr_len);
		}

		bool TCPSocket::get_connected(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return connected;
		}

		void TCPSocket::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (closesocket(working_sock) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, "Socket Error: Socket close failed. Error Code: %d", WSAGetLastError());
				return;
			}

			WSACleanup();
		}

		TCPSocket::~TCPSocket(void)
		{
			if (!disposed)
				dispose();
		}
	}
}
