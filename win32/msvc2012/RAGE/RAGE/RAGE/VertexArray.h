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

namespace RAGE
{
	namespace Graphics
	{
		class VertexArray
		{
		public:
			bool disposed;
			ALLEGRO_VERTEX *ary;
			int64_t ary_len;
			VertexArray(void);
			void initialize(int64_t vertices_count);
			void add_vertex(float x, float y, float z, float u, float v, ALLEGRO_COLOR color);
			void change_vertex(int64_t index, float x, float y, float z, float u, float v, ALLEGRO_COLOR color);
			void remove_vertex(int64_t index);
			float get_vertex_x(int64_t index);
			float get_vertex_y(int64_t index);
			float get_vertex_z(int64_t index);
			float get_vertex_u(int64_t index);
			float get_vertex_v(int64_t index);
			void set_vertex_x(int64_t index, float x);
			void set_vertex_y(int64_t index, float y);
			void set_vertex_z(int64_t index, float z);
			void set_vertex_u(int64_t index, float u);
			void set_vertex_v(int64_t index, float v);
			void set_vertex_color(int64_t index, ALLEGRO_COLOR color);
			void clear_array(void);
			ALLEGRO_COLOR get_vertex_color(int64_t index);
			void dispose(void);
			~VertexArray(void);
		};
	}
}
