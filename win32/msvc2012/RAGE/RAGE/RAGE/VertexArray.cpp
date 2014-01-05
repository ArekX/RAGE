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

#include "VertexArray.h"

#if RAGE_COMPILE_VERTEX_ARRAY

namespace RAGE
{
	namespace Graphics
	{

		VertexArray::VertexArray(void)
		{
			disposed = false;
		}

		void VertexArray::initialize(int64_t vertices_count)
		{
			if (vertices_count < 0) vertices_count = 0;

			if (vertices_count > 0)
				ary = (ALLEGRO_VERTEX*)al_malloc(sizeof(ALLEGRO_VERTEX) * vertices_count);
			else
				ary = nullptr;

			ary_len = vertices_count;
		}

		void VertexArray::add_vertex(float x, float y, float z, float u, float v, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ary == nullptr)
				ary = (ALLEGRO_VERTEX*)al_malloc(sizeof(ALLEGRO_VERTEX) * ++ary_len);
			else
				ary = (ALLEGRO_VERTEX*)al_realloc(ary, sizeof(ALLEGRO_VERTEX) * ++ary_len);
			
			ary[ary_len - 1].x = x;
			ary[ary_len - 1].y = y;
			ary[ary_len - 1].z = z;
			ary[ary_len - 1].u = u;
			ary[ary_len - 1].v = v;
			ary[ary_len - 1].color = color;
		}

		void VertexArray::change_vertex(int64_t index, float x, float y, float z, float u, float v, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);


			if ((index < 0) || (index >= ary_len)) return;

			ary[index].x = x;
			ary[index].y = y;
			ary[index].z = z;
			ary[index].u = u;
			ary[index].v = v;
			ary[index].color = color;
		}

		void VertexArray::remove_vertex(int64_t index)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((index < 0) || (index >= ary_len)) 

			if (index != (ary_len - 1))
			{
				for(int64_t i = index; i < ary_len - 1; i++)
					ary[i] = ary[i + 1];
				
			}

			ary = (ALLEGRO_VERTEX*)al_realloc(ary, sizeof(ALLEGRO_VERTEX) * --ary_len);
		}

		float VertexArray::get_vertex_x(int64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if ((index < 0) || (index >= ary_len))  return 0;

			return ary[index].x;
		}

		float VertexArray::get_vertex_y(int64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if ((index < 0) || (index >= ary_len))  return 0;

			return ary[index].y;
		}

		float VertexArray::get_vertex_z(int64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if ((index < 0) || (index >= ary_len))  return 0;

			return ary[index].z;
		}

		float VertexArray::get_vertex_u(int64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if ((index < 0) || (index >= ary_len))  return 0;

			return ary[index].u;
		}

		float VertexArray::get_vertex_v(int64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if ((index < 0) || (index >= ary_len))  return 0;

			return ary[index].v;
		}

		ALLEGRO_COLOR VertexArray::get_vertex_color(int64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, al_map_rgb(0, 0, 0));

			if ((index < 0) || (index >= ary_len))  return al_map_rgb(0, 0, 0);

			return ary[index].color;
		}

		void VertexArray::set_vertex_x(int64_t index, float x)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((index < 0) || (index >= ary_len))  return;

			ary[index].x = x;

		}
		void VertexArray::set_vertex_y(int64_t index, float y)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((index < 0) || (index >= ary_len))  return;

			ary[index].y = y;
		}
		void VertexArray::set_vertex_z(int64_t index, float z)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((index < 0) || (index >= ary_len))  return;

			ary[index].z = z;
		}
		void VertexArray::set_vertex_u(int64_t index, float u)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((index < 0) || (index >= ary_len))  return;

			ary[index].u = u;
		}

		void VertexArray::set_vertex_v(int64_t index, float v)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((index < 0) || (index >= ary_len))  return;

			ary[index].v = v;
		}
		void VertexArray::set_vertex_color(int64_t index, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((index < 0) || (index >= ary_len))  return;

			ary[index].color = color;
		}

		void VertexArray::clear_array(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_free(ary);

			ary_len = 0;
		}

		void VertexArray::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ary_len > 0) 
				al_free(ary);

			disposed = true;
		}

		VertexArray::~VertexArray(void)
		{
			if (!disposed)
				dispose();
		}

	}
}

#endif