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

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_UDP_SOCKET

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

#define RAGE_SOCKET_UDP_MAX_BUFFER 65536

namespace RAGE
{
	namespace Network
	{
		class UDPSocket
		{
		private:
			SOCKET server_sock;
			int serv_port;
		public:
			bool disposed;
			UDPSocket(void);
			void initialize(int port);
			SOCKET get_id(void);
			int send_data(char *data, int data_size, char *host, char *via_port);
			VALUE receive_data(int max_buffer);
			int get_server_port(void);
			void dispose(void);
			~UDPSocket(void);
		};
	}
}

#endif