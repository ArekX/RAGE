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

#include "Vector2_Wrapper.h"

namespace RAGE
{
	namespace Physics
	{
		VALUE rb_rage_Vector2Class;

		VALUE Vector2Wrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, Vector2Wrapper::rb_destroy, new Vector2());
		}

		void Vector2Wrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE Vector2Wrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			if ((argc != 0) && (argc != 2))
			{
				rb_raise(rb_eException, RAGE_VAR_FUNCTION_INCOMP_ARGS, 0, 2);
				return Qnil;
			}

			if (argc == 2)
				v2->initialize(NUM2DBL(args[0]), NUM2DBL(args[1]));
			else
				v2->initialize();

			return Qnil;
		}

		VALUE Vector2Wrapper::rb_get_x(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			return DBL2NUM(v2->get_x());
		}

		VALUE Vector2Wrapper::rb_get_y(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			return DBL2NUM(v2->get_y());
		}

		VALUE Vector2Wrapper::rb_set_x(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			v2->set_x(NUM2DBL(val));

			return Qnil;
		}

		VALUE Vector2Wrapper::rb_set_y(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			v2->set_y(NUM2DBL(val));

			return Qnil;
		}

		VALUE Vector2Wrapper::rb_length(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			return DBL2NUM(v2->length());
		}

		VALUE Vector2Wrapper::rb_length_squared(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			return DBL2NUM(v2->length_squared());
		}

		VALUE Vector2Wrapper::rb_add_operator(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, Vector2, v2);
			RAGE_GET_DATA(val, Vector2, v2val);

			v2->add(v2val->vec);

			return self;
		}

		VALUE Vector2Wrapper::rb_negate(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			v2->negate();

			return self;
		}

		VALUE Vector2Wrapper::rb_indexed_get(VALUE self, VALUE index)
		{
			int idx = FIX2INT(index);

			switch(idx)
			{
				case 0:
					return Vector2Wrapper::rb_get_x(self);
				case 1:
					return Vector2Wrapper::rb_get_y(self);

				default:
					return Qnil;
			}

		}

		VALUE Vector2Wrapper::rb_indexed_set(VALUE self, VALUE index, VALUE val)
		{
			int idx = FIX2INT(index);

			switch(idx)
			{
				case 0:
					return Vector2Wrapper::rb_set_x(self, val);
				case 1:
					return Vector2Wrapper::rb_set_y(self, val);

				default:
					return Qnil;
			}
		}

		VALUE Vector2Wrapper::rb_sub_operator(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, Vector2, v2);
			RAGE_GET_DATA(val, Vector2, v2val);

			v2->sub(v2val->vec);

			return self;
		}

		VALUE Vector2Wrapper::rb_mul_operator(VALUE self, VALUE val)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			v2->mul(NUM2DBL(val));

			return self;
		}

		VALUE Vector2Wrapper::rb_normalize(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			return DBL2NUM(v2->normalize());
		}

		VALUE Vector2Wrapper::rb_set(VALUE self, VALUE x, VALUE y)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			v2->set(NUM2DBL(x), NUM2DBL(y));

			return Qnil;
		}

		VALUE Vector2Wrapper::rb_set_zero(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			v2->set_zero();

			return Qnil;
		}

		VALUE Vector2Wrapper::rb_is_valid(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			return v2->is_valid() ? Qtrue : Qfalse;
		}

		VALUE Vector2Wrapper::rb_skew(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			VALUE new_vec = Vector2Wrapper::new_ruby_class_instance();

			RAGE_GET_DATA(new_vec, Vector2, valv2);

			v2->skew(valv2->vec);

			return new_vec;
		}

		VALUE Vector2Wrapper::rb_dispose(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			v2->dispose();

			return Qnil;
		}

		VALUE Vector2Wrapper::rb_disposed(VALUE self)
		{
			RAGE_GET_DATA(self, Vector2, v2);

			return v2->disposed ? Qtrue : Qfalse;
		}

		void Vector2Wrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Physics::Vector2")) return;

			
			VALUE rage = rb_define_module("RAGE");
			VALUE physics = rb_define_module_under(rage, "Physics");

			rb_rage_Vector2Class = rb_define_class_under(physics, "Vector2", rb_cObject);

			rb_define_alloc_func(rb_rage_Vector2Class, Vector2Wrapper::rb_alloc);

			rb_define_method(rb_rage_Vector2Class, "initialize", RFUNC(Vector2Wrapper::rb_initialize), -1);
			rb_define_method(rb_rage_Vector2Class, "x", RFUNC(Vector2Wrapper::rb_get_x), 0);
			rb_define_method(rb_rage_Vector2Class, "y", RFUNC(Vector2Wrapper::rb_get_y), 0);
			rb_define_method(rb_rage_Vector2Class, "x=", RFUNC(Vector2Wrapper::rb_set_x), 1);
			rb_define_method(rb_rage_Vector2Class, "y=", RFUNC(Vector2Wrapper::rb_set_y), 1);
			rb_define_method(rb_rage_Vector2Class, "+", RFUNC(Vector2Wrapper::rb_add_operator), 1);
			rb_define_method(rb_rage_Vector2Class, "-", RFUNC(Vector2Wrapper::rb_sub_operator), 1);
			rb_define_method(rb_rage_Vector2Class, "*", RFUNC(Vector2Wrapper::rb_mul_operator), 1);
			rb_define_method(rb_rage_Vector2Class, "-@", RFUNC(Vector2Wrapper::rb_negate), 0);
			rb_define_method(rb_rage_Vector2Class, "[]", RFUNC(Vector2Wrapper::rb_indexed_get), 1);
			rb_define_method(rb_rage_Vector2Class, "[]=", RFUNC(Vector2Wrapper::rb_indexed_set), 2);
			rb_define_method(rb_rage_Vector2Class, "isValid?", RFUNC(Vector2Wrapper::rb_is_valid), 0);
			rb_define_method(rb_rage_Vector2Class, "normalize", RFUNC(Vector2Wrapper::rb_normalize), 0);
			rb_define_method(rb_rage_Vector2Class, "set", RFUNC(Vector2Wrapper::rb_set), 2);
			rb_define_method(rb_rage_Vector2Class, "skew", RFUNC(Vector2Wrapper::rb_skew), 0);
			rb_define_method(rb_rage_Vector2Class, "setZero", RFUNC(Vector2Wrapper::rb_set_zero), 0);
			rb_define_method(rb_rage_Vector2Class, "length", RFUNC(Vector2Wrapper::rb_length), 0);
			rb_define_method(rb_rage_Vector2Class, "lengthSquared", RFUNC(Vector2Wrapper::rb_length_squared), 0);
			rb_define_method(rb_rage_Vector2Class, "dispose", RFUNC(Vector2Wrapper::rb_dispose), 0);
			rb_define_method(rb_rage_Vector2Class, "disposed?", RFUNC(Vector2Wrapper::rb_disposed), 0);
		}

		VALUE Vector2Wrapper::get_ruby_class(void)
		{
			return rb_rage_Vector2Class;
		}

		VALUE Vector2Wrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_Vector2Class);
		}
	}
}
