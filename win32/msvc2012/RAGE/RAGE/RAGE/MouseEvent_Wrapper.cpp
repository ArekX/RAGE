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

#include "MouseEvent_Wrapper.h"
#include "Event_Wrapper.h"
#include "Events_Wrapper.h"
#include "RubyInterpreter.h"
#include "MouseEvent.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_MOUSE_EVENT

namespace RAGE
{
	namespace Events
	{
		VALUE rb_rage_MouseEventClass;

		VALUE MouseEventWrapper::rb_mouse_event_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, MouseEventWrapper::rb_mouse_event_gc_mark, MouseEventWrapper::rb_mouse_event_destroy, new MouseEvent());
		}

		void MouseEventWrapper::rb_mouse_event_gc_mark(void *value)
		{
			((MouseEvent*)value)->gc_mark();
		}

		void MouseEventWrapper::rb_mouse_event_destroy(void *value)
		{
			delete value;
		}

		VALUE MouseEventWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc == 2)
				return rb_register(self, args[0], args[1]);

			return Qnil;
		}

		VALUE MouseEventWrapper::rb_register(VALUE self, VALUE event_type, VALUE proc)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);
			mouse_event->register_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE MouseEventWrapper::rb_unregister(VALUE self, VALUE event_type, VALUE proc)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);
			mouse_event->unregister_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE MouseEventWrapper::rb_clear(VALUE self, VALUE event_type)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);
			mouse_event->clear_procs(FIX2INT(event_type));
			return Qnil;
		}

		VALUE MouseEventWrapper::rb_run(VALUE self, VALUE event_type, VALUE buttons, VALUE x, VALUE y, VALUE wheel)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);
			mouse_event->call_procs(FIX2INT(event_type), FIX2UINT(buttons), FIX2INT(x), FIX2INT(y), FIX2INT(wheel));
			return Qnil;
		}

		VALUE MouseEventWrapper::rb_get_proc_count(VALUE self, VALUE event_type)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);
			return INT2FIX(mouse_event->get_proc_count(FIX2INT(event_type)));
		}

		VALUE MouseEventWrapper::rb_dispose(VALUE self)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);

			EventsWrapper::unregister_event(self);

			mouse_event->dispose();

			return Qnil;
		}

		VALUE MouseEventWrapper::rb_disposed(VALUE self)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);
			
			return mouse_event->disposed ? Qtrue : Qfalse;
		}

		VALUE MouseEventWrapper::rb_get_procs_array(VALUE self, VALUE event_type)
		{
			MouseEvent *mouse_event;
			Data_Get_Struct(self, MouseEvent, mouse_event);

			return mouse_event->get_observer_array(FIX2INT(event_type));
		}

		void MouseEventWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::MouseEvent")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rage_MouseEventClass = rb_define_class_under(rage, "MouseEvent", EventWrapper::get_ruby_class());

			VALUE events = rb_define_module_under(rage, "Events");
			rb_define_const(events, "MOUSE", INT2FIX(RAGE_MOUSE_EVENT));
			rb_define_const(events, "MOUSE_DOWN", INT2FIX(RAGE_EVENT_MOUSE_DOWN));
			rb_define_const(events, "MOUSE_UP", INT2FIX(RAGE_EVENT_MOUSE_UP));
			rb_define_const(events, "MOUSE_MOVE", INT2FIX(RAGE_EVENT_MOUSE_MOVE));
			rb_define_const(events, "MOUSE_ENTER", INT2FIX(RAGE_EVENT_MOUSE_ENTER));
			rb_define_const(events, "MOUSE_LEAVE", INT2FIX(RAGE_EVENT_MOUSE_LEAVE));

			rb_define_alloc_func(rb_rage_MouseEventClass, MouseEventWrapper::rb_mouse_event_alloc);

			rb_define_method(rb_rage_MouseEventClass, "initialize", RFUNC(MouseEventWrapper::rb_initialize), -1);
			rb_define_method(rb_rage_MouseEventClass, "register", RFUNC(MouseEventWrapper::rb_register), 2);
			rb_define_method(rb_rage_MouseEventClass, "unregister", RFUNC(MouseEventWrapper::rb_unregister), 2);
			rb_define_method(rb_rage_MouseEventClass, "clear", RFUNC(MouseEventWrapper::rb_clear), 1);
			rb_define_method(rb_rage_MouseEventClass, "run", RFUNC(MouseEventWrapper::rb_run), 5);
			rb_define_method(rb_rage_MouseEventClass, "getProcCount", RFUNC(MouseEventWrapper::rb_get_proc_count), 1);
			rb_define_method(rb_rage_MouseEventClass, "getProcsAsArray", RFUNC(MouseEventWrapper::rb_get_procs_array), 1);
			rb_define_method(rb_rage_MouseEventClass, "dispose", RFUNC(MouseEventWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_MouseEventClass, "disposed?", RFUNC(MouseEventWrapper::rb_disposed), 0);
		}

		VALUE MouseEventWrapper::get_ruby_class(void)
		{
			return rb_rage_MouseEventClass;
		}

		VALUE MouseEventWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_MouseEventClass);
		}

	}
}


#endif