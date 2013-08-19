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

#include "Shader.h"

namespace RAGE
{
	namespace Graphics
	{
		class ShaderWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void* value);
			static VALUE rb_initialize(VALUE self, VALUE shader_type, VALUE code);
			static VALUE rb_bind_texture(VALUE self, VALUE val_name, VALUE bitmap);
			static VALUE rb_set_float(VALUE self, VALUE float_name, VALUE val);
			static VALUE rb_set_int(VALUE self, VALUE int_name, VALUE val);
			static VALUE rb_set_iv2(int argc, VALUE *args, VALUE self);
			static VALUE rb_set_iv3(int argc, VALUE *args, VALUE self);
			static VALUE rb_set_iv4(int argc, VALUE *args, VALUE self);
			static VALUE rb_set_fv2(int argc, VALUE *args, VALUE self);
			static VALUE rb_set_fv3(int argc, VALUE *args, VALUE self);
			static VALUE rb_set_fv4(int argc, VALUE *args, VALUE self);
			static VALUE rb_set_mat(int argc, VALUE *args, VALUE self);
			static VALUE rb_attach_shader(VALUE self, VALUE shader);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_is_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}