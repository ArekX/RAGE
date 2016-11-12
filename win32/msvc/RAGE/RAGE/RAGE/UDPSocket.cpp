/*
Copyright (c) 2014 Aleksandar Panic

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

#include "UDPSocket.h"

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_UDP_SOCKET

namespace RAGE
{
	namespace Network
	{
		UDPSocket::UDPSocket(void)
		{
			#ifdef WIN32
			WSAData w_data;
			if (WSAStartup(MAKEWORD(2,0), &w_data) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_WSA_INIT);
				return;
			}
			#endif

			serv_port = 0;
			disposed = false;
		}

		void UDPSocket::initialize(int port)
		{
			sockaddr_in service;
			serv_port = port;

			closesocket(server_sock);

			memset(&service, 0, sizeof(service));
			service.sin_family = AF_INET;
			service.sin_addr.s_addr = htonl(INADDR_ANY);
			service.sin_port = htons(port);

			if ((server_sock = socket(AF_UNSPEC, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CREATE);
				return;
			}

			if (bind(server_sock, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) 
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_BIND_ERROR);
				return;
			}
		}

		SOCKET UDPSocket::get_id(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, INVALID_SOCKET);

			return server_sock;
		}

		int UDPSocket::send_data(char *data, int data_size, char *host, char *via_port)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			int result = 0;

			addrinfo hints, *s = nullptr;
			memset(&hints, 0, sizeof(hints));

			hints.ai_family = AF_UNSPEC;
			hints.ai_flags = AI_PASSIVE;
			hints.ai_protocol = IPPROTO_UDP;
			hints.ai_socktype = SOCK_DGRAM;

			if (getaddrinfo(host, via_port, &hints, &s) == 0)
			{
				SOCKET via_sock = socket(s->ai_family, s->ai_socktype, s->ai_protocol);
				result = sendto(via_sock, data, data_size, 0, s->ai_addr, s->ai_addrlen);
				closesocket(via_sock);
			}
			else
				result = -1;

			if (s != nullptr)
				freeaddrinfo(s);

			return result;
		}

		VALUE UDPSocket::receive_data(int max_buffer)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);
			
			sockaddr_storage res;
			socklen_t res_len;

			char *buffer = nullptr;
			VALUE ret_str = Qnil;
			int result = 0;

			if ((max_buffer > RAGE_SOCKET_UDP_MAX_BUFFER) || (max_buffer <= 0)) 
				max_buffer = RAGE_SOCKET_UDP_MAX_BUFFER;

			buffer = new char[max_buffer];
			memset(buffer, 0, max_buffer);

			result = recvfrom(server_sock, buffer, max_buffer, 0, (sockaddr*)&res, &res_len);

			if (result > 0)
			{
				char s[INET6_ADDRSTRLEN];
					
				ret_str = rb_ary_new();

				void *ip;
				int family = ((sockaddr*)&res)->sa_family;

				if (family == AF_INET) 
					ip = &(((sockaddr_in*)&res)->sin_addr);
				else
					ip = &(((sockaddr_in6*)&res)->sin6_addr);


				rb_ary_push(ret_str, rb_str_new2(inet_ntop(res.ss_family, ip, s, INET6_ADDRSTRLEN)));
				rb_ary_push(ret_str, rb_str_new(buffer, result));
			}

			return ret_str;
		}

		int UDPSocket::get_server_port(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return serv_port;
		}

		void UDPSocket::dispose(void)
		{
			if (disposed)
				return;

			closesocket(server_sock);

			#ifdef WIN32
			if (!WSACleanup())
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_WSA_CLEANUP);
				return;
			}
			#endif

			disposed = true;
		}

		UDPSocket::~UDPSocket(void)
		{
			if (!disposed)
				dispose();
		}

	}
}

#endif