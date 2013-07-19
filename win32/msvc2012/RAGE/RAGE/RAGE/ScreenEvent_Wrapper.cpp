#include "ScreenEvent_Wrapper.h"

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

		void ScreenEventWrapper::load_ruby_class(void)
		{
			VALUE rage = rb_define_module("RAGE");
			rb_rage_ScreenEventClass = rb_define_class_under(rage, "ScreenEvent", EventWrapper::get_ruby_class());

			VALUE events = rb_define_module_under(rage, "Events");
			rb_define_const(events, "SCREEN", INT2FIX(RAGE_SCREEN_EVENT));
			rb_define_const(events, "SCREEN_CLOSE", INT2FIX(RAGE_EVENT_SCREEN_CLOSE));
			rb_define_const(events, "SCREEN_FOCUS", INT2FIX(RAGE_EVENT_SCREEN_FOCUS));
			rb_define_const(events, "SCREEN_LOST", INT2FIX(RAGE_EVENT_SCREEN_LOST));
			rb_define_const(events, "SCREEN_RESIZE", INT2FIX(RAGE_EVENT_SCREEN_RESIZE));

			rb_define_alloc_func(rb_rage_ScreenEventClass, ScreenEventWrapper::rb_screen_event_alloc);

			rb_define_method(rb_rage_ScreenEventClass, "register", RFUNC(ScreenEventWrapper::rb_register), 2);
			rb_define_method(rb_rage_ScreenEventClass, "unregister", RFUNC(ScreenEventWrapper::rb_unregister), 2);
			rb_define_method(rb_rage_ScreenEventClass, "clear", RFUNC(ScreenEventWrapper::rb_clear), 1);
			rb_define_method(rb_rage_ScreenEventClass, "run", RFUNC(ScreenEventWrapper::rb_run), 1);
			rb_define_method(rb_rage_ScreenEventClass, "getProcCount", RFUNC(ScreenEventWrapper::rb_get_proc_count), 1);
			rb_define_method(rb_rage_ScreenEventClass, "dispose", RFUNC(ScreenEventWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_ScreenEventClass, "disposed?", RFUNC(ScreenEventWrapper::rb_disposed), 0);
		}

		VALUE ScreenEventWrapper::get_ruby_class(void)
		{
			return rb_rage_ScreenEventClass;
		}

		VALUE ScreenEventWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_ScreenEventClass);
		}

	}
}
