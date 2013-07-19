#include "KeyboardEvent_Wrapper.h"

namespace RAGE
{
	namespace Events
	{
		VALUE rb_rage_KeyEventClass;

		VALUE KeyboardEventWrapper::rb_key_event_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, KeyboardEventWrapper::rb_key_event_mark, KeyboardEventWrapper::rb_key_event_destroy, new KeyboardEvent());
		}

		void KeyboardEventWrapper::rb_key_event_mark(void *value)
		{
			((KeyboardEvent*)value)->gc_mark();
		}

		void KeyboardEventWrapper::rb_key_event_destroy(void *value)
		{
			delete value;
		}

		VALUE KeyboardEventWrapper::rb_register(VALUE self, VALUE event_type, VALUE proc)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			key_event->register_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE KeyboardEventWrapper::rb_unregister(VALUE self, VALUE event_type, VALUE proc)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			key_event->unregister_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE KeyboardEventWrapper::rb_clear(VALUE self, VALUE event_type)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			key_event->clear_procs(FIX2INT(event_type));
			return Qnil;
		}

		VALUE KeyboardEventWrapper::rb_run(VALUE self, VALUE event_type, VALUE keycode)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			key_event->call_procs(FIX2INT(event_type), FIX2INT(keycode));
			return Qnil;
		}

		VALUE KeyboardEventWrapper::rb_dispose(VALUE self)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);

			EventsWrapper::unregister_event(self);

			key_event->dispose();

			return Qnil;
		}

		VALUE KeyboardEventWrapper::rb_disposed(VALUE self)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			
			return key_event->disposed ? Qtrue : Qfalse;
		}

		VALUE KeyboardEventWrapper::rb_get_proc_count(VALUE self, VALUE event_type)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			return INT2FIX(key_event->get_proc_count(FIX2INT(event_type)));
		}

		VALUE KeyboardEventWrapper::rb_use_keycode_names(VALUE self, VALUE val)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			key_event->keycode_names = (TYPE(val) == T_TRUE);
			return Qnil;
		}

		VALUE KeyboardEventWrapper::rb_use_typed_char(VALUE self, VALUE val)
		{
			KeyboardEvent *key_event;
			Data_Get_Struct(self, KeyboardEvent, key_event);
			key_event->unichar = (TYPE(val) == T_TRUE);
			return Qtrue;
		}

		void KeyboardEventWrapper::load_ruby_class(void)
		{
			VALUE rage = rb_define_module("RAGE");
			rb_rage_KeyEventClass = rb_define_class_under(rage, "KeyEvent", EventWrapper::get_ruby_class());

			VALUE events = rb_define_module_under(rage, "Events");
			rb_define_const(events, "KEYBOARD", INT2FIX(RAGE_KEYBOARD_EVENT));
			rb_define_const(events, "KEY_UP", INT2FIX(RAGE_EVENTS_KEY_UP));
			rb_define_const(events, "KEY_DOWN", INT2FIX(RAGE_EVENTS_KEY_DOWN));
			rb_define_const(events, "KEY_PRESS", INT2FIX(RAGE_EVENTS_KEY_CHAR));

			rb_define_alloc_func(rb_rage_KeyEventClass, KeyboardEventWrapper::rb_key_event_alloc);

			rb_define_method(rb_rage_KeyEventClass, "register", RFUNC(KeyboardEventWrapper::rb_register), 2);
			rb_define_method(rb_rage_KeyEventClass, "unregister", RFUNC(KeyboardEventWrapper::rb_unregister), 2);
			rb_define_method(rb_rage_KeyEventClass, "useTyped", RFUNC(KeyboardEventWrapper::rb_use_typed_char), 1);
			rb_define_method(rb_rage_KeyEventClass, "useKeyCodeNames", RFUNC(KeyboardEventWrapper::rb_use_keycode_names), 1);
			rb_define_method(rb_rage_KeyEventClass, "clear", RFUNC(KeyboardEventWrapper::rb_clear), 1);
			rb_define_method(rb_rage_KeyEventClass, "run", RFUNC(KeyboardEventWrapper::rb_run), 2);
			rb_define_method(rb_rage_KeyEventClass, "getProcCount", RFUNC(KeyboardEventWrapper::rb_get_proc_count), 1);
			rb_define_method(rb_rage_KeyEventClass, "dispose", RFUNC(KeyboardEventWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_KeyEventClass, "disposed?", RFUNC(KeyboardEventWrapper::rb_disposed), 0);
		}

		VALUE KeyboardEventWrapper::get_ruby_class(void)
		{
			return rb_rage_KeyEventClass;
		}

		VALUE KeyboardEventWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_KeyEventClass);
		}
	}
}