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

#include "Shader.h"

#if RAGE_COMPILE_SHADER

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
				glDetachShader(glslhandle, glsl_shader_program);
				glDeleteProgram(glsl_shader_program);
			}

			bool available = al_have_opengl_extension("GL_ARB_shader_objects") && 
				            (al_have_opengl_extension("GL_ARB_vertex_shader") || 
							al_have_opengl_extension("GL_ARB_fragment_shader")) && 
							al_have_opengl_extension("GL_ARB_shading_language_100");

			if (!available)
			{
				rb_raise(rb_eException, RAGE_ERROR_NO_EXT_FRAGMENT_SHADERS);
				return;
			}

			if (shader_type == RAGE_FRAGMENT_SHADER)
				glslhandle = glCreateShader(GL_FRAGMENT_SHADER_ARB);
			

			if (shader_type == RAGE_VERTEX_SHADER)
				glslhandle = glCreateShader(GL_VERTEX_SHADER_ARB);

			glsl_shader_program = glCreateProgramObjectARB();
			glShaderSource(glslhandle, SHADER_LEN, (const char**)&code, NULL);
			glCompileShader(glslhandle);

			if (check_errors(GL_COMPILE_STATUS))
			{
				code_added = true;
				return;
			}

			
			glAttachShader(glsl_shader_program, glslhandle);
			glLinkProgram(glsl_shader_program);
			check_errors(GL_LINK_STATUS);

			code_added = true;
		}

		void Shader::attach_shader(Shader *src)
		{
			glAttachShader(glsl_shader_program, src->glslhandle);
			glLinkProgram(glsl_shader_program);
			check_errors(GL_LINK_STATUS);
			glDetachShader(glsl_shader_program, src->glslhandle);

			check_errors(GL_LINK_STATUS);
		}

		void Shader::bind_bitmap(char *texture_name, ALLEGRO_BITMAP *bitmap)
		{
			RAGE_CHECK_DISPOSED(disposed);

			glUniform1i(glGetUniformLocation(glsl_shader_program, texture_name),
				           al_get_opengl_texture(bitmap));
		}

		void Shader::set_float(char *name, float val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			glUniform1f(glGetUniformLocation(glsl_shader_program, (const char*)name), val);
		}

		void Shader::set_int(char *name, int val)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			glUniform1i(glGetUniformLocation(glsl_shader_program, (const char*)name), val);
		}

		void Shader::set_ivec2(char *name, int max_val, int val1, int val2)
		{
			RAGE_CHECK_DISPOSED(disposed);

			GLint g[2] = { val1, val2 };

			glUniform2iv(glGetUniformLocation(glsl_shader_program, (const char*)name), max_val, g);

		}

		void Shader::set_ivec3(char *name, int max_val, int val1, int val2, int val3)
		{
			RAGE_CHECK_DISPOSED(disposed);

			GLint g[3] = { val1, val2, val3 };

			glUniform3iv(glGetUniformLocation(glsl_shader_program, (const char*)name), max_val, g);
		}

		void Shader::set_ivec4(char *name, int max_val, int val1, int val2, int val3, int val4)
		{
			RAGE_CHECK_DISPOSED(disposed);

			GLint g[4] = { val1, val2, val3, val4 };

			glUniform4iv(glGetUniformLocation(glsl_shader_program, (const char*)name), max_val, g);
		}

		void Shader::set_fvec2(char *name, int max_val, float val1, float val2)
		{
			RAGE_CHECK_DISPOSED(disposed);

			GLfloat g[2] = { val1, val2 };

			glUniform2fv(glGetUniformLocation(glsl_shader_program, (const char*)name), max_val, g);
		}

		void Shader::set_fvec3(char *name, int max_val, float val1, int val2, int val3)
		{
			RAGE_CHECK_DISPOSED(disposed);

			GLfloat g[3] = { val1, val2, val3 };

			glUniform2fv(glGetUniformLocation(glsl_shader_program, (const char*)name), max_val, g);
		}

		void Shader::set_fvec4(char *name, int max_val, float val1, float val2, float val3, float val4)
		{
			RAGE_CHECK_DISPOSED(disposed);

			GLfloat g[4] = { val1, val2, val3, val4 };

			glUniform4fv(glGetUniformLocation(glsl_shader_program, (const char*)name), max_val, g);
		}

		void Shader::set_mat(char *name, int mat_type, int count, bool transpose, float *vals)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(mat_type)
			{
				case RAGE_SHADER_MATRIX_2X2:
					glUniformMatrix2fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_3X3:
					glUniformMatrix3fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_4X4:
					glUniformMatrix4fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_2X3:
					glUniformMatrix2x3fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_3X2:
					glUniformMatrix3x2fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_2X4:
					glUniformMatrix2x4fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_4X2:
					glUniformMatrix4x2fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_3X4:
					glUniformMatrix3x4fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
					break;
				case RAGE_SHADER_MATRIX_4X3:
					glUniformMatrix4x3fv(glGetUniformLocation(glsl_shader_program, (const char*)name), count, transpose, vals);
			}
		}

		void Shader::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (code_added)
			{
				glDetachShader(glslhandle, glsl_shader_program);
				glDeleteProgram(glsl_shader_program);
			}

			if (is_active)
				glUseProgram(0);
			
		}

		Shader::~Shader(void)
		{
			if (!disposed)
				dispose();
		}
	}
}

#endif