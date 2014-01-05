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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_SHADER

#define SHADER_LEN 1
#define RAGE_FRAGMENT_SHADER 1
#define RAGE_VERTEX_SHADER 2

#define RAGE_SHADER_MATRIX_2X2 0
#define RAGE_SHADER_MATRIX_3X3 1
#define RAGE_SHADER_MATRIX_4X4 2
#define RAGE_SHADER_MATRIX_2X3 3
#define RAGE_SHADER_MATRIX_3X2 4
#define RAGE_SHADER_MATRIX_2X4 5
#define RAGE_SHADER_MATRIX_4X2 6
#define RAGE_SHADER_MATRIX_3X4 7
#define RAGE_SHADER_MATRIX_4X3 8

namespace RAGE
{
	namespace Graphics
	{

		class Shader
		{
		public:
			GLhandleARB glslhandle;
			GLhandleARB glsl_shader_program;
			bool disposed;
			bool code_added;
			bool is_active;
			void set_code(int shader_type, const char *code);
			void bind_bitmap(char *texture_name, ALLEGRO_BITMAP *bitmap);
			
			void set_float(char *name, float val);
			void set_int(char *name, int val);
			void set_ivec2(char *name, int max_val, int val1, int val2);
			void set_ivec3(char *name, int max_val, int val1, int val2, int val3);
			void set_ivec4(char *name, int max_val, int val1, int val2, int val3, int val4);
			void set_fvec2(char *name, int max_val, float val1, float val2);
			void set_fvec3(char *name, int max_val, float val1, int val2, int val3);
			void set_fvec4(char *name, int max_val, float val1, float val2, float val3, float val4);

			void set_mat(char *name, int mat_type, int count, bool transpose, float *vals); 

			void attach_shader(Shader *src);
			bool check_errors(GLint check);
			void dispose(void);
			Shader(void);
			~Shader(void);
		};

	}
}

#endif