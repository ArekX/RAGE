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
			uint64_t ary_len;
			VertexArray(void);
			void initialize(int vertices_count);
			void add_vertex(float x, float y, float z, float u, float v, ALLEGRO_COLOR color);
			void change_vertex(uint64_t index, float x, float y, float z, float u, float v, ALLEGRO_COLOR color);
			void remove_vertex(uint64_t index);
			float get_vertex_x(uint64_t index);
			float get_vertex_y(uint64_t index);
			float get_vertex_z(uint64_t index);
			float get_vertex_u(uint64_t index);
			float get_vertex_v(uint64_t index);
			void set_vertex_x(uint64_t index, float x);
			void set_vertex_y(uint64_t index, float y);
			void set_vertex_z(uint64_t index, float z);
			void set_vertex_u(uint64_t index, float u);
			void set_vertex_v(uint64_t index, float v);
			void set_vertex_color(uint64_t index, ALLEGRO_COLOR color);
			void clear_array(void);
			ALLEGRO_COLOR get_vertex_color(uint64_t index);
			void dispose(void);
			~VertexArray(void);
		};
	}
}
