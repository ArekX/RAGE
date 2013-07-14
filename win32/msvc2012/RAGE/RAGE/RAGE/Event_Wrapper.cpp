#include "Event_Wrapper.h"

namespace RAGE
{
	namespace Events
	{
		VALUE rb_rage_EventClass;

		VALUE EventWrapper::rb_err(VALUE self)
		{
			rb_raise(rb_eException, RAGE_EVENT_ERROR);
			return Qnil;
		}

		void EventWrapper::load_ruby_class(void)
		{
			VALUE rage = rb_define_module("RAGE");
			rb_rage_EventClass = rb_define_class_under(rage, "Event", rb_cObject);

			rb_define_method(rb_rage_EventClass, "register", RFUNC(EventWrapper::rb_err), 0);
			rb_define_method(rb_rage_EventClass, "unregister", RFUNC(EventWrapper::rb_err), 0);
			rb_define_method(rb_rage_EventClass, "clear", RFUNC(EventWrapper::rb_err), 0);
			rb_define_method(rb_rage_EventClass, "run", RFUNC(EventWrapper::rb_err), 0);
			rb_define_method(rb_rage_EventClass, "getProcCount", RFUNC(EventWrapper::rb_err), 0);
			rb_define_method(rb_rage_EventClass, "dispose", RFUNC(EventWrapper::rb_err), 0);
		}

		VALUE EventWrapper::get_ruby_class(void)
		{
			return rb_rage_EventClass;
		}

		VALUE EventWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_EventClass);
		}

	}
}