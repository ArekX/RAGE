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
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
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
