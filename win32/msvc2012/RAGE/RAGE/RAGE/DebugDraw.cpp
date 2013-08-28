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

#include "DebugDraw.h"

namespace RAGE
{
	namespace Physics
	{
		DebugDraw::DebugDraw(void)
		{
			alpha = 1;
			line_width = 2;

			ALLEGRO_VERTEX_ELEMENT elems[] = {
				 {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_2, offsetof(DEBUG_VERTEX, x)},
				 {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(DEBUG_VERTEX, color)},
				 {0, 0, 0}
			  };

			decl = al_create_vertex_decl(elems, sizeof(DEBUG_VERTEX));
		}

		void DebugDraw::draw_poly(const b2Vec2* vertices, int32 vertexCount, ALLEGRO_COLOR cl, int type)
		{
			DEBUG_VERTEX *v = new DEBUG_VERTEX[vertexCount];

			for (int32 i = 0; i < vertexCount; i++)
			{
				v[i].x = vertices[i].x;
				v[i].y = vertices[i].y;
				v[i].color = cl;
			}

			al_set_target_backbuffer(RAGE::Graphics::GraphicsWrappers::get_display());
			
			al_draw_prim(v, decl, NULL, 0, vertexCount, type);
			RAGE::Graphics::GraphicsWrappers::restore_drawing_target();

			delete[] v;
		}

		void DebugDraw::set_debug_opacity(float s_alpha)
		{
			if (alpha > 1)
				alpha = 1;
			else if (alpha < 0)
				alpha = 0;
			else
				alpha = s_alpha;
		}

		float32 DebugDraw::get_debug_opacity(void)
		{
			return alpha;
		}

		void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
		{
			glLineWidth(line_width);
			draw_poly(vertices, vertexCount, al_map_rgba_f(color.r, color.g, color.b, alpha), ALLEGRO_PRIM_LINE_LOOP);
		}

		void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
		{
			draw_poly(vertices, vertexCount, al_map_rgba_f(color.r, color.g, color.b, alpha), ALLEGRO_PRIM_TRIANGLE_FAN);
		}

		void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
		{

			al_set_target_backbuffer(RAGE::Graphics::GraphicsWrappers::get_display());
			al_draw_circle(center.x, center.y, radius, al_map_rgba_f(color.r, color.g, color.b, alpha), line_width);
			RAGE::Graphics::GraphicsWrappers::restore_drawing_target();

		}

		void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
		{

			al_set_target_backbuffer(RAGE::Graphics::GraphicsWrappers::get_display());
			al_draw_filled_circle(center.x, center.y, radius, al_map_rgba_f(color.r, color.g, color.b, alpha));
			RAGE::Graphics::GraphicsWrappers::restore_drawing_target();
		}

		void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
		{

			al_set_target_backbuffer(RAGE::Graphics::GraphicsWrappers::get_display());
			al_draw_line(p1.x, p1.y, p2.x, p2.y, al_map_rgba_f(color.r, color.g, color.b, alpha), line_width);
			RAGE::Graphics::GraphicsWrappers::restore_drawing_target();
		}

		void DebugDraw::DrawTransform(const b2Transform& xf)
		{

			b2Vec2 p1 = xf.p, p2;
			const float32 k_axisScale = 0.4f;

			p2 = p1 + k_axisScale * xf.q.GetXAxis();
			DrawSegment(p1, p2, b2Color(1, 0, 0));

			p2 = p1 + k_axisScale * xf.q.GetYAxis();
			DrawSegment(p1, p2, b2Color(0, 1, 0));
		}

		DebugDraw::~DebugDraw(void)
		{
			al_destroy_vertex_decl(decl);
		}
	}
}