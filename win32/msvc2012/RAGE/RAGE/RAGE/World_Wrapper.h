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

#include "Vector2.h"
#include "BodyDef.h"
#include "World.h"
#include "Vector2_Wrapper.h"

namespace RAGE
{
	namespace Physics
	{
		class WorldWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static void rb_mark(void *ptr);
			static VALUE rb_initialize(VALUE self, VALUE gravity_vector);
			static VALUE rb_get_gravity(VALUE self);
			static VALUE rb_create_body(VALUE self, VALUE body_def);
			static VALUE rb_draw_debug(VALUE self);
			static VALUE rb_set_debug_draw_objects(VALUE self, VALUE flags);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};

	}
}
