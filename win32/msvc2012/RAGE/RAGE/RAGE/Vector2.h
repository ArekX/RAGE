#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_PHYSICS

#include "box2d-mod\Common\b2Math.h"

namespace RAGE
{
	namespace Physics
	{
		class Vector2
		{
		public:
			b2Vec2 *vec = nullptr;
			bool disposed = false;
			Vector2();
			~Vector2();
		};
	}
}

#endif


