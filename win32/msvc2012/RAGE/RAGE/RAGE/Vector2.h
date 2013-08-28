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
#include "Box2D.h"
#include "PhObject.h"

namespace RAGE
{
	namespace Physics
	{
		class Vector2 : public PhObject
		{
		public:
			b2Vec2 *vec;
			Vector2(void);
			void initialize(void);
			void initialize(float32 x, float32 y);
			float32 length(void);
			float32 length_squared(void);
			bool is_valid(void);
			float32 normalize(void);
			void skew(b2Vec2 *set);
			void set_zero(void);
			void set(float32 x, float32 y);
			void set_x(float32 new_x);
			void set_y(float32 new_y);
			void add(b2Vec2 *other_vec);
			void sub(b2Vec2 *other_vec);
			void mul(float32 val);
			void negate(void);
			void physics_dispose(void);
			float32 get_x(void);
			float32 get_y(void);
			~Vector2(void);
		};
	}
}