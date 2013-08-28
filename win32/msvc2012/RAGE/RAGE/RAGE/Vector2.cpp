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

#include "Vector2.h"

namespace RAGE
{
	namespace Physics
	{
		Vector2::Vector2(void)
		{
			vec = NULL;
		}


		void Vector2::initialize(void)
		{
			vec = new b2Vec2();
		}

		void Vector2::initialize(float x, float y)
		{
			vec = new b2Vec2(x, y);
		}

		float32 Vector2::length(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return vec->Length();
		}

		float32 Vector2::length_squared(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return vec->LengthSquared();
		}

		bool Vector2::is_valid(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return vec->IsValid();
		}

		void Vector2::set_zero(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			vec->SetZero();
		}

		void Vector2::set(float32 x, float32 y)
		{
			RAGE_CHECK_DISPOSED(disposed);

			vec->Set(x, y);
		}

		void Vector2::set_x(float32 new_x)
		{
			RAGE_CHECK_DISPOSED(disposed);

			vec->x = new_x;
		}

		void Vector2::set_y(float32 new_y)
		{
			RAGE_CHECK_DISPOSED(disposed);

			vec->y = new_y;
		}

		float32 Vector2::get_x(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return vec->x;
		}

		float32 Vector2::get_y(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return vec->y;
		}

		void Vector2::add(b2Vec2 *other_vec)
		{
			RAGE_CHECK_DISPOSED(disposed);

			*vec += *other_vec;
		}

		void Vector2::sub(b2Vec2 *other_vec)
		{
			RAGE_CHECK_DISPOSED(disposed);

			*vec -= *other_vec;
		}

		void Vector2::mul(float32 val)
		{
			RAGE_CHECK_DISPOSED(disposed);

			*vec *= val;
		}

		void Vector2::negate(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			*vec = -(*vec);
		}

		float32 Vector2::normalize(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return vec->Normalize();
		}

		void Vector2::skew(b2Vec2 *set)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (set != NULL)
			{
				set->x = -vec->y;
				set->y = vec->x;
			}
		}

		void Vector2::physics_dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			delete vec;

			vec = NULL;
		}

		Vector2::~Vector2(void)
		{
			
		}
	}
}
