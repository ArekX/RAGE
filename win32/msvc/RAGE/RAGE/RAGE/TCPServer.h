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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_TCP_SERVER

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

#define RAGE_SERVER_TCP_MAX_BUFFER 2048
#define RAGE_SERVER_TCP_DEFAULT_BACKLOG 10

namespace RAGE
{
	namespace Network
	{
		class TCPServer
		{
		private:
			SOCKET server_sock;
			addrinfo *serv_info;
			int max_clients;
			int blocking_default;
			int serv_port;
			bool connected;
		public:
			bool disposed;
			TCPServer(void);
			void initialize(int port, bool blocking_mode, int max_connections);
			SOCKET get_id(void);
			SOCKET listen_clients(void);
			int send_data(SOCKET client_sock, char *data, int size);
			bool get_is_data_available(SOCKET client_sock);
			VALUE receive_data(SOCKET client_sock, int max_buffer);
			char* get_client_ip(SOCKET client_sock);
			void disconnect(SOCKET client_sock);
			bool get_is_connected(SOCKET client_sock);
			int get_server_port(void);
			int get_max_clients(void);
			bool get_is_blocking(void);
			void dispose(void);
			~TCPServer(void);
		};
	}
}

#endif