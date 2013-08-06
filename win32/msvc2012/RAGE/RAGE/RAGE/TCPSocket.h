#pragma once

#include "RubyInterpreter.h"
#include <WinSock2.h>

#define TCP_SOCKET_MAX_BUFFER 4096

namespace RAGE
{
	namespace Network
	{
		class TCPSocket
		{
		// FIXME: Server and client should have their socket id's available, use procs too.
		private:
			WSADATA wsaData;
			SOCKET main_sock;
			SOCKET accept_sock;
			SOCKET working_sock;
			sockaddr_in accept_connection;
			sockaddr_in connection;
			u_long blocking_mode;
			struct timeval timeout;
			int ip_address_type;
			bool connected;
			bool is_server;
		public:
			bool disposed;
			TCPSocket(void);
			void tcp_create(u_short port);
			void tcp_connect(char *ip, u_short port);
			void tcp_shutdown(int what);
			void tcp_accept(void);
			int tcp_send(char* data);
			char* tcp_receive_all(void);
			char* tcp_receive(int buffer_size);
			void tcp_set_blocking(bool blocking);
			bool tcp_get_blocking(void);
			void tcp_set_timeout(int seconds); 
			int tcp_get_timeout(void);
			int tcp_get_ip_type(void);
			void tcp_set_ip_type(int new_type);
			bool get_connected(void);
			void dispose(void);
			~TCPSocket(void);
		};

	}
}