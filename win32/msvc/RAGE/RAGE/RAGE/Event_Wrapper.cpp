/*
Copyright (c) 2014 Aleksandar Panic

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

#include "Event_Wrapper.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_EVENTS

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

		bool EventWrapper::rb_is_enabled(void)
		{
			return (
					Interpreter::Ruby::get_config()->is_on("RAGE::JoyEvent") ||
					Interpreter::Ruby::get_config()->is_on("RAGE::KeyEvent") ||
					Interpreter::Ruby::get_config()->is_on("RAGE::MouseEvent") ||
					Interpreter::Ruby::get_config()->is_on("RAGE::ScreenEvent") ||
					Interpreter::Ruby::get_config()->is_on("RAGE::TimerEvent")
				   );
		}

		void EventWrapper::load_ruby_class(void)
		{
			if (!EventWrapper::rb_is_enabled()) return;

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
			return rb_class_new_instance(0, nullptr, rb_rage_EventClass);
		}

	}
}

#endif