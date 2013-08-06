#include "JoyEvent_Wrapper.h"

namespace RAGE
{
	namespace Events
	{
		VALUE rb_rage_JoyEventClass;

		VALUE JoyEventWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, JoyEventWrapper::rb_mark, JoyEventWrapper::rb_destroy, new JoyEvent());
		}

		void JoyEventWrapper::rb_mark(void *ptr)
		{
			((JoyEvent*)ptr)->gc_mark();
		}

		void JoyEventWrapper::rb_destroy(void *value)
		{
			delete value;
		}

		VALUE JoyEventWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc == 2)
				return rb_register(self, args[0], args[1]);

			return Qnil;
		}

		VALUE JoyEventWrapper::rb_register(VALUE self, VALUE event_type, VALUE proc)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);
			joy_event->register_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE JoyEventWrapper::rb_unregister(VALUE self, VALUE event_type, VALUE proc)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);
			joy_event->unregister_proc(FIX2INT(event_type), proc);
			return Qnil;
		}

		VALUE JoyEventWrapper::rb_clear(VALUE self, VALUE event_type)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);
			joy_event->clear_procs(FIX2INT(event_type));
			return Qnil;
		}

		VALUE JoyEventWrapper::rb_run(VALUE self, VALUE event_type, VALUE button_num)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);
			joy_event->call_procs_button(FIX2INT(event_type), FIX2INT(button_num));
			return Qnil;
		}

		VALUE JoyEventWrapper::rb_dispose(VALUE self)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);

			EventsWrapper::unregister_event(self);

			joy_event->dispose();

			return Qnil;
		}

		VALUE JoyEventWrapper::rb_disposed(VALUE self)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);
			
			return joy_event->disposed ? Qtrue : Qfalse;
		}

		VALUE JoyEventWrapper::rb_get_proc_count(VALUE self, VALUE event_type)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);
			return INT2FIX(joy_event->get_proc_count(FIX2INT(event_type)));
		}

		VALUE JoyEventWrapper::rb_run_axis(VALUE self, VALUE stick_num, VALUE axis_num, VALUE axis_val)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);

			joy_event->call_procs_axis(FIX2INT(stick_num), FIX2INT(axis_num), NUM2DBL(axis_val));

			return Qnil;
		}

		VALUE JoyEventWrapper::rb_run_reconfigured(VALUE self)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);

			joy_event->call_procs_reconfigured();

			return Qnil;
		}

		VALUE JoyEventWrapper::rb_set_event_joystick(VALUE self, VALUE joystick)
		{
			Input::Joystick *joy;
			JoyEvent *joy_event;
			Data_Get_Struct(joystick, Input::Joystick, joy);
			Data_Get_Struct(self, JoyEvent, joy_event);

			joy_event->set_joystick(joy->joy);

			return Qnil;
		}


		VALUE JoyEventWrapper::rb_is_event_joystick(VALUE self, VALUE joystick)
		{
			Input::Joystick *joy;
			JoyEvent *joy_event;
			Data_Get_Struct(joystick, Input::Joystick, joy);
			Data_Get_Struct(self, JoyEvent, joy_event);

			return joy_event->is_joystick(joy->joy) ? Qtrue : Qfalse;
		}

		VALUE JoyEventWrapper::rb_get_proc_array(VALUE self, VALUE event_type)
		{
			JoyEvent *joy_event;
			Data_Get_Struct(self, JoyEvent, joy_event);

			return joy_event->get_observer_array(FIX2INT(event_type));
		}

		void JoyEventWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::JoyEvent")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rage_JoyEventClass = rb_define_class_under(rage, "JoyEvent", EventWrapper::get_ruby_class());

			VALUE events = rb_define_module_under(rage, "Events");
			rb_define_const(events, "JOYSTICK", INT2FIX(RAGE_JOYSTICK_EVENT));
			rb_define_const(events, "JOY_UP", INT2FIX(RAGE_EVENTS_JOY_UP));
			rb_define_const(events, "JOY_DOWN", INT2FIX(RAGE_EVENTS_JOY_DOWN));
			rb_define_const(events, "JOY_AXIS", INT2FIX(RAGE_EVENTS_JOY_AXIS));
			rb_define_const(events, "JOY_CONFIG", INT2FIX(RAGE_EVENTS_JOY_CONFIG));

			rb_define_alloc_func(rb_rage_JoyEventClass, JoyEventWrapper::rb_alloc);

			rb_define_method(rb_rage_JoyEventClass, "initialize", RFUNC(JoyEventWrapper::rb_initialize), -1);
			rb_define_method(rb_rage_JoyEventClass, "register", RFUNC(JoyEventWrapper::rb_register), 2);
			rb_define_method(rb_rage_JoyEventClass, "unregister", RFUNC(JoyEventWrapper::rb_unregister), 2);
			rb_define_method(rb_rage_JoyEventClass, "clear", RFUNC(JoyEventWrapper::rb_clear), 1);
			rb_define_method(rb_rage_JoyEventClass, "run", RFUNC(JoyEventWrapper::rb_run), 2);
			rb_define_method(rb_rage_JoyEventClass, "runAxisProcs", RFUNC(JoyEventWrapper::rb_run_axis), 3);
			rb_define_method(rb_rage_JoyEventClass, "runReconfiguredProcs", RFUNC(JoyEventWrapper::rb_run_reconfigured), 0);
			rb_define_method(rb_rage_JoyEventClass, "getProcCount", RFUNC(JoyEventWrapper::rb_get_proc_count), 1);
			rb_define_method(rb_rage_JoyEventClass, "getProcsAsArray", RFUNC(JoyEventWrapper::rb_get_proc_array), 1);
			rb_define_method(rb_rage_JoyEventClass, "setJoystick", RFUNC(JoyEventWrapper::rb_set_event_joystick), 1);
			rb_define_method(rb_rage_JoyEventClass, "isFromJoystick?", RFUNC(JoyEventWrapper::rb_is_event_joystick), 1);
			rb_define_method(rb_rage_JoyEventClass, "dispose", RFUNC(JoyEventWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_JoyEventClass, "disposed?", RFUNC(JoyEventWrapper::rb_disposed), 0);
		}

		VALUE JoyEventWrapper::get_ruby_class(void)
		{
			return rb_rage_JoyEventClass;
		}

		VALUE JoyEventWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rage_JoyEventClass);
		}
	}
}