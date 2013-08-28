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

#include "Network_Wrappers.h"

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

		VALUE NetworkWrappers::rb_inet_ntop(VALUE self, VALUE ip_data, VALUE ip_type)
		{
			VALUE ret_str = Qnil;

			char c_ip[INET6_ADDRSTRLEN];

			return rb_str_new2(inet_ntop(FIX2INT(ip_type), RSTRING_PTR(ip_data), c_ip, INET6_ADDRSTRLEN));
		}

		VALUE NetworkWrappers::rb_inet_pton(VALUE self, VALUE ip, VALUE ip_type)
		{
			if (FIX2INT(ip_type) == AF_INET)
			{
				sockaddr_in sa;
				inet_pton(FIX2INT(ip_type), StringValueCStr(ip), &sa.sin_addr);
				return rb_str_new((const char*)&sa.sin_addr, sizeof(sa.sin_addr));
				
			}
			else if (FIX2INT(ip_type) == AF_INET6)
			{
				sockaddr_in6 sa6;
				inet_pton(FIX2INT(ip_type), StringValueCStr(ip), &sa6.sin6_addr);
				return rb_str_new((const char*)&sa6.sin6_addr, sizeof(sa6.sin6_addr));
			}
			else
				return Qnil;
		}

		void NetworkWrappers::load_wrappers(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Net")) return;

			VALUE rage = rb_define_module("RAGE");
			VALUE net = rb_define_module_under(rage, "Net");

			rb_define_const(net, "AF_INET", INT2FIX(AF_INET));
			rb_define_const(net, "AF_INET6", INT2FIX(AF_INET6));

			rb_define_module_function(net, "httpGET", RFUNC(NetworkWrappers::rb_get_string), -1);
			rb_define_module_function(net, "httpPOST", RFUNC(NetworkWrappers::rb_post_string), -1);
			rb_define_module_function(net, "inetPtoN", RFUNC(NetworkWrappers::rb_inet_pton), 2);
			rb_define_module_function(net, "inetNtoP", RFUNC(NetworkWrappers::rb_inet_ntop), 2);
		}
	}
}
