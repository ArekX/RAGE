#pragma once

#include "RubyInterpreter.h"
#include "JoyEvent.h"

#define RAGE_JOYSTICK_EVENT 5

namespace RAGE
{
	namespace Events
	{
		class JoyEventWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *value);
			static VALUE rb_register(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_unregister(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_clear(VALUE self, VALUE event_type);
			static VALUE rb_run(VALUE self, VALUE event_type, VALUE button_num);
			static VALUE rb_run_axis(VALUE self, VALUE stick_num, VALUE axis_num, VALUE axis_val);
			static VALUE rb_run_reconfigured(VALUE self);
			static VALUE rb_set_event_joystick(VALUE self, VALUE joystick);
			static VALUE rb_is_event_joystick(VALUE self, VALUE joystick);
			static VALUE rb_get_proc_count(VALUE self, VALUE event_type);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};
	}
}