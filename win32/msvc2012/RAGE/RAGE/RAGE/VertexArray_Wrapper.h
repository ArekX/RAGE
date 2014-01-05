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

#if RAGE_COMPILE_VERTEX_ARRAY

namespace RAGE
{
	namespace Graphics
	{
		class VertexArrayWrapper
		{
		private:
			static VALUE rb_allocate(VALUE self);
			static void rb_destroy(void* ptr);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_push_c(VALUE self, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE r, VALUE g, VALUE b, VALUE a);
			
			#if RAGE_COMPILE_COLOR
			static VALUE rb_push(VALUE self, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE color);
			static VALUE rb_change(VALUE self, VALUE index, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE color);
			static VALUE rb_get_color(VALUE self, VALUE index);
			static VALUE rb_get_color_to(VALUE self, VALUE index, VALUE color);
			static VALUE rb_set_color(VALUE self, VALUE index, VALUE color);
			#endif

			static VALUE rb_change_c(VALUE self, VALUE index, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE rb_pop(VALUE self);
			static VALUE rb_remove(VALUE self, VALUE index);
			static VALUE rb_clear(VALUE self);
			static VALUE rb_size(VALUE self);
			static VALUE rb_get_x(VALUE self, VALUE index);
			static VALUE rb_get_y(VALUE self, VALUE index);
			static VALUE rb_get_z(VALUE self, VALUE index);
			static VALUE rb_get_u(VALUE self, VALUE index);
			static VALUE rb_get_v(VALUE self, VALUE index);
			static VALUE rb_set_x(VALUE self, VALUE index, VALUE x);
			static VALUE rb_set_y(VALUE self, VALUE index, VALUE y);
			static VALUE rb_set_z(VALUE self, VALUE index, VALUE z);
			static VALUE rb_set_u(VALUE self, VALUE index, VALUE u);
			static VALUE rb_set_v(VALUE self, VALUE index, VALUE v);
			static VALUE rb_set_color_c(VALUE self, VALUE index, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_is_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}

#endif