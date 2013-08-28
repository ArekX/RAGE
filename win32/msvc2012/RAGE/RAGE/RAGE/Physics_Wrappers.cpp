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

#include "Physics_Wrappers.h"

namespace RAGE
{
	namespace Physics
	{
		void PhysicsWrappers::load_wrappers(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Physics")) return;

			VALUE rage = rb_define_module("RAGE");
			VALUE physics = rb_define_module_under(rage, "Physics");

			rb_define_const(physics, "STATIC_BODY_TYPE", INT2FIX(b2BodyType::b2_staticBody));
			rb_define_const(physics, "KINEMATIC_BODY_TYPE", INT2FIX(b2BodyType::b2_kinematicBody));
			rb_define_const(physics, "DYNAMIC_BODY_TYPE", INT2FIX(b2BodyType::b2_dynamicBody));
			
			rb_define_const(physics, "DEBUG_DRAW_SHAPES", INT2FIX(b2Draw::e_shapeBit));
			rb_define_const(physics, "DEBUG_DRAW_JOINTS", INT2FIX(b2Draw::e_jointBit));
			rb_define_const(physics, "DEBUG_DRAW_PAIRS", INT2FIX(b2Draw::e_pairBit));
			rb_define_const(physics, "DEBUG_DRAW_CENTER_OF_MASS", INT2FIX(b2Draw::e_centerOfMassBit));
			rb_define_const(physics, "DEBUG_DRAW_AABB", INT2FIX(b2Draw::e_aabbBit));
			rb_define_const(physics, "DEBUG_DRAW_ALL", INT2FIX(31));
		}
	}
}
