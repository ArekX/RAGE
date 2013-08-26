#pragma once

#include "TCPServer.h"

namespace RAGE
{
	namespace Network
	{

		class TCPServerWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_listen(int argc, VALUE *args, VALUE self);
			static VALUE rb_send(VALUE self, VALUE client, VALUE data);
			static VALUE rb_recv(int argc, VALUE *args, VALUE self);
			static VALUE rb_get_ip(VALUE self, VALUE client, VALUE ip_type);
			static VALUE rb_disconnect(VALUE self, VALUE client);
			static VALUE rb_is_connected(VALUE self, VALUE client);
			static VALUE rb_get_id(VALUE self);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(int argc, VALUE *args);
		};
	}
}

