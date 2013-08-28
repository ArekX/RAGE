#include "Body_Wrapper.h"

namespace RAGE
{
	namespace Physics
	{
		VALUE rb_rage_BodyClass;

		VALUE BodyWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, BodyWrapper::rb_mark, BodyWrapper::rb_destroy, new Body());
		}

		void BodyWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		void BodyWrapper::rb_mark(void *ptr)
		{
			((Body*)ptr)->gc_mark();
		}

		VALUE BodyWrapper::rb_initialize(VALUE self, VALUE world, VALUE body_def)
		{
			RAGE_GET_DATA(self, Body, bod);
			RAGE_GET_DATA(world, World, wld);
			RAGE_GET_DATA(body_def, BodyDef, bd);

			bod->initialize(wld->wld, bd->bd);

			return Qnil;
		}

		void BodyWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Physics::Body")) return;

			VALUE rage = rb_define_module("RAGE");
			VALUE physics = rb_define_module_under(rage, "Physics");

			rb_rage_BodyClass = rb_define_class_under(physics, "Body", rb_cObject);

			rb_define_alloc_func(rb_rage_BodyClass, BodyWrapper::rb_alloc);
		}

		VALUE BodyWrapper::get_ruby_class(void)
		{
			return rb_rage_BodyClass;
		}

		VALUE BodyWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_BodyClass);
		}
	}
}
