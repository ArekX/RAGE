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

#include "UDPSocket_Wrapper.h"
#include "UDPSocket.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_UDP_SOCKET

namespace RAGE
{
	namespace Network
	{
		VALUE rb_rage_UDPSocketClass;

		VALUE UDPSocketWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, UDPSocketWrapper::rb_destroy, new UDPSocket());
		}

		void UDPSocketWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE UDPSocketWrapper::rb_initialize(VALUE self, VALUE port)
		{
			RAGE_GET_DATA(self, UDPSocket, sv);
			
			sv->initialize(FIX2INT(port));

			return Qnil;
		}

		VALUE UDPSocketWrapper::rb_send(VALUE self, VALUE data, VALUE host, VALUE port)
		{
			RAGE_GET_DATA(self, UDPSocket, sv);

			VALUE port_string = rb_fix2str(port, 10);

			return INT2FIX(sv->send_data(RSTRING_PTR(data), RSTRING_LEN(data), StringValueCStr(host), StringValueCStr(port_string)));
		}

		VALUE UDPSocketWrapper::rb_recv(int argc, VALUE *args, VALUE self)
		{
			RAGE_GET_DATA(self, UDPSocket, sv);

			if (argc == 0)
				return sv->receive_data(0);
			else if (argc == 1)
				return sv->receive_data(FIX2INT(args[0]));
			else
				rb_raise(rb_eException, RAGE_VAR_FUNCTION_INCOMP_ARGS, 0, 1);

			return Qnil;
		}

		VALUE UDPSocketWrapper::rb_get_port(VALUE self)
		{
			RAGE_GET_DATA(self, UDPSocket, sv);

			return INT2FIX(sv->get_server_port());
		}

		VALUE UDPSocketWrapper::rb_dispose(VALUE self)
		{
			RAGE_GET_DATA(self, UDPSocket, sv);

			sv->dispose();
			
			return Qnil;
		}

		VALUE UDPSocketWrapper::rb_disposed(VALUE self)
		{
			RAGE_GET_DATA(self, UDPSocket, sv);

			return sv->disposed ? Qtrue : Qfalse;
		}

		VALUE UDPSocketWrapper::rb_get_id(VALUE self)
		{
			RAGE_GET_DATA(self, UDPSocket, sv);

			return LL2NUM(sv->get_id());
		}

		void UDPSocketWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::UDPSocket")) return;

			VALUE rage = rb_define_module("RAGE");

			rb_rage_UDPSocketClass = rb_define_class_under(rage, "UDPSocket", rb_cObject);
			
			rb_define_alloc_func(rb_rage_UDPSocketClass, UDPSocketWrapper::rb_alloc);

			rb_define_method(rb_rage_UDPSocketClass, "initialize", RFUNC(UDPSocketWrapper::rb_initialize), 1);
			rb_define_method(rb_rage_UDPSocketClass, "id", RFUNC(UDPSocketWrapper::rb_get_id), 0);
			rb_define_method(rb_rage_UDPSocketClass, "port", RFUNC(UDPSocketWrapper::rb_get_port), 0);
			rb_define_method(rb_rage_UDPSocketClass, "send", RFUNC(UDPSocketWrapper::rb_send), 3);
			rb_define_method(rb_rage_UDPSocketClass, "receive", RFUNC(UDPSocketWrapper::rb_recv), -1);
			rb_define_method(rb_rage_UDPSocketClass, "dispose", RFUNC(UDPSocketWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_UDPSocketClass, "disposed?", RFUNC(UDPSocketWrapper::rb_dispose), 0);
		}

		VALUE UDPSocketWrapper::get_ruby_class(void)
		{
			return rb_rage_UDPSocketClass;
		}

		VALUE UDPSocketWrapper::new_ruby_class_instance(int argc, VALUE *args)
		{
			return rb_class_new_instance(argc, args, rb_rage_UDPSocketClass);
		}
	}
}

#endif