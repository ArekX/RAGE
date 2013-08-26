#pragma once

#include "TCPClient.h"

namespace RAGE
{
	namespace Network
	{

		class TCPClientWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_connect(VALUE self, VALUE host, VALUE port);
			static VALUE rb_send(VALUE self, VALUE data);
			static VALUE rb_recv(int argc, VALUE *args, VALUE self);
			static VALUE rb_get_blocking(VALUE self);
			static VALUE rb_set_blocking(VALUE self, VALUE val);
			static VALUE rb_get_connected(VALUE self);
			static VALUE rb_disconnect(VALUE self);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(int argc, VALUE *args);
		};
	}
}

