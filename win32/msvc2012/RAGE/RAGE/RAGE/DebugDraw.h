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
#include "box2d-mod/Box2D.h"

#if RAGE_COMPILE_PHYSICS && RAGE_COMPILE_PHYS_DEBUG_DRAW

namespace RAGE
{
	namespace Physics
	{

		typedef struct
		{
		   float32 x, y;
		   ALLEGRO_COLOR color;
		} DEBUG_VERTEX;

		class DebugDraw : public b2Draw
		{
		private:
			void draw_poly(const b2Vec2* vertices, int32 vertexCount, ALLEGRO_COLOR cl, int type);
			float32 alpha;
			float32 line_width;
			ALLEGRO_VERTEX_DECL *decl;
		public:
			DebugDraw(void);
			void set_debug_opacity(float s_alpha);
			float32 get_debug_opacity(void);
			void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
			void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
			void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
			void DrawTransform(const b2Transform& xf);
			~DebugDraw(void);
		};

	}
}

#endif