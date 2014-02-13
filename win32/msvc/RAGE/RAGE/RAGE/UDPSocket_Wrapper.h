/*
Copyright (c) 2014 Aleksandar Panic

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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_UDP_SOCKET

namespace RAGE
{
	namespace Network
	{

		class UDPSocketWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_initialize(VALUE self, VALUE port);
			static VALUE rb_send(VALUE self, VALUE data, VALUE host, VALUE port);
			static VALUE rb_recv(int argc, VALUE *args, VALUE self);
			static VALUE rb_get_port(VALUE self);
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

#endif