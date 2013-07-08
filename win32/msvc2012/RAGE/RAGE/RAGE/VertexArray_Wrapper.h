#pragma once

#include "VertexArray.h"

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
			static VALUE rb_push(VALUE self, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE color);
			static VALUE rb_change(VALUE self, VALUE index, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE color);
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
			static VALUE rb_get_color(VALUE self, VALUE index);
			static VALUE rb_get_color_to(VALUE self, VALUE index, VALUE color);
			static VALUE rb_set_x(VALUE self, VALUE index, VALUE x);
			static VALUE rb_set_y(VALUE self, VALUE index, VALUE y);
			static VALUE rb_set_z(VALUE self, VALUE index, VALUE z);
			static VALUE rb_set_u(VALUE self, VALUE index, VALUE u);
			static VALUE rb_set_v(VALUE self, VALUE index, VALUE v);
			static VALUE rb_set_color(VALUE self, VALUE index, VALUE color);
			static VALUE rb_set_color_c(VALUE self, VALUE index, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_is_disposed(VALUE self);
		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};
	}
}

