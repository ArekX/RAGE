#include "TCPClient_Wrapper.h"

namespace RAGE
{
	namespace Network
	{
		VALUE rb_rage_TCPClientClass;

		VALUE TCPClientWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, TCPClientWrapper::rb_destroy, new TCPClient());
		}

		void TCPClientWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE TCPClientWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if ((argc == 1) || (argc > 2))
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 0, 2);
				return Qnil;
			}

			if (argc == 2)
				TCPClientWrapper::rb_connect(self, args[0], args[1]);
			

			return Qnil;
		}

		VALUE TCPClientWrapper::rb_connect(VALUE self, VALUE host, VALUE port)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			VALUE port_string = rb_fix2str(port, 10);
			
			cl->tcp_connect(StringValueCStr(host), StringValueCStr(port_string));

			return Qnil;
		}

		VALUE TCPClientWrapper::rb_send(VALUE self, VALUE data)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			return INT2FIX(cl->tcp_send(RSTRING_PTR(data), RSTRING_LEN(data)));
		}

		VALUE TCPClientWrapper::rb_recv(int argc, VALUE *args, VALUE self)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			if (argc > 1)
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 0, 1);
				return Qnil;
			}

			return cl->tcp_recv((argc == 1) ? FIX2INT(args[0]) : 0);
		}

	    VALUE TCPClientWrapper::rb_get_connected(VALUE self)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			return cl->get_connected() ? Qtrue : Qfalse;
		}

		VALUE TCPClientWrapper::rb_disconnect(VALUE self)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			cl->disconnect();

			return Qnil;
		}

		VALUE TCPClientWrapper::rb_get_blocking(VALUE self)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			return cl->get_blocking_mode() ? Qtrue : Qfalse;
		}

		VALUE TCPClientWrapper::rb_set_blocking(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			cl->set_blocking_mode((TYPE(val) == T_TRUE));

			return Qnil;
		}

		VALUE TCPClientWrapper::rb_dispose(VALUE self)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			cl->dispose();

			return Qnil;
		}

		VALUE TCPClientWrapper::rb_disposed(VALUE self)
		{
			RAGE_GET_DATA(self, TCPClient, cl);

			return cl->disposed ? Qtrue : Qfalse;
		}

		void TCPClientWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::TCPClient")) return;

			VALUE rage = rb_define_module("RAGE");

			rb_rage_TCPClientClass = rb_define_class_under(rage, "TCPClient", rb_cObject);

			rb_define_alloc_func(rb_rage_TCPClientClass, TCPClientWrapper::rb_alloc);

			rb_define_method(rb_rage_TCPClientClass, "initialize", RFUNC(TCPClientWrapper::rb_initialize), -1);
			rb_define_method(rb_rage_TCPClientClass, "connected?", RFUNC(TCPClientWrapper::rb_get_connected), 0);
			rb_define_method(rb_rage_TCPClientClass, "connect", RFUNC(TCPClientWrapper::rb_connect), 2);
			rb_define_method(rb_rage_TCPClientClass, "send", RFUNC(TCPClientWrapper::rb_send), 1);
			rb_define_method(rb_rage_TCPClientClass, "receive", RFUNC(TCPClientWrapper::rb_recv), -1);
			rb_define_method(rb_rage_TCPClientClass, "blocking=", RFUNC(TCPClientWrapper::rb_set_blocking), 1);
			rb_define_method(rb_rage_TCPClientClass, "blocking", RFUNC(TCPClientWrapper::rb_get_blocking), 0);
			rb_define_method(rb_rage_TCPClientClass, "disconnect", RFUNC(TCPClientWrapper::rb_disconnect), 0);
			rb_define_method(rb_rage_TCPClientClass, "dispose", RFUNC(TCPClientWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_TCPClientClass, "disposed?", RFUNC(TCPClientWrapper::rb_disposed), 0);
		}

		VALUE TCPClientWrapper::get_ruby_class(void)
		{
			return rb_rage_TCPClientClass;
		}

		VALUE TCPClientWrapper::new_ruby_class_instance(int argc, VALUE *args)
		{
			return rb_class_new_instance(argc, args, rb_rage_TCPClientClass);
		}
	}
}
