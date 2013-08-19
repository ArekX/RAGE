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

#include "TCPSocket_Wrapper.h"

namespace RAGE
{
	namespace Network
	{
		VALUE rb_rageTCPSocketClass;

		VALUE TCPSocketWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, TCPSocketWrapper::rb_destroy, new TCPSocket());
		}

		void TCPSocketWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE TCPSocketWrapper::rb_create(VALUE self, VALUE port)
		{
			TCPSocket *sc;
			Data_Get_Struct(self, TCPSocket, sc);

			sc->tcp_create(FIX2SHORT(port));

			sc->tcp_accept();

			return Qnil;
		}

		VALUE TCPSocketWrapper::rb_connect(VALUE self, VALUE ip, VALUE port)
		{
			TCPSocket *sc;
			Data_Get_Struct(self, TCPSocket, sc);

			sc->tcp_connect(StringValueCStr(ip), FIX2SHORT(port));

			return Qnil;
		}

		VALUE TCPSocketWrapper::rb_send(VALUE self, VALUE data)
		{
			TCPSocket *sc;
			Data_Get_Struct(self, TCPSocket, sc);

			return INT2FIX(sc->tcp_send(StringValueCStr(data)));
		}

		VALUE TCPSocketWrapper::rb_receive_all(VALUE self)
		{
			TCPSocket *sc;
			Data_Get_Struct(self, TCPSocket, sc);

			char *recv_str = sc->tcp_receive_all();
			
			VALUE str = rb_str_new2(recv_str);

			al_free(recv_str);

			return str;
			
		}

		VALUE TCPSocketWrapper::rb_receive(int argc, VALUE *args, VALUE self)
		{
			TCPSocket *sc;
			Data_Get_Struct(self, TCPSocket, sc);

			char *recv_str = sc->tcp_receive((argc == 1) ? FIX2INT(args[0]) : 0);
			
			VALUE str = rb_str_new2(recv_str);

			al_free(recv_str);

			return str;
		}

		VALUE TCPSocketWrapper::rb_dispose(VALUE self)
		{
			TCPSocket *sc;
			Data_Get_Struct(self, TCPSocket, sc);

			sc->dispose();

			return Qnil;
		}

		VALUE TCPSocketWrapper::rb_is_disposed(VALUE self)
		{
			TCPSocket *sc;
			Data_Get_Struct(self, TCPSocket, sc);

			return sc->disposed ? Qtrue : Qfalse;
		}

		void TCPSocketWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::TCPSocket")) return;

			VALUE rage = rb_define_module("RAGE");

			rb_rageTCPSocketClass = rb_define_class_under(rage, "TCPSocket", rb_cObject);

			rb_define_alloc_func(rb_rageTCPSocketClass, TCPSocketWrapper::rb_alloc);

			rb_define_method(rb_rageTCPSocketClass, "create", RFUNC(TCPSocketWrapper::rb_create), 1);
			rb_define_method(rb_rageTCPSocketClass, "connect", RFUNC(TCPSocketWrapper::rb_connect), 2);
			rb_define_method(rb_rageTCPSocketClass, "send", RFUNC(TCPSocketWrapper::rb_send), 1);
			rb_define_method(rb_rageTCPSocketClass, "receiveAll", RFUNC(TCPSocketWrapper::rb_receive_all), 0);
			rb_define_method(rb_rageTCPSocketClass, "receive", RFUNC(TCPSocketWrapper::rb_receive), -1);
			rb_define_method(rb_rageTCPSocketClass, "dispose", RFUNC(TCPSocketWrapper::rb_dispose), 0);
			rb_define_method(rb_rageTCPSocketClass, "disposed?", RFUNC(TCPSocketWrapper::rb_is_disposed), 0);
		}

		VALUE TCPSocketWrapper::get_ruby_class(void)
		{
			return rb_rageTCPSocketClass;
		}

		VALUE TCPSocketWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rageTCPSocketClass);
		}

	}
}