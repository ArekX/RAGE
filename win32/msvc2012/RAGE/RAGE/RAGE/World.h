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
#include "Vector2_Wrapper.h"
#include "DebugDraw.h"
#include "PhObject.h"

namespace RAGE
{
	namespace Physics
	{
		// TODO: Needs to be finished. Make sure you use add_dependency

		class World : public PhObject
		{
		private:
			DebugDraw *debug;
			VALUE body_ary;
			VALUE g_vector;
		public:
			b2World *wld;
			World(void);
			void initialize(VALUE gravity_vector);
			VALUE get_gravity(void);
			void set_gravity(VALUE gravity);
			void draw_debug_objects(void);
			void setup_debug_draw_objects(int flags);
			VALUE create_body(b2BodyDef *def);
			void physics_dispose(void);
			void gc_mark(void);
			~World(void);
		};
	}
}