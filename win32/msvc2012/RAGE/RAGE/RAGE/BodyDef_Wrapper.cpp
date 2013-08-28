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

#include "BodyDef_Wrapper.h"

namespace RAGE
{
	namespace Physics
	{
		VALUE rb_rage_BodyDefClass;

		VALUE BodyDefWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, BodyDefWrapper::rb_destroy, new BodyDef());
		}

		void BodyDefWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE BodyDefWrapper::rb_initialize(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->initialize();

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_set_type(VALUE self, VALUE type)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_body_type((b2BodyType)FIX2INT(type));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_type(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return INT2FIX(bd->get_body_type());
		}

		VALUE BodyDefWrapper::rb_get_position(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return bd->get_position();
		}

		VALUE BodyDefWrapper::rb_set_position(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);
			RAGE_GET_DATA(val, Vector2, v2);
			
			bd->set_position(v2->vec);

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_angle(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return DBL2NUM(bd->get_angle());
		}

		VALUE BodyDefWrapper::rb_set_angle(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_angle(NUM2DBL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_linear_velocity(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return bd->get_linear_velocity();
		}

		VALUE BodyDefWrapper::rb_set_linear_velocity(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);
			RAGE_GET_DATA(val, Vector2, v2);

			bd->set_linear_velocity(v2->vec);

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_gravity_scale(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return DBL2NUM(bd->get_gravity_scale());
		}

		VALUE BodyDefWrapper::rb_set_gravity_scale(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_gravity_scale(NUM2DBL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_angular_velocity(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return DBL2NUM(bd->get_angular_velocity());
		}

		VALUE BodyDefWrapper::rb_set_angular_velocity(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_angular_velocity(NUM2DBL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_linear_damping(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return DBL2NUM(bd->get_linear_damping());
		}

		VALUE BodyDefWrapper::rb_set_linear_damping(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_linear_damping(NUM2DBL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_angular_damping(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return DBL2NUM(bd->get_angular_damping());
		}

		VALUE BodyDefWrapper::rb_set_angular_damping(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_angular_damping(NUM2DBL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_allow_sleep(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return BOOL2RB(bd->get_allow_sleep());
		}

		VALUE BodyDefWrapper::rb_set_allow_sleep(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_allow_sleep(RB2BOOL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_awake(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return BOOL2RB(bd->get_awake());
		}

		VALUE BodyDefWrapper::rb_set_awake(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_awake(RB2BOOL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_fixed_rotation(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return BOOL2RB(bd->get_fixed_rotation());
		}

		VALUE BodyDefWrapper::rb_set_fixed_rotation(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_fixed_rotation(RB2BOOL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_bullet(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return BOOL2RB(bd->get_bullet());
		}

		VALUE BodyDefWrapper::rb_set_bullet(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_bullet(RB2BOOL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_get_active(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return BOOL2RB(bd->get_active());
		}

		VALUE BodyDefWrapper::rb_set_active(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->set_active(RB2BOOL(val));

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_dispose(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			bd->dispose();

			return Qnil;
		}

		VALUE BodyDefWrapper::rb_disposed(VALUE self)
		{
			RAGE_GET_DATA(self, BodyDef, bd);

			return bd->disposed ? Qtrue : Qfalse;
		}

		void BodyDefWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Physics::BodyDef")) return;

			VALUE rage = rb_define_module("RAGE");
			VALUE physics = rb_define_module_under(rage, "Physics");

			rb_rage_BodyDefClass = rb_define_class_under(physics, "BodyDef", rb_cObject);

			rb_define_alloc_func(rb_rage_BodyDefClass, BodyDefWrapper::rb_alloc);

			rb_define_method(rb_rage_BodyDefClass, "initialize", RFUNC(BodyDefWrapper::rb_initialize), 0);
			rb_define_method(rb_rage_BodyDefClass, "type=", RFUNC(BodyDefWrapper::rb_set_type), 1);
			rb_define_method(rb_rage_BodyDefClass, "type", RFUNC(BodyDefWrapper::rb_get_type), 0);
			rb_define_method(rb_rage_BodyDefClass, "position=", RFUNC(BodyDefWrapper::rb_set_position), 1);
			rb_define_method(rb_rage_BodyDefClass, "position", RFUNC(BodyDefWrapper::rb_get_position), 0);
			rb_define_method(rb_rage_BodyDefClass, "angle=", RFUNC(BodyDefWrapper::rb_set_angle), 1);
			rb_define_method(rb_rage_BodyDefClass, "angle", RFUNC(BodyDefWrapper::rb_get_angle), 0);
			rb_define_method(rb_rage_BodyDefClass, "linearVelocity=", RFUNC(BodyDefWrapper::rb_set_linear_velocity), 1);
			rb_define_method(rb_rage_BodyDefClass, "linearVelocity", RFUNC(BodyDefWrapper::rb_get_linear_velocity), 0);
			rb_define_method(rb_rage_BodyDefClass, "gravityScale=", RFUNC(BodyDefWrapper::rb_set_gravity_scale), 1);
			rb_define_method(rb_rage_BodyDefClass, "gravityScale", RFUNC(BodyDefWrapper::rb_get_gravity_scale), 0);
			rb_define_method(rb_rage_BodyDefClass, "angularVelocity=", RFUNC(BodyDefWrapper::rb_set_angular_velocity), 1);
			rb_define_method(rb_rage_BodyDefClass, "angularVelocity", RFUNC(BodyDefWrapper::rb_get_angular_velocity), 0);
			rb_define_method(rb_rage_BodyDefClass, "linearDamping=", RFUNC(BodyDefWrapper::rb_set_linear_damping), 1);
			rb_define_method(rb_rage_BodyDefClass, "linearDamping", RFUNC(BodyDefWrapper::rb_get_linear_damping), 0);
			rb_define_method(rb_rage_BodyDefClass, "angularDamping=", RFUNC(BodyDefWrapper::rb_set_angular_damping), 1);
			rb_define_method(rb_rage_BodyDefClass, "angularDamping", RFUNC(BodyDefWrapper::rb_get_angular_damping), 0);
			rb_define_method(rb_rage_BodyDefClass, "allowSleep=", RFUNC(BodyDefWrapper::rb_set_allow_sleep), 1);
			rb_define_method(rb_rage_BodyDefClass, "allowSleep", RFUNC(BodyDefWrapper::rb_get_allow_sleep), 0);
			rb_define_method(rb_rage_BodyDefClass, "awake=", RFUNC(BodyDefWrapper::rb_set_awake), 1);
			rb_define_method(rb_rage_BodyDefClass, "awake", RFUNC(BodyDefWrapper::rb_get_awake), 0);
			rb_define_method(rb_rage_BodyDefClass, "fixedRotation=", RFUNC(BodyDefWrapper::rb_set_fixed_rotation), 1);
			rb_define_method(rb_rage_BodyDefClass, "fixedRotation", RFUNC(BodyDefWrapper::rb_get_fixed_rotation), 0);
			rb_define_method(rb_rage_BodyDefClass, "bullet=", RFUNC(BodyDefWrapper::rb_set_bullet), 1);
			rb_define_method(rb_rage_BodyDefClass, "bullet", RFUNC(BodyDefWrapper::rb_get_bullet), 0);
			rb_define_method(rb_rage_BodyDefClass, "active=", RFUNC(BodyDefWrapper::rb_set_active), 1);
			rb_define_method(rb_rage_BodyDefClass, "active", RFUNC(BodyDefWrapper::rb_get_active), 0);
			rb_define_method(rb_rage_BodyDefClass, "dispose", RFUNC(BodyDefWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_BodyDefClass, "disposed?", RFUNC(BodyDefWrapper::rb_disposed), 0);
		}

		VALUE BodyDefWrapper::get_ruby_class(void)
		{
			return rb_rage_BodyDefClass;
		}

		VALUE BodyDefWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_BodyDefClass);
		}
	}
}
