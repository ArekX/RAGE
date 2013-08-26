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
			u_long blocking_mode;
			bool connected;
		public:
			bool disposed;
			TCPClient(void);
			void tcp_connect(char *host, char *port);
			int tcp_send(char *data, int len);
			VALUE tcp_recv(int max_buffer);
			SOCKET get_id(void);
			bool get_connected(void);
			void set_blocking_mode(bool blocking);
			bool get_blocking_mode(void);
			void disconnect(void);
			void dispose(void);
			~TCPClient(void);
		};
	}
}