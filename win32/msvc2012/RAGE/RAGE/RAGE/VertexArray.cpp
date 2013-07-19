#include "VertexArray.h"

namespace RAGE
{
	namespace Graphics
	{

		VertexArray::VertexArray(void)
		{
			disposed = false;
		}

		void VertexArray::initialize(int vertices_count)
		{
			if (vertices_count < 0) vertices_count = 0;

			if (vertices_count > 0)
				ary = (ALLEGRO_VERTEX*)al_malloc(sizeof(ALLEGRO_VERTEX) * vertices_count);
			else
				ary = NULL;

			ary_len = vertices_count;
		}

		void VertexArray::add_vertex(float x, float y, float z, float u, float v, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ary == NULL)
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

		void VertexArray::change_vertex(uint64_t index, float x, float y, float z, float u, float v, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

			ary[index].x = x;
			ary[index].y = y;
			ary[index].z = z;
			ary[index].u = u;
			ary[index].v = v;
			ary[index].color = color;
		}

		void VertexArray::remove_vertex(uint64_t index)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

			if (index != (ary_len - 1))
			{
				for(uint64_t i = index; i < ary_len - 1; i++)
					ary[i] = ary[i + 1];
				
			}

			ary = (ALLEGRO_VERTEX*)al_realloc(ary, sizeof(ALLEGRO_VERTEX) * --ary_len);
		}

		float VertexArray::get_vertex_x(uint64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (index >= ary_len) return 0;

			return ary[index].x;
		}

		float VertexArray::get_vertex_y(uint64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (index >= ary_len) return 0;

			return ary[index].y;
		}

		float VertexArray::get_vertex_z(uint64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (index >= ary_len) return 0;

			return ary[index].z;
		}

		float VertexArray::get_vertex_u(uint64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (index >= ary_len) return 0;

			return ary[index].u;
		}

		float VertexArray::get_vertex_v(uint64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (index >= ary_len) return 0;

			return ary[index].v;
		}

		ALLEGRO_COLOR VertexArray::get_vertex_color(uint64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, al_map_rgb(0, 0, 0));

			if (index >= ary_len) return al_map_rgb(0, 0, 0);

			return ary[index].color;
		}

		void VertexArray::set_vertex_x(uint64_t index, float x)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

			ary[index].x = x;

		}
		void VertexArray::set_vertex_y(uint64_t index, float y)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

			ary[index].y = y;
		}
		void VertexArray::set_vertex_z(uint64_t index, float z)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

			ary[index].z = z;
		}
		void VertexArray::set_vertex_u(uint64_t index, float u)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

			ary[index].u = u;
		}

		void VertexArray::set_vertex_v(uint64_t index, float v)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

			ary[index].v = v;
		}
		void VertexArray::set_vertex_color(uint64_t index, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (index >= ary_len) return;

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