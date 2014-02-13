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

#include "Shader.h"
#include "Bitmap.h"
#include "Shader_Wrapper.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_BITMAP && RAGE_COMPILE_SHADER

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
			delete value;
		}

		VALUE ShaderWrapper::rb_initialize(VALUE self, VALUE type, VALUE code)
		{
			Shader *sh;

			Data_Get_Struct(self, Shader, sh);

			sh->set_code(FIX2INT(type), StringValueCStr(code));

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

		VALUE ShaderWrapper::rb_set_iv2(int argc, VALUE *args, VALUE self)
		{
			if ((argc > 1) && (argc < 4))
			{
				Shader *sh;
				Data_Get_Struct(self, Shader, sh);

				sh->set_ivec2(
					          StringValueCStr(args[0]), argc - 1, 
					          FIX2INT(args[1]), 
							  (argc == 3) ? FIX2INT(args[2]) : 0  
							 );
			}
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 3);

			return Qnil;
		}

		VALUE ShaderWrapper::rb_set_iv3(int argc, VALUE *args, VALUE self)
		{
			if ((argc > 1) && (argc < 5))
			{
				Shader *sh;
				Data_Get_Struct(self, Shader, sh);

				sh->set_ivec3(
					          StringValueCStr(args[0]), argc - 1, 
					          FIX2INT(args[1]), 
							  (argc > 2) ? FIX2INT(args[2]) : 0,
							  (argc == 4) ? FIX2INT(args[3]) : 0
							 );
			}
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 4);

			return Qnil;
		}

		VALUE ShaderWrapper::rb_set_iv4(int argc, VALUE *args, VALUE self)
		{
			if ((argc > 1) && (argc < 6))
			{
				Shader *sh;
				Data_Get_Struct(self, Shader, sh);

				sh->set_ivec4(
					          StringValueCStr(args[0]), argc - 1, 
					          FIX2INT(args[1]), 
							  (argc > 2) ? FIX2INT(args[2]) : 0,
							  (argc > 3) ? FIX2INT(args[3]) : 0,
							  (argc == 5) ? FIX2INT(args[4]) : 0
							 );
			}
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 5);

			return Qnil;
		}

		VALUE ShaderWrapper::rb_set_fv2(int argc, VALUE *args, VALUE self)
		{
			if ((argc > 1) && (argc < 4))
			{
				Shader *sh;
				Data_Get_Struct(self, Shader, sh);

				sh->set_fvec2(
					          StringValueCStr(args[0]), argc - 1, 
					          NUM2DBL(args[1]), 
							  (argc == 3) ? NUM2DBL(args[2]) : 0  
							 );
			}
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 3);

			return Qnil;
		}

		VALUE ShaderWrapper::rb_set_fv3(int argc, VALUE *args, VALUE self)
		{
			if ((argc > 1) && (argc < 5))
			{
				Shader *sh;
				Data_Get_Struct(self, Shader, sh);

				sh->set_fvec3(
					          StringValueCStr(args[0]), argc - 1, 
					          NUM2DBL(args[1]), 
							  (argc > 2) ? NUM2DBL(args[2]) : 0,
							  (argc == 4) ? NUM2DBL(args[3]) : 0
							 );
			}
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 4);

			return Qnil;
		}

		VALUE ShaderWrapper::rb_set_fv4(int argc, VALUE *args, VALUE self)
		{
			if ((argc > 1) && (argc < 6))
			{
				Shader *sh;
				Data_Get_Struct(self, Shader, sh);

				sh->set_fvec4(
					          StringValueCStr(args[0]), argc - 1, 
					          NUM2DBL(args[1]), 
							  (argc > 2) ? NUM2DBL(args[2]) : 0,
							  (argc > 3) ? NUM2DBL(args[3]) : 0,
							  (argc == 5) ? NUM2DBL(args[4]) : 0
							 );
			}
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 5);

			return Qnil;
		}

		VALUE ShaderWrapper::rb_set_mat(int argc, VALUE *args, VALUE self)
		{
			if (argc == 4)
			{
				VALUE mat = args[3];

				if (TYPE(mat) != T_ARRAY)
				{
					rb_raise(rb_eArgError, RAGE_ERROR_SHADER_ARG_NOT_ARY);
					return Qnil;
				}

				int max_elements = RARRAY_LEN(mat);
				float *f = new float[max_elements];

				for (int i = 0; i < max_elements; i++)
					f[i] = NUM2DBL(rb_ary_entry(mat, i));

				Shader *sh;
				Data_Get_Struct(self, Shader, sh);

				sh->set_mat(StringValueCStr(args[0]), FIX2INT(args[1]), max_elements, FIX2INT(args[2]), f);

				delete[] f;
			}
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 4, 4);

			return Qnil;
		}

		VALUE ShaderWrapper::rb_attach_shader(VALUE self, VALUE shader)
		{
			Shader *sh_self, *sh_shader;
			Data_Get_Struct(self, Shader, sh_self);
			Data_Get_Struct(self, Shader, sh_shader);

			sh_self->attach_shader(sh_shader);

			return Qnil;
		}

		void ShaderWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Shader")) return;

			VALUE rage = rb_define_module("RAGE");
			
			VALUE g = rb_define_module_under(rage, "Graphics");

			rb_define_const(g, "FRAGMENT_SHADER", INT2FIX(RAGE_FRAGMENT_SHADER));
			rb_define_const(g, "VERTEX_SHADER", INT2FIX(RAGE_VERTEX_SHADER));
			rb_define_const(g, "SHADER_MATRIX_2X2", INT2FIX(RAGE_SHADER_MATRIX_2X2));
			rb_define_const(g, "SHADER_MATRIX_3X3", INT2FIX(RAGE_SHADER_MATRIX_3X3));
			rb_define_const(g, "SHADER_MATRIX_4X4", INT2FIX(RAGE_SHADER_MATRIX_4X4));
			rb_define_const(g, "SHADER_MATRIX_2X3", INT2FIX(RAGE_SHADER_MATRIX_2X3));
			rb_define_const(g, "SHADER_MATRIX_3X2", INT2FIX(RAGE_SHADER_MATRIX_3X2));
			rb_define_const(g, "SHADER_MATRIX_2X4", INT2FIX(RAGE_SHADER_MATRIX_2X4));
			rb_define_const(g, "SHADER_MATRIX_4X2", INT2FIX(RAGE_SHADER_MATRIX_4X2));
			rb_define_const(g, "SHADER_MATRIX_3X4", INT2FIX(RAGE_SHADER_MATRIX_3X4));
			rb_define_const(g, "SHADER_MATRIX_4X3", INT2FIX(RAGE_SHADER_MATRIX_3X4));

			rb_rageShaderClass = rb_define_class_under(rage, "Shader", rb_cObject);

			rb_define_alloc_func(rb_rageShaderClass, ShaderWrapper::rb_alloc);

			rb_define_method(rb_rageShaderClass, "initialize", RFUNC(ShaderWrapper::rb_initialize), 2);
			rb_define_method(rb_rageShaderClass, "bindBitmap", RFUNC(ShaderWrapper::rb_bind_texture), 2);
			rb_define_method(rb_rageShaderClass, "setFloat", RFUNC(ShaderWrapper::rb_set_float), 2);
			rb_define_method(rb_rageShaderClass, "setInt", RFUNC(ShaderWrapper::rb_set_int), 2);
			rb_define_method(rb_rageShaderClass, "setIntVector2", RFUNC(ShaderWrapper::rb_set_iv2), -1);
			rb_define_method(rb_rageShaderClass, "setIntVector3", RFUNC(ShaderWrapper::rb_set_iv3), -1);
			rb_define_method(rb_rageShaderClass, "setIntVector4", RFUNC(ShaderWrapper::rb_set_iv4), -1);
			rb_define_method(rb_rageShaderClass, "setFloatVector2", RFUNC(ShaderWrapper::rb_set_fv2), -1);
			rb_define_method(rb_rageShaderClass, "setFloatVector3", RFUNC(ShaderWrapper::rb_set_fv3), -1);
			rb_define_method(rb_rageShaderClass, "setFloatVector4", RFUNC(ShaderWrapper::rb_set_fv4), -1);
			rb_define_method(rb_rageShaderClass, "setMatrix", RFUNC(ShaderWrapper::rb_set_mat), -1);
			rb_define_method(rb_rageShaderClass, "attachShader", RFUNC(ShaderWrapper::rb_attach_shader), 1);
			rb_define_method(rb_rageShaderClass, "dispose", RFUNC(ShaderWrapper::rb_dispose), 0);
			rb_define_method(rb_rageShaderClass, "disposed?", RFUNC(ShaderWrapper::rb_is_disposed), 0);
		}

		VALUE ShaderWrapper::get_ruby_class(void)
		{
			return rb_rageShaderClass;
		}

		VALUE ShaderWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, nullptr, rb_rageShaderClass);
		}
	}
}

#endif