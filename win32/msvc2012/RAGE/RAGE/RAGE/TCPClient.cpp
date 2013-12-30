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

#include "TCPClient.h"

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_TCP_CLIENT

namespace RAGE
{
	namespace Network
	{
		TCPClient::TCPClient(void)
		{
			#ifdef WIN32
			WSAData w_data;
			if (WSAStartup(MAKEWORD(2,0), &w_data) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_WSA_INIT);
				return;
			}
			#endif

			memset(&timeout, 0, sizeof(timeout));

			blocking_mode = 0;

			disposed = false;
			connected = false;
		}

		void TCPClient::tcp_connect(char *host, int prt)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (connected)
				disconnect();

			addrinfo *servinfo, hints;

			memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_flags = AI_PASSIVE;

			port = prt;

			char c_port[12] = {0};

			#ifdef WIN32
			sprintf_s(c_port, 12, "%d", prt);
			#else
			sprintf(c_port, "%d", prt);
			#endif

			if (getaddrinfo(host, c_port, &hints, &servinfo) != 0)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RESOLVE_HOST);
				connected = false;
				return;
			}

			sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

			if (sock == INVALID_SOCKET)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CREATE);
				connected = false;
				return;
			}

			if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CONNECT_HOST);
				connected = false;
				return;
			}

			connected = true;
		}

		int TCPClient::tcp_send(char *data, int len)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return send(sock, data, len, 0);
		}

		SOCKET TCPClient::get_id(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return sock;
		}

		VALUE TCPClient::tcp_recv(int max_buffer)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			char *buffer = NULL;
			VALUE ret_str;
			int result = 0;

			if (max_buffer == 0)
			{
				buffer = new char[RAGE_CLIENT_TCP_MAX_BUFFER];
				char *data = NULL;
				size_t max_len = 0, i, pos = 0;

				do 
				{
					memset(buffer, 0, RAGE_CLIENT_TCP_MAX_BUFFER);
					result = recv(sock, buffer, RAGE_CLIENT_TCP_MAX_BUFFER, 0);

					if (result > 0)
					{
						data = (char*)al_realloc(data, max_len + result);

						for (i = 0; i < result; i++)
							data[pos++] = buffer[i];

						max_len += result;
					}
					else if (result == 0)
					{
						disconnect();
					}


				} while(result > 0);

				ret_str = rb_str_new(data, max_len);

				if (data != NULL)
					al_free(data);

			}
			else
			{
				buffer = new char[max_buffer];
				memset(buffer, 0, max_buffer);

				result = recv(sock, buffer, max_buffer, 0);

				if (result > 0)
				{
					ret_str = rb_str_new(buffer, result);
				}
				else
					ret_str = Qnil;

				
			}

			return ret_str;
		}

		void TCPClient::set_blocking_mode(bool blocking)
		{
			RAGE_CHECK_DISPOSED(disposed);

			blocking_mode = blocking ? 0 : 1;

			#ifdef WIN32
			if (ioctlsocket(sock, FIONBIO, &blocking_mode) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_BLOCK_MODE);
				return;
			}
			#else
			if (fcntl(sock, F_SETFL, blocking_mode) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_BLOCK_MODE);
				return INVALID_SOCKET;
			}
			#endif
			
		}

		bool TCPClient::get_blocking_mode(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (blocking_mode == 1)
				return false;
			else
				return true;
		}

		int TCPClient::get_timeout(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return timeout.tv_sec;
		}

		void TCPClient::set_timeout(int seconds)
		{
			RAGE_CHECK_DISPOSED(disposed);

			timeout.tv_sec = seconds;
			
			#ifdef WIN32
			int miliseconds = seconds * 1000;
			if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&miliseconds, sizeof(miliseconds)))
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_TIMEOUT_CANNOT_SET);
				return;
			}
			#else
			if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (timeval*)&timeout, sizeof(timeout)))
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_TIMEOUT_CANNOT_SET);
				return;
			}
			#endif

		}

		bool TCPClient::get_connected(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return connected;
		}

		void TCPClient::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (connected)
				disconnect();

			#ifdef WIN32
			if (!WSACleanup())
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_WSA_CLEANUP);
				return;
			}
			#endif

			disposed = true;
		}

		int TCPClient::get_port(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return port;
		}

		bool TCPClient::get_data_available(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			char t = 0;

			int result = recv(sock, &t, 1, MSG_PEEK);

			if (result == 0)
				disconnect();

			return (result > 0);
		}

		void TCPClient::disconnect(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			closesocket(sock);

			connected = false;
		}

		TCPClient::~TCPClient(void)
		{
			if (!disposed)
				dispose();
		}

	}
}

#endif