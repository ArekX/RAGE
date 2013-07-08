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
			static VALUE rb_attach_shader(VALUE self, VALUE shader);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_is_disposed(VALUE self);
		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};
	}
}