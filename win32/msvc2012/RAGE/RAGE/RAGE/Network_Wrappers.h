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

namespace RAGE
{
	namespace Network
	{
		class NetworkWrappers
		{
		private:
			
			static VALUE rb_get_string(int argc, VALUE *args, VALUE self);
			static VALUE rb_post_string(int argc, VALUE *args, VALUE self);
		public:
			static void load_wrappers(void);
		};
	}
}

