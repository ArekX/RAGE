#pragma once
#include "RubyInterpreter.h"
#include "Color.h"


namespace RAGE
{
	namespace Graphics
	{
		class ColorWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *value);
			static VALUE rb_from_rgba(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE rb_from_cmyk(VALUE self, VALUE c, VALUE m, VALUE y, VALUE k);
			static VALUE rb_from_hsl(VALUE self, VALUE h, VALUE s, VALUE l);
			static VALUE rb_from_hsv(VALUE self, VALUE h, VALUE s, VALUE v);
			static VALUE rb_from_yuv(VALUE self, VALUE y, VALUE u, VALUE v);
			static VALUE rb_from_html(VALUE self, VALUE html);
			static VALUE rb_from_name(VALUE self, VALUE name);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
			static VALUE rb_get_r(VALUE self);
			static VALUE rb_set_r(VALUE self, VALUE val);
			static VALUE rb_get_g(VALUE self);
			static VALUE rb_set_g(VALUE self, VALUE val);
			static VALUE rb_get_b(VALUE self);
			static VALUE rb_set_b(VALUE self, VALUE val);
			static VALUE rb_get_a(VALUE self);
			static VALUE rb_set_a(VALUE self, VALUE val);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}
