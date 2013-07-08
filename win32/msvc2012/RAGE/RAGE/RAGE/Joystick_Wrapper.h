#pragma once

#include "Joystick.h"

namespace RAGE
{
	namespace Input
	{

		class JoystickWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void  rb_destroy(void *value);
			static VALUE rb_initialize(VALUE self, VALUE joystick_num);
			static VALUE rb_is_active(VALUE self);
			static VALUE rb_button_repeat(VALUE self, VALUE button_num);
			static VALUE rb_button_down(VALUE self, VALUE button_num);
			static VALUE rb_button_up(VALUE self, VALUE button_num);
			static VALUE rb_get_axis(VALUE self, VALUE stick_num, VALUE axis_num);
			static VALUE rb_get_name(VALUE self);
			static VALUE rb_get_button_name(VALUE self, VALUE button_num);
			static VALUE rb_get_stick_name(VALUE self, VALUE stick_num);
			static VALUE rb_get_axis_name(VALUE self, VALUE stick_num, VALUE axis_num);
			static VALUE rb_get_max_buttons(VALUE self);
			static VALUE rb_get_max_sticks(VALUE self);
			static VALUE rb_get_max_axis(VALUE self, VALUE stick_num);
			static VALUE rb_update(VALUE self);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_is_disposed(VALUE self);
		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};

	}
}