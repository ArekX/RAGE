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

#pragma once

#include "RubyInterpreter.h"

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

#define RAGE_CLIENT_TCP_MAX_BUFFER 2048

namespace RAGE
{
	namespace Network
	{
		class TCPClient
		{
		private:
			SOCKET sock;
			timeval timeout;
			u_long blocking_mode;
			int port;
			bool connected;
		public:
			bool disposed;
			TCPClient(void);
			void tcp_connect(char *host, int prt);
			int tcp_send(char *data, int len);
			VALUE tcp_recv(int max_buffer);
			SOCKET get_id(void);
			bool get_data_available(void);
			bool get_connected(void);
			void set_blocking_mode(bool blocking);
			bool get_blocking_mode(void);
			int get_timeout(void);
			void set_timeout(int seconds);
			int get_port(void);
			void disconnect(void);
			void dispose(void);
			~TCPClient(void);
		};
	}
}