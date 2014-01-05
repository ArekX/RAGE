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

#include "Joystick_Wrapper.h"
#include "Joystick.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_INPUT && RAGE_COMPILE_JOYSTICK

namespace RAGE
{
	namespace Input
	{
		VALUE rb_rage_JoystickClass;

		VALUE JoystickWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, JoystickWrapper::rb_destroy, new Joystick());
		}

		void JoystickWrapper::rb_destroy(void* ptr)
		{
			delete ptr;
		}

		VALUE JoystickWrapper::rb_initialize(VALUE self, VALUE joystick_num) 
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			joy->initialize(FIX2INT(joystick_num));

			return Qnil;
		}
		
		VALUE JoystickWrapper::rb_is_active(VALUE self) 
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			if (joy->is_joystick_active())
				return Qtrue;

			return Qfalse;
		}
		
		VALUE JoystickWrapper::rb_button_repeat(VALUE self, VALUE button_num) 
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return joy->is_button_repeat(FIX2INT(button_num)) ? Qtrue : Qfalse;
		}
		
		VALUE JoystickWrapper::rb_button_down(VALUE self, VALUE button_num) 
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return joy->is_button_down(FIX2INT(button_num)) ? Qtrue : Qfalse;
		}

		VALUE JoystickWrapper::rb_button_up(VALUE self, VALUE button_num) 
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return joy->is_button_up(FIX2INT(button_num)) ? Qtrue : Qfalse;
		}
		
		VALUE JoystickWrapper::rb_get_axis(VALUE self, VALUE stick_num, VALUE axis_num) 
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return DBL2NUM(joy->get_axis(FIX2INT(stick_num), FIX2INT(axis_num)));
		}

		VALUE JoystickWrapper::rb_get_name(VALUE self) 
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return rb_str_new2(joy->get_name());
		}
		
		VALUE JoystickWrapper::rb_get_button_name(VALUE self, VALUE button_num)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return rb_str_new2(joy->get_button_name(FIX2INT(button_num)));
		}

		VALUE JoystickWrapper::rb_get_stick_name(VALUE self, VALUE stick_num)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return rb_str_new2(joy->get_stick_name(FIX2INT(stick_num)));
		}

		VALUE JoystickWrapper::rb_get_axis_name(VALUE self, VALUE stick_num, VALUE axis_num)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return rb_str_new2(joy->get_axis_name(FIX2INT(stick_num), FIX2UINT(axis_num)));
		}

		VALUE JoystickWrapper::rb_get_max_buttons(VALUE self)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return INT2FIX(joy->get_button_max());
		}

		VALUE JoystickWrapper::rb_get_max_sticks(VALUE self)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return INT2FIX(joy->get_stick_max());
		}

		VALUE JoystickWrapper::rb_get_max_axis(VALUE self, VALUE stick_num)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			return INT2FIX(joy->get_axis_max(FIX2INT(stick_num)));
		}

		VALUE JoystickWrapper::rb_update(VALUE self)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			joy->update();

			return Qnil;
		}

		VALUE JoystickWrapper::rb_dispose(VALUE self)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);

			joy->dispose();

			return Qnil;
		}

		VALUE JoystickWrapper::rb_is_disposed(VALUE self)
		{
			Joystick *joy;
			Data_Get_Struct(self, Joystick, joy);
			
			return (joy->disposed) ? Qtrue : Qfalse;
		}

		void JoystickWrapper::load_ruby_class(void) 
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Joystick")) return;

			VALUE rage = rb_define_module("RAGE");

			rb_rage_JoystickClass = rb_define_class_under(rage, "Joystick", rb_cObject);

			rb_define_alloc_func(rb_rage_JoystickClass, JoystickWrapper::rb_alloc);

			rb_define_method(rb_rage_JoystickClass, "initialize", RFUNC(JoystickWrapper::rb_initialize), 1);
			rb_define_method(rb_rage_JoystickClass, "isActive?", RFUNC(JoystickWrapper::rb_is_active), 0);
			rb_define_method(rb_rage_JoystickClass, "buttonRepeat?", RFUNC(JoystickWrapper::rb_button_repeat), 1);
			rb_define_method(rb_rage_JoystickClass, "buttonDown?", RFUNC(JoystickWrapper::rb_button_down), 1);
			rb_define_method(rb_rage_JoystickClass, "buttonUp?", RFUNC(JoystickWrapper::rb_button_up), 1);
			rb_define_method(rb_rage_JoystickClass, "getAxis", RFUNC(JoystickWrapper::rb_get_axis), 2);
			rb_define_method(rb_rage_JoystickClass, "getName", RFUNC(JoystickWrapper::rb_get_name), 0);
			rb_define_method(rb_rage_JoystickClass, "getButtonName", RFUNC(JoystickWrapper::rb_get_button_name), 1);
			rb_define_method(rb_rage_JoystickClass, "getStickName", RFUNC(JoystickWrapper::rb_get_stick_name), 1);
			rb_define_method(rb_rage_JoystickClass, "getAxisName", RFUNC(JoystickWrapper::rb_get_axis_name), 2);
			rb_define_method(rb_rage_JoystickClass, "getMaxButtons", RFUNC(JoystickWrapper::rb_get_max_buttons), 0);
			rb_define_method(rb_rage_JoystickClass, "getMaxSticks", RFUNC(JoystickWrapper::rb_get_max_sticks), 0);
			rb_define_method(rb_rage_JoystickClass, "getMaxAxis", RFUNC(JoystickWrapper::rb_get_max_axis), 1);
			rb_define_method(rb_rage_JoystickClass, "update", RFUNC(JoystickWrapper::rb_update), 0);
			rb_define_method(rb_rage_JoystickClass, "dispose", RFUNC(JoystickWrapper::rb_dispose), 0);
			rb_define_method(rb_rage_JoystickClass, "disposed?", RFUNC(JoystickWrapper::rb_is_disposed), 0);

		}

		VALUE JoystickWrapper::get_ruby_class(void) 
		{
			return rb_rage_JoystickClass;
		}

		VALUE JoystickWrapper::new_ruby_class_instance(int joy_num)
		{
			VALUE jnum = FIX2UINT(joy_num);
			return rb_class_new_instance(1, &jnum, rb_rage_JoystickClass);
		}
	}
}

#endif