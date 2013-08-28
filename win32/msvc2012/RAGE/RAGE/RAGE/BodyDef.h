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
#include "PhObject.h"

namespace RAGE
{
	namespace Physics
	{
		class BodyDef : public PhObject
		{
		public:
			b2BodyDef *bd;
			BodyDef(void);
			void initialize(void);
			b2BodyType get_body_type(void);
			void set_body_type(b2BodyType type);
			VALUE get_position(void);
			void set_position(b2Vec2 *vec);
			float32 get_angle(void);
			void set_angle(float32 angle);
			VALUE get_linear_velocity(void);
			void set_linear_velocity(b2Vec2 *vec);
			float32 get_gravity_scale(void);
			void set_gravity_scale(float32 gravity_scale);
			float32 get_angular_velocity(void);
			void set_angular_velocity(float32 angular_velocity);
			float32 get_linear_damping(void);
			void set_linear_damping(float32 linear_damping);
			float32 get_angular_damping(void);
			void set_angular_damping(float32 angular_damping);
			bool get_allow_sleep(void);
			void set_allow_sleep(bool val);
			bool get_awake(void);
			void set_awake(bool val);
			bool get_fixed_rotation(void);
			void set_fixed_rotation(bool val);
			bool get_bullet(void);
			void set_bullet(bool val);
			bool get_active(void);
			void set_active(bool val);
			void physics_dispose(void);
			~BodyDef(void);
		};
	}
}
