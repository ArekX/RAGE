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

#include "BodyDef.h"

namespace RAGE
{
	namespace Physics
	{
		BodyDef::BodyDef(void)
		{
			bd = NULL;
		}

		void BodyDef::initialize(void)
		{
			bd = new b2BodyDef();
		}

		b2BodyType BodyDef::get_body_type(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, b2BodyType::b2_staticBody);

			return bd->type;
		}

		void BodyDef::set_body_type(b2BodyType type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->type = type;
		}

		VALUE BodyDef::get_position(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			VALUE new_vec = RAGE::Physics::Vector2Wrapper::new_ruby_class_instance();

			RAGE_GET_DATA(new_vec, Vector2, v2);

			delete v2->vec;
			v2->vec = &(bd->position);
			v2->add_dependency();

			return new_vec;
		}

		void BodyDef::set_position(b2Vec2 *vec)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->position.x = vec->x;
			bd->position.y = vec->y;
		}

		float32 BodyDef::get_angle(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return bd->angle;
		}

		void BodyDef::set_angle(float32 angle)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->angle = angle;
		}

		VALUE BodyDef::get_linear_velocity(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			VALUE new_vec = RAGE::Physics::Vector2Wrapper::new_ruby_class_instance();

			RAGE_GET_DATA(new_vec, Vector2, v2);

			delete v2->vec;
			v2->vec = &(bd->position);
			v2->add_dependency();

			return new_vec;
		}

		void BodyDef::set_linear_velocity(b2Vec2 *vec)
		{
			RAGE_CHECK_DISPOSED(disposed);

			vec->x = bd->linearVelocity.x;
			vec->y = bd->linearVelocity.y;
		}

		float32 BodyDef::get_gravity_scale(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return bd->gravityScale;
		}

		void BodyDef::set_gravity_scale(float32 gravity_scale)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->gravityScale = gravity_scale;
		}

		float32 BodyDef::get_angular_velocity(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return bd->angularVelocity;
		}

		void BodyDef::set_angular_velocity(float32 angular_velocity)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->angularVelocity = angular_velocity;
		}

		float32 BodyDef::get_linear_damping(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return bd->linearDamping;
		}

		void BodyDef::set_linear_damping(float32 linear_damping)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->linearDamping = linear_damping;
		}

		float32 BodyDef::get_angular_damping(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return bd->angularDamping;
		}

		void BodyDef::set_angular_damping(float32 angular_damping)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->angularDamping = angular_damping;
		}

		bool BodyDef::get_allow_sleep(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return bd->allowSleep;
		}

		void BodyDef::set_allow_sleep(bool val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->allowSleep = val;
		}

		bool BodyDef::get_awake(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return bd->awake;
		}

		void BodyDef::set_awake(bool val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->awake = val;
		}

		bool BodyDef::get_fixed_rotation(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return bd->fixedRotation;
		}

		void BodyDef::set_fixed_rotation(bool val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->fixedRotation = val;
		}

		bool BodyDef::get_bullet(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return bd->bullet;
		}

		void BodyDef::set_bullet(bool val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->bullet = val;
		}

		bool BodyDef::get_active(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return bd->active;
		}

		void BodyDef::set_active(bool val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			bd->active = val;
		}

		void BodyDef::physics_dispose(void)
		{
			delete bd;

			bd = NULL;
		}

		BodyDef::~BodyDef(void)
		{
			if (!disposed)
				dispose();
		}
	}
}
