#pragma once

#include "RubyInterpreter.h"

#define SHADER_LEN 1

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
			void attach_shader(Shader *src);
			bool check_errors(GLint check);
			void dispose(void);
			Shader(void);
			~Shader(void);
		};

	}
}