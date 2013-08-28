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

#include "World.h"

namespace RAGE
{
	namespace Physics
	{
		World::World(void)
		{
			disposed = false;

			wld = NULL;
			body_ary = rb_ary_new();
			g_vector = Qnil;
			debug = new DebugDraw();

			debug->SetFlags( b2Draw::e_shapeBit );
			debug->set_debug_opacity(0.5);
		}

		void World::initialize(VALUE gravity_vector)
		{
			RAGE_GET_DATA(gravity_vector, Vector2, v2);

			v2->add_dependency();

			g_vector = gravity_vector;

			wld = new b2World(*(v2->vec));
			wld->SetDebugDraw(debug);
			
		}

		VALUE World::get_gravity(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			VALUE new_vec = RAGE::Physics::Vector2Wrapper::new_ruby_class_instance();

			RAGE_GET_DATA(new_vec, Vector2, v2);

			delete v2->vec;
			v2->vec = &(wld->GetGravity());
			v2->add_dependency();

			return new_vec;

		}

		void World::draw_debug_objects(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			wld->DrawDebugData();
		}

		VALUE World::create_body(b2BodyDef *def)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			VALUE new_body = Qnil; // To be done...

			b2Body *bd = wld->CreateBody(def);

			b2PolygonShape *polygonShape = new b2PolygonShape();
			b2FixtureDef *myFixtureDef = new b2FixtureDef();
			myFixtureDef->shape = polygonShape;
			
			polygonShape->SetAsBox( 200, 100, b2Vec2(220, 110), 0);
			bd->CreateFixture(myFixtureDef);
			polygonShape->SetAsBox( 20, 1, b2Vec2(0, 40), 0);
			bd->CreateFixture(myFixtureDef);
			polygonShape->SetAsBox( 1, 20, b2Vec2(-20, 20), 0);
		    bd->CreateFixture(myFixtureDef);
			polygonShape->SetAsBox( 1, 20, b2Vec2(20, 20), 0);
			bd->CreateFixture(myFixtureDef);

			rb_ary_push(body_ary, new_body);
		}

		void World::setup_debug_draw_objects(int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			debug->SetFlags(flags);
		}

		void World::gc_mark(void)
		{
			if (!disposed)
			{
				rb_gc_mark(body_ary);
				rb_gc_mark(g_vector);
			}
		}

		void World::physics_dispose(void)
		{

			for(long i = 0; i < RARRAY_LEN(body_ary); i++)
			{
				RAGE_GET_DATA(rb_ary_entry(body_ary, i), Vector2, body);

				body->dispose();
			}

			rb_ary_clear(body_ary);

			RAGE_GET_DATA(g_vector, Vector2, v2);

			v2->dispose();

			delete wld;

			delete debug;

			wld = NULL;
			debug = NULL;

			disposed = true;
		}

		World::~World(void)
		{
			if (!disposed)
				dispose();
		}
	}
}
