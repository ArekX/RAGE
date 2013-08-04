#include "Shader.h"

namespace RAGE
{
	namespace Graphics
	{
		Shader::Shader(void)
		{
			disposed = false;
			code_added = false;
		}

		bool Shader::check_errors(GLint check)
		{
			GLint is_ok = 1;
			
			glGetShaderiv(glslhandle, check, &is_ok);

			if (is_ok == GL_FALSE)
			{
				PRINT(RAGE_SHADER_COMPILE_LINK_ERROR);

				GLint maxLength = 0;
				glGetShaderiv(glslhandle, GL_INFO_LOG_LENGTH, &maxLength);
 
				GLchar* strInfoLog = new GLchar[maxLength + 1];
				glGetShaderInfoLog(glslhandle, maxLength, &maxLength, strInfoLog);

				PRINT(strInfoLog);

				delete[] strInfoLog;

				return true;
			}

			return false;
		}

		void Shader::set_code(int shader_type, const char *code)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (code_added)
			{
				glDetachObjectARB(glslhandle, glsl_shader_program);
				glDeleteObjectARB(glsl_shader_program);
			}

			if (shader_type == RAGE_FRAGMENT_SHADER)
			{
				if (!al_have_opengl_extension("GL_ARB_fragment_shader"))
				{
					rb_raise(rb_eException, RAGE_ERROR_NO_EXT_FRAGMENT_SHADERS);
					return;
				}
				
				glslhandle = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
			}

			if (shader_type == RAGE_VERTEX_SHADER)
			{
				if (!al_have_opengl_extension("GL_ARB_vertex_shader"))
				{
					rb_raise(rb_eException, RAGE_ERROR_NO_EXT_FRAGMENT_SHADERS);
					return;
				}

				glslhandle = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
			}
			
			
			glsl_shader_program = glCreateProgramObjectARB();
			glShaderSourceARB(glslhandle, SHADER_LEN, (const char**)&code, NULL);
			glCompileShaderARB(glslhandle);

			if (check_errors(GL_COMPILE_STATUS))
			{
				code_added = true;
				return;
			}

			
			glAttachObjectARB(glsl_shader_program, glslhandle);
			glLinkProgramARB(glsl_shader_program);
			check_errors(GL_LINK_STATUS);

			code_added = true;
		}

		void Shader::attach_shader(Shader *src)
		{
			glAttachObjectARB(glsl_shader_program, src->glslhandle);
			glLinkProgramARB(glsl_shader_program);
			check_errors(GL_LINK_STATUS);
			glDetachObjectARB(glsl_shader_program, src->glslhandle);

			check_errors(GL_LINK_STATUS);
		}

		void Shader::bind_bitmap(char *texture_name, ALLEGRO_BITMAP *bitmap)
		{
			RAGE_CHECK_DISPOSED(disposed);

			glUniform1iARB(glGetUniformLocationARB(glsl_shader_program, texture_name),
				           al_get_opengl_texture(bitmap));
		}

		void Shader::set_float(char *name, float val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			glUniform1fARB(glGetUniformLocationARB(glsl_shader_program, (const char*)name), val);
		}

		void Shader::set_int(char *name, int val)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			glUniform1iARB(glGetUniformLocationARB(glsl_shader_program, (const char*)name), val);
		}

		void Shader::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (code_added)
			{
				glDetachObjectARB(glslhandle, glsl_shader_program);
				glDeleteObjectARB(glsl_shader_program);
			}

			if (is_active)
				glUseProgramObjectARB(0);
			
		}

		Shader::~Shader(void)
		{
			if (!disposed)
				dispose();
		}
	}
}