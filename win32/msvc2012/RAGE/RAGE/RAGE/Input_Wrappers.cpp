#include "Input_Wrappers.h"


namespace RAGE
{
	namespace Input
	{
		ALLEGRO_KEYBOARD_STATE ks;
		ALLEGRO_JOYSTICK_STATE js;
		ALLEGRO_MOUSE_STATE ms;
		
		VALUE InputWrappers::rb_keyboard_update(VALUE self)
		{
			al_get_keyboard_state(&ks);
			return Qnil;
		}

		VALUE InputWrappers::rb_joystick_update(VALUE self, VALUE joystick_num)
		{
			al_get_joystick_state(al_get_joystick(FIX2INT(joystick_num)), &js);
			return Qnil;
		}

		VALUE InputWrappers::rb_key_is_down(VALUE self, VALUE keycode)
		{
			if (al_key_down(&ks, FIX2INT(keycode)))
				return Qtrue;
			else
				return Qfalse;
		}

		VALUE InputWrappers::rb_joystick_down(VALUE self, VALUE button)
		{
			if (*(js.button) == FIX2INT(button))
				return Qtrue;
			else
				return Qfalse;
		}

		VALUE InputWrappers::rb_joystick_max(VALUE self)
		{
			return INT2FIX(al_get_num_joysticks());
		}

		VALUE InputWrappers::rb_mouse_update(VALUE self)
		{
			
			al_get_mouse_state(&ms);
			return Qnil;
		}

		VALUE InputWrappers::rb_mouse_down(VALUE self, VALUE button)
		{
			if (ms.buttons == FIX2INT(button))
				return Qtrue;
			else
				return Qfalse;
		}

		VALUE InputWrappers::rb_mouse_x(VALUE self)
		{
			return INT2FIX(ms.x);
		}

		VALUE InputWrappers::rb_mouse_y(VALUE self)
		{
			return INT2FIX(ms.y);
		}

		void InputWrappers::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE input = rb_define_module_under(rage, "Input");
			rb_define_const(input, "MOUSE_BTN1", INT2FIX(RAGE_MOUSE_BUTTON_1));
			rb_define_const(input, "MOUSE_BTN2", INT2FIX(RAGE_MOUSE_BUTTON_2));
			rb_define_const(input, "MOUSE_BTN3", INT2FIX(RAGE_MOUSE_BUTTON_3));

			#include "Keyboard_Consts.inc"

			rb_define_module_function(input, "updateKeyboard", RFUNC(InputWrappers::rb_keyboard_update), 0);
			rb_define_module_function(input, "updateMouse", RFUNC(InputWrappers::rb_mouse_update), 0);
			rb_define_module_function(input, "isKeyDown?", RFUNC(InputWrappers::rb_key_is_down), 1);
			rb_define_module_function(input, "updateJoystick", RFUNC(InputWrappers::rb_joystick_update), 1);
			rb_define_module_function(input, "getMaxJoysticks", RFUNC(InputWrappers::rb_joystick_max), 0);
			rb_define_module_function(input, "isMouseDown?", RFUNC(InputWrappers::rb_mouse_down), 1);
			rb_define_module_function(input, "getMouseX", RFUNC(InputWrappers::rb_mouse_x), 0);
			rb_define_module_function(input, "getMouseY", RFUNC(InputWrappers::rb_mouse_y), 0);

			// TODO: Finish joystick (test it), finish keyboard constants, other stuff...
		}
	}
}
