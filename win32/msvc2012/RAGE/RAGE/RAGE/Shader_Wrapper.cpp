#include "Shader_Wrapper.h"

namespace RAGE
{
	namespace Graphics
	{
		VALUE rb_rageShaderClass;

		VALUE ShaderWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, ShaderWrapper::rb_destroy, new Shader());
		}

		void ShaderWrapper::rb_destroy(void* value)
		{
			free((Shader*)value);
		}

		VALUE ShaderWrapper::rb_initialize(VALUE self, VALUE code)
		{
			Shader *sh;

			Data_Get_Struct(self, Shader, sh);

			sh->set_code(StringValueCStr(code));

			return Qnil;
		}

	    VALUE ShaderWrapper::rb_bind_texture(VALUE self, VALUE val_name, VALUE bitmap)
		{
			Shader *sh;
			Bitmap *bmp;

			Data_Get_Struct(self, Shader, sh);
			Data_Get_Struct(bitmap, Bitmap, bmp);

			sh->bind_bitmap(StringValueCStr(val_name), bmp->bitmap); 

			return Qnil;
		}

		VALUE ShaderWrapper::rb_set_float(VALUE self, VALUE float_name, VALUE val)
		{
			Shader *sh;
			Data_Get_Struct(self, Shader, sh);
			
			sh->set_float(StringValueCStr(float_name), NUM2DBL(val));

			return Qnil;
		}

		VALUE ShaderWrapper::rb_dispose(VALUE self)
		{
			Shader *sh;
			Data_Get_Struct(self, Shader, sh);

			sh->dispose();

			return Qnil;
		}

		VALUE ShaderWrapper::rb_is_disposed(VALUE self)
		{
			Shader *sh;
			Data_Get_Struct(self, Shader, sh);

			if (sh->disposed == true)
				return Qtrue;

			return Qfalse;
		}

		VALUE ShaderWrapper::rb_set_int(VALUE self, VALUE int_name, VALUE val)
		{
			Shader *sh;
			Data_Get_Struct(self, Shader, sh);

			sh->set_int(StringValueCStr(int_name), FIX2INT(val));
			
			return Qnil;
		}

		void ShaderWrapper::load_ruby_class()
		{
			VALUE rage = rb_define_module("RAGE");
			
			rb_rageShaderClass = rb_define_class_under(rage, "Shader", rb_cObject);

			rb_define_alloc_func(rb_rageShaderClass, ShaderWrapper::rb_alloc);

			rb_define_method(rb_rageShaderClass, "initialize", RFUNC(ShaderWrapper::rb_initialize), 1);
			rb_define_method(rb_rageShaderClass, "bindBitmap", RFUNC(ShaderWrapper::rb_bind_texture), 2);
			rb_define_method(rb_rageShaderClass, "setFloat", RFUNC(ShaderWrapper::rb_set_float), 2);
			rb_define_method(rb_rageShaderClass, "setInt", RFUNC(ShaderWrapper::rb_set_int), 2);
			rb_define_method(rb_rageShaderClass, "dispose", RFUNC(ShaderWrapper::rb_dispose), 0);
			rb_define_method(rb_rageShaderClass, "disposed?", RFUNC(ShaderWrapper::rb_is_disposed), 0);
		}

		VALUE ShaderWrapper::get_ruby_class()
		{
			return rb_rageShaderClass;
		}

		VALUE ShaderWrapper::new_ruby_class_instance()
		{
			return rb_class_new_instance(0, NULL, rb_rageShaderClass);
		}
	}
}