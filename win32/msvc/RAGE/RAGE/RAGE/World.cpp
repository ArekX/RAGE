#include "World.h"
#include "Vector2.h"

#if RAGE_COMPILE_PHYSICS

namespace RAGE
{
	namespace Physics
	{
		World::World()
		{
		}


		World::~World()
		{
			if (!disposed)
				dispose();
		}

		void World::initialize_world(Vector2 *gravity_vector)
		{
			wd = new b2World(*(gravity_vector->vec));
		}

		void World::dispose()
		{
			RAGE_CHECK_DISPOSED(disposed);

			// TODO: Destroy world, destroy bodies, destroy joints, fixtures etc...
		}
	}
}

#endif
