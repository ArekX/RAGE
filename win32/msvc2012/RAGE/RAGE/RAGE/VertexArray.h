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
