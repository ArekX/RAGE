#include "Network_Wrappers.h"

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

namespace RAGE
{
	namespace Network
	{
		#ifdef WIN32
		WSAData w_data;
		#endif

		std::string *post_buffer = NULL;

		int rb_post_hash_callback(VALUE key, VALUE val, VALUE in)
		{

			post_buffer->append(StringValueCStr(key));
			post_buffer->append(SOCKET_POST_EQUALS);
			post_buffer->append(StringValueCStr(val));
			post_buffer->append(SOCKET_POST_AND);

			return ST_CONTINUE;
		}

		VALUE NetworkWrappers::rb_get_string(int argc, VALUE *args, VALUE self)
		{
			if ((argc < 1) || (argc > 3))
			{
				rb_raise(rb_eException, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 3);
				return Qnil;
			}
			
			#ifdef WIN32
			WSAData wd_data;
			WSAStartup(MAKEWORD(2,0), &wd_data);
			#endif

			SOCKET sock;
			int status;
			addrinfo hints, *servinfo;
			
			memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_flags = AI_PASSIVE;

			std::string *s_uri = new std::string(StringValueCStr(args[0]));
			std::string *s_get = new std::string(SOCKET_URI_SEPARATOR);
			std::string *s_port = new std::string(SOCKET_PORT_HTTP);

			if (s_uri->find_first_of(SOCKET_HTTP_STRIP) != s_uri->npos)
				s_uri->erase(0, 7);

			if (s_uri->find_first_of(SOCKET_PORT_SEPARATOR) != s_uri->npos)
			{
				s_port->assign(s_uri->substr(s_uri->find_first_of(SOCKET_PORT_SEPARATOR) + 1, 
					           s_uri->size() - s_uri->find_first_of(SOCKET_PORT_SEPARATOR)));
				s_uri->erase(s_uri->find_first_of(SOCKET_PORT_SEPARATOR), 
					         s_uri->size() - s_uri->find_first_of(SOCKET_PORT_SEPARATOR));
			}

			if (s_uri->find_first_of(SOCKET_URI_SEPARATOR) != s_uri->npos)
			{
				s_get->append(s_uri->substr(s_uri->find_first_of(SOCKET_URI_SEPARATOR) + 1, 
					          s_uri->size() - s_uri->find_first_of(SOCKET_URI_SEPARATOR)));
				s_uri->erase(s_uri->find_first_of(SOCKET_URI_SEPARATOR), 
					         s_uri->size() - s_uri->find_first_of(SOCKET_URI_SEPARATOR));
			}

			const char *res_uri = s_uri->c_str();

			#ifdef WIN32
			if (getaddrinfo((PCSTR)res_uri, s_port->c_str(), &hints, &servinfo) != 0)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RESOLVE_HOST);
				return Qnil;
			}
			#else
			if (getaddrinfo(res_uri, s_port->c_str(), &hints, &servinfo) != 0)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RESOLVE_HOST);
				return Qnil;
			}
			#endif

			sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

			if (sock == INVALID_SOCKET)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CREATE);
				return Qnil;
			}

			if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CONNECT_HOST);
				return Qnil;
			}

			std::string *header = new std::string();
			
			if (argc != 3)
			{
				header->append(SOCKET_HEADERS_GET);
				header->append(s_get->c_str());
				header->append(SOCKET_HEADERS_1);
				header->append(res_uri);
				header->append(SOCKET_HEADERS_2);
			}
			else
				header->append(StringValueCStr(args[2]));

			char buffer[2048];
			int result = 0;
			u_long mode = 1; 

			if (send(sock, header->c_str(), header->size(), 0) == SOCKET_ERROR) 
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_SEND_DATA);
				return Qnil;
			}
			 

			std::string *str = new std::string();
			char *data = NULL;
			int64_t len = 0;
			int i = 0;

			do {
				memset(buffer, 0, 2048);

				result = recv(sock, buffer, 2048, 0);

				if (result == SOCKET_ERROR)
				{
					rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RECV_DATA);
					return Qnil;
				}

				if (result > 0)
				{
					data = (char*)al_realloc(data, len + result);

					for (i = 0; i < result; i++)
						data[len++] = buffer[i];
				}

			}
			while (result > 0);

			close(sock);
			freeaddrinfo(servinfo);

			str->assign(data, len);

			VALUE ret_str;

			if (TYPE(args[1]) == T_TRUE)
				ret_str = rb_str_new(str->data(), str->size());
			else
			{
				ret_str = rb_str_new(
									 str->substr(str->find(SOCKET_HTTP_REQ_END) + 4, 
					                 str->find(SOCKET_HTTP_REQ_END) - str->size()).data(), 
									 str->substr(str->find(SOCKET_HTTP_REQ_END) + 4,
								     str->find(SOCKET_HTTP_REQ_END) - str->size()).size()
									);
			}

			delete str;
			delete header;
			delete s_get;
			delete s_port;
			delete s_uri;

			#ifdef WIN32
			WSACleanup();
			#endif

			return ret_str;
		}

		VALUE NetworkWrappers::rb_post_string(int argc, VALUE *args, VALUE self)
		{
			if ((argc < 1) || (argc > 3))
			{
				rb_raise(rb_eException, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 3);
				return Qnil;
			}
			
			#ifdef WIN32
			WSAData wd_data;
			WSAStartup(MAKEWORD(2,0), &wd_data);
			#endif

			SOCKET sock;
			int status;
			addrinfo hints, *servinfo;
			
			memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_flags = AI_PASSIVE;

			std::string *s_uri = new std::string(StringValueCStr(args[0]));
			std::string *s_get = new std::string(SOCKET_URI_SEPARATOR);
			std::string *s_port = new std::string(SOCKET_PORT_HTTP);

			if (s_uri->find_first_of(SOCKET_HTTP_STRIP) != s_uri->npos)
				s_uri->erase(0, 7);

			if (s_uri->find_first_of(SOCKET_PORT_SEPARATOR) != s_uri->npos)
			{
				s_port->assign(s_uri->substr(s_uri->find_first_of(SOCKET_PORT_SEPARATOR) + 1, 
					           s_uri->size() - s_uri->find_first_of(SOCKET_PORT_SEPARATOR)));
				s_uri->erase(s_uri->find_first_of(SOCKET_PORT_SEPARATOR), 
					         s_uri->size() - s_uri->find_first_of(SOCKET_PORT_SEPARATOR));
			}

			if (s_uri->find_first_of(SOCKET_URI_SEPARATOR) != s_uri->npos)
			{
				s_get->append(s_uri->substr(s_uri->find_first_of(SOCKET_URI_SEPARATOR) + 1, 
					          s_uri->size() - s_uri->find_first_of(SOCKET_URI_SEPARATOR)));
				s_uri->erase(s_uri->find_first_of(SOCKET_URI_SEPARATOR), 
					         s_uri->size() - s_uri->find_first_of(SOCKET_URI_SEPARATOR));
			}

			const char *res_uri = s_uri->c_str();

			#ifdef WIN32
			if (getaddrinfo((PCSTR)res_uri, s_port->c_str(), &hints, &servinfo) != 0)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RESOLVE_HOST);
				return Qnil;
			}
			#else
			if (getaddrinfo(res_uri, s_port->c_str(), &hints, &servinfo) != 0)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RESOLVE_HOST);
				return Qnil;
			}
			#endif

			sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

			if (sock == INVALID_SOCKET)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CREATE);
				return Qnil;
			}

			if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) == SOCKET_ERROR)
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_CONNECT_HOST);
				return Qnil;
			}

			char content_length[32] = {0};

			if ((argc >= 2) && (TYPE(args[1]) == T_HASH))
			{
				post_buffer = new std::string();
				rb_hash_foreach(args[1], (int(*)(...))rb_post_hash_callback, RUBY_HASH_PASSTHROUGH);

				if (post_buffer->size() > 0)
					post_buffer->pop_back();

				#ifdef WIN32
				sprintf_s(content_length, 32, "%d", post_buffer->size());
				#else
				sprintf(content_length, "%d", post_buffer->size());
				#endif
			}

			std::string *header = new std::string();
			
			if (argc != 4)
			{
				header->append(SOCKET_HEADERS_POST);
				header->append(s_get->c_str());
				header->append(SOCKET_HEADERS_1);
				header->append(res_uri);
				header->append(SOCKET_HEADERS_POST_1);
				header->append(SOCKET_HEADERS_POST_LENGTH);
				header->append(content_length);
				header->append(SOCKET_HEADERS_POST_2);
				header->append(post_buffer->c_str());
			}
			else
				header->append(StringValueCStr(args[3]));

			char buffer[2048];
			int result = 0;
			u_long mode = 1; 

			if (send(sock, header->c_str(), header->size(), 0) == SOCKET_ERROR) 
			{
				rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_SEND_DATA);
				return Qnil;
			}
			 

			std::string *str = new std::string();
			char *data = NULL;
			int64_t len = 0;
			int i = 0;

			do {
				memset(buffer, 0, 2048);

				result = recv(sock, buffer, 2048, 0);

				if (result == SOCKET_ERROR)
				{
					rb_raise(rb_eException, RAGE_ERROR_SOCKET_CANNOT_RECV_DATA);
					return Qnil;
				}

				if (result > 0)
				{
					data = (char*)al_realloc(data, len + result);

					for (i = 0; i < result; i++)
						data[len++] = buffer[i];
				}

			}
			while (result > 0);

			close(sock);
			freeaddrinfo(servinfo);

			str->assign(data, len);

			VALUE ret_str;

			if (TYPE(args[1]) == T_TRUE)
				ret_str = rb_str_new(str->data(), str->size());
			else
			{
				ret_str = rb_str_new(
									 str->substr(str->find(SOCKET_HTTP_REQ_END) + 4, 
					                 str->find(SOCKET_HTTP_REQ_END) - str->size()).data(), 
									 str->substr(str->find(SOCKET_HTTP_REQ_END) + 4,
								     str->find(SOCKET_HTTP_REQ_END) - str->size()).size()
									);			
			}

			delete str;
			delete header;
			delete s_get;
			delete s_port;
			delete s_uri;
			delete post_buffer;

			#ifdef WIN32
			WSACleanup();
			#endif

			return ret_str;
		}

		void NetworkWrappers::load_wrappers(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Net")) return;

			VALUE rage = rb_define_module("RAGE");
			VALUE net = rb_define_module_under(rage, "Net");

			rb_define_module_function(net, "httpGET", RFUNC(NetworkWrappers::rb_get_string), -1);
			rb_define_module_function(net, "httpPOST", RFUNC(NetworkWrappers::rb_post_string), -1);
		}
	}
}
