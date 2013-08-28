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

#include "World_Wrapper.h"

namespace RAGE
{
	namespace Physics
	{
		VALUE rb_rage_WorldClass;

		VALUE WorldWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, WorldWrapper::rb_mark, WorldWrapper::rb_destroy, new World());
		}

		VALUE WorldWrapper::rb_initialize(VALUE self, VALUE gravity_vector)
		{
			RAGE_GET_DATA(self, World, wld);

			wld->initialize(gravity_vector);
			
			return Qnil;
		}

		VALUE WorldWrapper::rb_get_gravity(VALUE self)
		{
			RAGE_GET_DATA(self, World, wld);

			return wld->get_gravity();
		}

		void WorldWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		void WorldWrapper::rb_mark(void *ptr)
		{
			((World*)ptr)->gc_mark();
		}

		VALUE WorldWrapper::rb_draw_debug(VALUE self)
		{
			RAGE_GET_DATA(self, World, wld);

			wld->draw_debug_objects();

			return Qnil;
		}

		VALUE WorldWrapper::rb_dispose(VALUE self)
		{
			RAGE_GET_DATA(self, World, wld);

			wld->dispose();

			return Qnil;
		}

		VALUE WorldWrapper::rb_set_debug_draw_objects(VALUE self, VALUE flags)
		{
			RAGE_GET_DATA(self, World, wld);

			wld->setup_debug_draw_objects(FIX2INT(flags));

			return Qnil;
		}

		VALUE WorldWrapper::rb_disposed(VALUE self)
		{
			RAGE_GET_DATA(self, World, wld);

			return wld->disposed ? Qtrue : Qfalse;
		}

		VALUE WorldWrapper::rb_create_body(VALUE self, VALUE body_def)
		{
			RAGE_GET_DATA(self, World, wld);
			RAGE_GET_DATA(body_def, BodyDef, bd);

			return wld->create_body(bd->bd);
		}

		void WorldWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Physics::World")) return;

			VALUE rage = rb_define_module("RAGE");
			VALUE physics = rb_define_module_under(rage, "Physics");

			rb_rage_WorldClass = rb_define_class_under(physics, "World", rb_cObject);

			rb_define_alloc_func(rb_rage_WorldClass, WorldWrapper::rb_alloc);

			rb_define_method(rb_rage_WorldClass, "initialize", RFUNC(WorldWrapper::rb_initialize), 1);
			rb_define_method(rb_rage_WorldClass, "getGravity", RFUNC(WorldWrapper::rb_get_gravity), 0);
			rb_define_method(rb_rage_WorldClass, "drawDebugData", RFUNC(WorldWrapper::rb_draw_debug), 0);
			rb_define_method(rb_rage_WorldClass, "setDebugFlags", RFUNC(WorldWrapper::rb_set_debug_draw_objects), 1);
			rb_define_method(rb_rage_WorldClass, "createBody", RFUNC(WorldWrapper::rb_create_body), 1);
			rb_define_method(rb_rage_WorldClass, "dispose", RFUNC(WorldWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_WorldClass, "disposed?", RFUNC(WorldWrapper::rb_disposed), 0);
		}

		VALUE WorldWrapper::get_ruby_class(void)
		{
			return rb_rage_WorldClass;
		}

		VALUE WorldWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_WorldClass);
		}
	}
}
