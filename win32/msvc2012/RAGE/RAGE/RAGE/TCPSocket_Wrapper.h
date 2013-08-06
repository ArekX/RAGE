#pragma once

#include "TCPSocket.h"

namespace RAGE
{
	namespace Network
	{
		class TCPSocketWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_create(VALUE self, VALUE port);
			static VALUE rb_connect(VALUE self, VALUE ip, VALUE port);
			static VALUE rb_send(VALUE self, VALUE data);
			static VALUE rb_receive_all(VALUE self);
			static VALUE rb_receive(int argc, VALUE *args, VALUE self);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_is_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}
