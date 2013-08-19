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
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(int joy_num);
		};

	}
}