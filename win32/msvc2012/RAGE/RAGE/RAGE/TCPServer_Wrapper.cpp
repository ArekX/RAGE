#include "TCPServer_Wrapper.h"

namespace RAGE
{
	namespace Network
	{
		VALUE rb_rage_TCPServerClass;

		VALUE TCPServerWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, TCPServerWrapper::rb_destroy, new TCPServer());
		}

		void TCPServerWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE TCPServerWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if ((argc < 1) || (argc > 3))
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 3);
			}
			else
			{
				RAGE_GET_DATA(self, TCPServer, sv);
			
				sv->initialize(
								FIX2INT(args[0]), 
								(argc == 2) ? (TYPE(args[1]) == T_TRUE) : true, 
								(argc == 3) ? FIX2INT(args[2]) : RAGE_SERVER_TCP_DEFAULT_BACKLOG
							  );
			}

			return Qnil;
		}

		VALUE TCPServerWrapper::rb_listen(int argc, VALUE *args, VALUE self)
		{
			RAGE_GET_DATA(self, TCPServer, sv);
			
			SOCKET client = sv->listen_clients();

			if (client == INVALID_SOCKET)
				return Qnil;
			else
				return LL2NUM(client);
		}

		VALUE TCPServerWrapper::rb_send(VALUE self, VALUE client, VALUE data)
		{
			RAGE_GET_DATA(self, TCPServer, sv);

			return INT2FIX(sv->send_data(NUM2LL(client), RSTRING_PTR(data), RSTRING_LEN(data)));
		}

		VALUE TCPServerWrapper::rb_recv(int argc, VALUE *args, VALUE self)
		{
			if ((argc < 1) || (argc > 2))
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 2);
			}
			else
			{
				RAGE_GET_DATA(self, TCPServer, sv);
				return sv->receive_data(NUM2LL(args[0]), (argc == 2) ? FIX2INT(args[1]) : 0);
			}
			
			return Qnil;
		}

		VALUE TCPServerWrapper::rb_is_connected(VALUE self, VALUE client)
		{
			RAGE_GET_DATA(self, TCPServer, sv);

			return INT2FIX(sv->data_available(NUM2LL(client)));
		}

		VALUE TCPServerWrapper::rb_get_ip(VALUE self, VALUE client, VALUE ip_type)
		{
			RAGE_GET_DATA(self, TCPServer, sv);

			char *str = sv->get_client_ip(NUM2LL(client), FIX2INT(ip_type));

			if (str == NULL)
				return Qnil;
			else
			{
				VALUE ret_str = rb_str_new2(str);
				delete str;

				return ret_str;
			}
		}

		VALUE TCPServerWrapper::rb_disconnect(VALUE self, VALUE client)
		{
			RAGE_GET_DATA(self, TCPServer, sv);

			sv->disconnect(NUM2LL(client));

			return Qnil;
		}

		VALUE TCPServerWrapper::rb_dispose(VALUE self)
		{
			RAGE_GET_DATA(self, TCPServer, sv);

			sv->dispose();
			
			return Qnil;
		}

		VALUE TCPServerWrapper::rb_disposed(VALUE self)
		{
			RAGE_GET_DATA(self, TCPServer, sv);

			return sv->disposed ? Qtrue : Qfalse;
		}

		VALUE TCPServerWrapper::rb_get_id(VALUE self)
		{
			RAGE_GET_DATA(self, TCPServer, sv);

			return LL2NUM(sv->get_id());
		}

		void TCPServerWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::TCPServer")) return;

			VALUE rage = rb_define_module("RAGE");

			rb_rage_TCPServerClass = rb_define_class_under(rage, "TCPServer", rb_cObject);
			
			rb_define_alloc_func(rb_rage_TCPServerClass, TCPServerWrapper::rb_alloc);

			rb_define_method(rb_rage_TCPServerClass, "initialize", RFUNC(TCPServerWrapper::rb_initialize), -1);
			rb_define_method(rb_rage_TCPServerClass, "id", RFUNC(TCPServerWrapper::rb_get_id), 0);
			rb_define_method(rb_rage_TCPServerClass, "listen", RFUNC(TCPServerWrapper::rb_listen), -1);
			rb_define_method(rb_rage_TCPServerClass, "send", RFUNC(TCPServerWrapper::rb_send), 2);
			rb_define_method(rb_rage_TCPServerClass, "receive", RFUNC(TCPServerWrapper::rb_recv), -1);
			rb_define_method(rb_rage_TCPServerClass, "getIP", RFUNC(TCPServerWrapper::rb_get_ip), 2);
			rb_define_method(rb_rage_TCPServerClass, "getAvailableData", RFUNC(TCPServerWrapper::rb_is_connected), 1);
			rb_define_method(rb_rage_TCPServerClass, "disconnect", RFUNC(TCPServerWrapper::rb_disconnect), 1);
			rb_define_method(rb_rage_TCPServerClass, "dispose", RFUNC(TCPServerWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_TCPServerClass, "disposed?", RFUNC(TCPServerWrapper::rb_dispose), 0);
		}

		VALUE TCPServerWrapper::get_ruby_class(void)
		{
			return rb_rage_TCPServerClass;
		}

		VALUE TCPServerWrapper::new_ruby_class_instance(int argc, VALUE *args)
		{
			return rb_class_new_instance(argc, args, rb_rage_TCPServerClass);
		}
	}
}
