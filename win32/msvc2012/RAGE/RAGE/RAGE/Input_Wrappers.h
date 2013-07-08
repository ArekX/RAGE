#pragma once

#include "RubyInterpreter.h"

#define RAGE_MOUSE_BUTTON_1 1
#define RAGE_MOUSE_BUTTON_2 2
#define RAGE_MOUSE_BUTTON_3 4

#define RDEF_KEY(name, keycode) rb_define_const(input, name, INT2FIX(keycode));

namespace RAGE
{
	namespace Input
	{
		class InputWrappers
		{
		private:
			static VALUE rb_key_is_down(VALUE self, VALUE keycode);
			static VALUE rb_key_is_up(VALUE self, VALUE keycode);
			static VALUE rb_key_is_repeat(VALUE self, VALUE keycode);
			static VALUE rb_keyboard_update(VALUE self);
			static VALUE rb_joystick_max(VALUE self);
			static VALUE rb_mouse_update(VALUE self);
			static VALUE rb_mouse_down(VALUE self, VALUE button);
			static VALUE rb_mouse_up(VALUE self, VALUE button);
			static VALUE rb_mouse_repeat(VALUE self, VALUE button);
			static VALUE rb_mouse_x(VALUE self);
			static VALUE rb_mouse_y(VALUE self);
			static VALUE rb_reconfigure_joysticks(VALUE self);
		public:
			static void load_wrappers();
		};

	}
}

