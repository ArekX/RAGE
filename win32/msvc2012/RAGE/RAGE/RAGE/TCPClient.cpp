#include "TCPClient.h"

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

			blocking_mode = 0;

			disposed = false;
			connected = false;
		}

		void TCPClient::tcp_connect(char *host, char *port)
		{
			RAGE_CHECK_DISPOSED(disposed);

			addrinfo *servinfo, hints;

			memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_flags = AI_PASSIVE;

			if (getaddrinfo(host, port, &hints, &servinfo) != 0)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RESOLVE_HOST);
				return;
			}

			sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

			if (sock == INVALID_SOCKET)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CREATE);
				return;
			}

			if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CONNECT_HOST);
				return;
			}

			connected = true;
			
		}

		int TCPClient::tcp_send(char *data, int len)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_CLIENT_NOT_CONNECTED);
				return 0;
			}

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

			if (!connected)
			{
				rb_raise(rb_eException, RAGE_ERROR_CLIENT_NOT_CONNECTED);
				return Qnil;
			}

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
						connected = false;
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

		void TCPClient::disconnect(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			shutdown(sock, SD_BOTH);
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