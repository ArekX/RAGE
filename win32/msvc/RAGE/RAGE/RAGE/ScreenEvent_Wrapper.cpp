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

#include "ScreenEvent_Wrapper.h"
#include "Event_Wrapper.h"
#include "Events_Wrapper.h"
#include "RubyInterpreter.h"
#include "ScreenEvent.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_SCREEN_EVENT

namespace RAGE
{
	namespace Events
	{
		VALUE rb_rage_ScreenEventClass;

		VALUE ScreenEventWrapper::rb_screen_event_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, ScreenEventWrapper::rb_screen_event_gc_mark, ScreenEventWrapper::rb_screen_event_destroy, new ScreenEvent());
		}

		void ScreenEventWrapper::rb_screen_event_gc_mark(void *value)
		{
			((ScreenEvent*)value)->gc_mark();
		}

		void ScreenEventWrapper::rb_screen_event_destroy(void *value)
		{
			delete value;
		}

		VALUE ScreenEventWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc == 2)
				return rb_register(self, args[0], args[1]);

			return Qnil;
		}

		VALUE ScreenEventWrapper::rb_register(VALUE self, VALUE event_type, VALUE proc)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);
			screen_event->register_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE ScreenEventWrapper::rb_unregister(VALUE self, VALUE event_type, VALUE proc)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);
			screen_event->unregister_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE ScreenEventWrapper::rb_clear(VALUE self, VALUE event_type)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);
			screen_event->clear_procs(FIX2INT(event_type));
			return Qnil;
		}

		VALUE ScreenEventWrapper::rb_run(VALUE self, VALUE event_type)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);
			screen_event->call_procs(FIX2INT(event_type));
			return Qnil;
		}

		VALUE ScreenEventWrapper::rb_get_proc_count(VALUE self, VALUE event_type)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);
			return INT2FIX(screen_event->get_proc_count(FIX2INT(event_type)));
		}

		VALUE ScreenEventWrapper::rb_dispose(VALUE self)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);

			EventsWrapper::unregister_event(self);

			screen_event->dispose();

			return Qnil;
		}

		VALUE ScreenEventWrapper::rb_disposed(VALUE self)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);
			
			return screen_event->disposed ? Qtrue : Qfalse;
		}

		VALUE ScreenEventWrapper::rb_get_procs_array(VALUE self, VALUE event_type)
		{
			ScreenEvent *screen_event;
			Data_Get_Struct(self, ScreenEvent, screen_event);
			
			return screen_event->get_observer_array(FIX2INT(event_type));
		}

		void ScreenEventWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::ScreenEvent")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rage_ScreenEventClass = rb_define_class_under(rage, "ScreenEvent", EventWrapper::get_ruby_class());

			VALUE events = rb_define_module_under(rage, "Events");
			rb_define_const(events, "SCREEN", INT2FIX(RAGE_SCREEN_EVENT));
			rb_define_const(events, "SCREEN_CLOSE", INT2FIX(RAGE_EVENT_SCREEN_CLOSE));
			rb_define_const(events, "SCREEN_FOCUS", INT2FIX(RAGE_EVENT_SCREEN_FOCUS));
			rb_define_const(events, "SCREEN_LOST", INT2FIX(RAGE_EVENT_SCREEN_LOST));
			rb_define_const(events, "SCREEN_RESIZE", INT2FIX(RAGE_EVENT_SCREEN_RESIZE));

			rb_define_alloc_func(rb_rage_ScreenEventClass, ScreenEventWrapper::rb_screen_event_alloc);

			rb_define_method(rb_rage_ScreenEventClass, "initialize", RFUNC(ScreenEventWrapper::rb_initialize), -1);
			rb_define_method(rb_rage_ScreenEventClass, "register", RFUNC(ScreenEventWrapper::rb_register), 2);
			rb_define_method(rb_rage_ScreenEventClass, "unregister", RFUNC(ScreenEventWrapper::rb_unregister), 2);
			rb_define_method(rb_rage_ScreenEventClass, "clear", RFUNC(ScreenEventWrapper::rb_clear), 1);
			rb_define_method(rb_rage_ScreenEventClass, "run", RFUNC(ScreenEventWrapper::rb_run), 1);
			rb_define_method(rb_rage_ScreenEventClass, "getProcCount", RFUNC(ScreenEventWrapper::rb_get_proc_count), 1);
			rb_define_method(rb_rage_ScreenEventClass, "getProcsAsArray", RFUNC(ScreenEventWrapper::rb_get_procs_array), 1);
			rb_define_method(rb_rage_ScreenEventClass, "dispose", RFUNC(ScreenEventWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_ScreenEventClass, "disposed?", RFUNC(ScreenEventWrapper::rb_disposed), 0);
		}

		VALUE ScreenEventWrapper::get_ruby_class(void)
		{
			return rb_rage_ScreenEventClass;
		}

		VALUE ScreenEventWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, nullptr, rb_rage_ScreenEventClass);
		}

	}
}

#endif