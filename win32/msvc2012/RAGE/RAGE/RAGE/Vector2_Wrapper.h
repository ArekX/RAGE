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
#include "Vector2.h"

namespace RAGE
{
	namespace Physics
	{
		class Vector2Wrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_get_x(VALUE self);
			static VALUE rb_get_y(VALUE self);
			static VALUE rb_set_x(VALUE self, VALUE val);
			static VALUE rb_set_y(VALUE self, VALUE val);
			static VALUE rb_skew(VALUE self);
			static VALUE rb_is_valid(VALUE self);
			static VALUE rb_normalize(VALUE self);
			static VALUE rb_set(VALUE self, VALUE x, VALUE y);
			static VALUE rb_set_zero(VALUE self);
			static VALUE rb_length(VALUE self);
			static VALUE rb_length_squared(VALUE self);
			static VALUE rb_add_operator(VALUE self, VALUE val);
			static VALUE rb_sub_operator(VALUE self, VALUE val);
			static VALUE rb_mul_operator(VALUE self, VALUE val);
			static VALUE rb_negate(VALUE self);
			static VALUE rb_indexed_get(VALUE self, VALUE index);
			static VALUE rb_indexed_set(VALUE self, VALUE index, VALUE val);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};

	}
}