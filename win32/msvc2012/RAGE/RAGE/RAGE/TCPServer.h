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
			void bind_server(void);
		public:
			bool disposed;
			TCPServer(void);
			void initialize(int port, bool blocking_mode, int max_connections);
			SOCKET get_id(void);
			SOCKET listen_clients(void);
			int send_data(SOCKET client_sock, char *data, int size);
			VALUE receive_data(SOCKET client_sock, int max_buffer);
			char* get_client_ip(SOCKET client_sock, int ip_type);
			void disconnect(SOCKET client_sock);
			int data_available(SOCKET client_sock);
			void dispose(void);
			~TCPServer(void);
		};
	}
}
