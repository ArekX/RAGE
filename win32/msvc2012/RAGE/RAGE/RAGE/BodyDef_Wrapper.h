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
#include "BodyDef.h"

namespace RAGE
{
	namespace Physics
	{
		class BodyDefWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_initialize(VALUE self);
			static VALUE rb_set_type(VALUE self, VALUE type);
			static VALUE rb_get_type(VALUE self);
			static VALUE rb_get_position(VALUE self);
			static VALUE rb_set_position(VALUE self, VALUE val);
			static VALUE rb_get_angle(VALUE self);
			static VALUE rb_set_angle(VALUE self, VALUE val);
			static VALUE rb_get_linear_velocity(VALUE self);
			static VALUE rb_set_linear_velocity(VALUE self, VALUE val);
			static VALUE rb_get_gravity_scale(VALUE self);
			static VALUE rb_set_gravity_scale(VALUE self, VALUE val);
			static VALUE rb_get_angular_velocity(VALUE self);
			static VALUE rb_set_angular_velocity(VALUE self, VALUE val);
			static VALUE rb_get_linear_damping(VALUE self);
			static VALUE rb_set_linear_damping(VALUE self, VALUE val);
			static VALUE rb_get_angular_damping(VALUE self);
			static VALUE rb_set_angular_damping(VALUE self, VALUE val);
			static VALUE rb_get_allow_sleep(VALUE self);
			static VALUE rb_set_allow_sleep(VALUE self, VALUE val);
			static VALUE rb_get_awake(VALUE self);
			static VALUE rb_set_awake(VALUE self, VALUE val);
			static VALUE rb_get_fixed_rotation(VALUE self);
			static VALUE rb_set_fixed_rotation(VALUE self, VALUE val);
			static VALUE rb_get_bullet(VALUE self);
			static VALUE rb_set_bullet(VALUE self, VALUE val);
			static VALUE rb_get_active(VALUE self);
			static VALUE rb_set_active(VALUE self, VALUE val);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}
