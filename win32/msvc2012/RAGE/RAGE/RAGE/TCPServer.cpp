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

#include "TCPServer.h"

namespace RAGE
{
	namespace Network
	{
		TCPServer::TCPServer(void)
		{
			#ifdef WIN32
			WSAData w_data;
			if (WSAStartup(MAKEWORD(2,0), &w_data) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_WSA_INIT);
				return;
			}
			#endif

			blocking_default = 0;
			max_clients = 10;

			serv_info = NULL;

			connected = false;

			disposed = false;
		}

		void TCPServer::initialize(int port, bool blocking_mode, int max_connections)
		{
			sockaddr_in service;

			max_clients = max_connections;
			
			blocking_default = blocking_mode ? 0 : O_NONBLOCK;

			serv_port = port;

			memset(&service, 0, sizeof(service));
			service.sin_family = AF_INET;
			service.sin_addr.s_addr = htonl(INADDR_ANY);
			service.sin_port = htons(serv_port);
			
			#ifdef WIN32
			char opt = '1';
			int len = sizeof(char);
			#else
			int opt = 1;
			int len = sizeof(int);
			#endif

			if ((server_sock = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CREATE);
				return;
			}

			if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, len) == SOCKET_ERROR) 
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CONFIG);
				return;
			}

			#ifdef WIN32
			u_long mode = blocking_default;
			if (ioctlsocket(server_sock, FIONBIO, &mode) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_BLOCK_MODE);
				return;
			}
			#else
			if (fcntl(server_sock, F_SETFL, blocking_default) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_BLOCK_MODE);
				return;
			}
			#endif

			if (bind(server_sock, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) 
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_BIND_ERROR);
				return;
			}

			if (listen(server_sock, max_connections) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_BIND_ERROR);
				return;
			}

			connected = true;
		}
		

		SOCKET TCPServer::get_id(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, INVALID_SOCKET);

			return server_sock;
		}

		char* TCPServer::get_client_ip(SOCKET client_sock, int ip_type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			sockaddr name;
			socklen_t namelen = sizeof(name);

			char *str = new char[INET6_ADDRSTRLEN];
			memset(str, 0, INET6_ADDRSTRLEN);
			

			if (getpeername(client_sock, (sockaddr*)&name, &namelen) == SOCKET_ERROR)
			{
				return NULL;
			}
			else
			{
				inet_ntop(ip_type, &name.sa_data, str, INET6_ADDRSTRLEN);
				return str;
			}
		}

		SOCKET TCPServer::listen_clients(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, INVALID_SOCKET);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return INVALID_SOCKET;
			}
			

			SOCKET sc = accept(server_sock, NULL, NULL);

			if (sc != INVALID_SOCKET)
			{
				#ifdef WIN32
				u_long mode = blocking_default;
				if (ioctlsocket(sc, FIONBIO, &mode) == SOCKET_ERROR)
				{
					rb_raise(rb_eException, RAGE_ERROR_SOCKET_BLOCK_MODE);
					return INVALID_SOCKET;
				}
				#else
				if (fcntl(sc, F_SETFL, blocking_default) == SOCKET_ERROR)
				{
					rb_raise(rb_eException, RAGE_ERROR_SOCKET_BLOCK_MODE);
					return INVALID_SOCKET;
				}
				#endif
			}

			return sc;
		}

		int TCPServer::send_data(SOCKET client_sock, char *data, int size)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return 0;
			}

			return send(client_sock, data, size, 0);
		}

		bool TCPServer::get_is_data_available(SOCKET client_sock)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return false;
			}

			char t = 0;

			int result = recv(client_sock, &t, 1, MSG_PEEK);

			return (result > 0);
		}

		VALUE TCPServer::receive_data(SOCKET client_sock, int max_buffer)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return Qnil;
			}


			char *buffer = NULL;
			VALUE ret_str;
			int result = 0;

			if (max_buffer == 0)
			{
				buffer = new char[RAGE_SERVER_TCP_MAX_BUFFER];
				char *data = NULL;
				size_t max_len = 0, i, pos = 0;

				do 
				{
					memset(buffer, 0, RAGE_SERVER_TCP_MAX_BUFFER);
					result = recv(client_sock, buffer, RAGE_SERVER_TCP_MAX_BUFFER, 0);

					if (result > 0)
					{
						data = (char*)al_realloc(data, max_len + result);

						for (i = 0; i < result; i++)
							data[pos++] = buffer[i];

						max_len += result;
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

				result = recv(client_sock, buffer, max_buffer, 0);

				if (result > 0)
				{
					ret_str = rb_str_new(buffer, result);
				}
				else
					ret_str = Qnil;

				
			}

			return ret_str;
		}

		bool TCPServer::get_is_connected(SOCKET client_sock)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return false;
			}

			char test_data[RAGE_SERVER_TCP_MAX_BUFFER];

			return recv(client_sock, test_data, RAGE_SERVER_TCP_MAX_BUFFER, MSG_PEEK);
		}

		int TCPServer::get_server_port(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return 0;
			}

			return serv_port;
		}

		bool TCPServer::get_is_blocking(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return false;
			}

			return (blocking_default == 0) ? true : false;
		}

		int TCPServer::get_max_clients(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_NOT_CONNECTED);
				return 0;
			}

			return max_clients;
		}

		void TCPServer::disconnect(SOCKET client_sock)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (client_sock == server_sock)
			{
				rb_raise(rb_eException, RAGE_ERROR_SERVER_CANNOT_DISCONNECT_SELF);
				return;
			}

			shutdown(client_sock, SD_BOTH);
			closesocket(client_sock);
		}

		void TCPServer::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (connected)
			{
				if (shutdown(server_sock, SD_BOTH) == SOCKET_ERROR)
				{
					rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CLOSE_SERVER);
					return;
				}

				if (close(server_sock) == SOCKET_ERROR)
				{
					rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CLOSE_SERVER);
					return;
				}
			}

			#ifdef WIN32
			if (!WSACleanup())
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_WSA_CLEANUP);
				return;
			}
			#endif

			disposed = true;
		}

		TCPServer::~TCPServer(void)
		{
			if (!disposed)
				dispose();
		}

	}
}