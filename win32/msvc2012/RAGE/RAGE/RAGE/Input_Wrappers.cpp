#include "Input_Wrappers.h"


namespace RAGE
{
	namespace Input
	{
		ALLEGRO_KEYBOARD_STATE ks_old, ks;
		ALLEGRO_MOUSE_STATE ms_old, ms;
		
		VALUE InputWrappers::rb_keyboard_update(VALUE self)
		{
			ks_old = ks;
			al_get_keyboard_state(&ks);
			return Qnil;
		}

		VALUE InputWrappers::rb_key_is_down(VALUE self, VALUE keycode)
		{
			if (al_key_down(&ks, FIX2INT(keycode)) && !al_key_down(&ks_old, FIX2INT(keycode)))
			{
				return Qtrue;
			}
			else
			{
				return Qfalse;
			}
		}

		VALUE InputWrappers::rb_key_is_up(VALUE self, VALUE keycode)
		{
			if (!al_key_down(&ks, FIX2INT(keycode)) && al_key_down(&ks_old, FIX2INT(keycode)))
			{
				return Qtrue;
			}
			else
			{
				return Qfalse;
			}
		}

		VALUE InputWrappers::rb_key_is_repeat(VALUE self, VALUE keycode)
		{
			if (al_key_down(&ks, FIX2INT(keycode)))
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
			ms_old = ms;
			al_get_mouse_state(&ms);
			return Qnil;
		}

		VALUE InputWrappers::rb_mouse_repeat(VALUE self, VALUE button)
		{
			if (al_mouse_button_down(&ms, FIX2INT(button)))
				return Qtrue;
			else
				return Qfalse;
		}

		VALUE InputWrappers::rb_mouse_down(VALUE self, VALUE button)
		{
			
			if (al_mouse_button_down(&ms, FIX2INT(button)) && !al_mouse_button_down(&ms_old, FIX2INT(button)))
			{
				return Qtrue;
			}
			else
			{
				return Qfalse;
			}
		}

		VALUE InputWrappers::rb_mouse_up(VALUE self, VALUE button)
		{
			if (!al_mouse_button_down(&ms, FIX2INT(button)) && al_mouse_button_down(&ms_old, FIX2INT(button)))
			{
				return Qtrue;
			}
			else
			{
				return Qfalse;
			}
		}

		VALUE InputWrappers::rb_mouse_x(VALUE self)
		{
			return INT2FIX(ms.x);
		}

		VALUE InputWrappers::rb_mouse_y(VALUE self)
		{
			return INT2FIX(ms.y);
		}

		VALUE InputWrappers::rb_reconfigure_joysticks(VALUE self)
		{
			return (al_reconfigure_joysticks() == true) ? Qtrue : Qfalse;
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
			rb_define_module_function(input, "keyDown?", RFUNC(InputWrappers::rb_key_is_down), 1);
			rb_define_module_function(input, "keyUp?", RFUNC(InputWrappers::rb_key_is_up), 1);
			rb_define_module_function(input, "keyRepeat?", RFUNC(InputWrappers::rb_key_is_repeat), 1);
			rb_define_module_function(input, "mouseDown?", RFUNC(InputWrappers::rb_mouse_down), 1);
			rb_define_module_function(input, "mouseUp?", RFUNC(InputWrappers::rb_mouse_up), 1);
			rb_define_module_function(input, "mouseRepeat?", RFUNC(InputWrappers::rb_mouse_repeat), 1);
			rb_define_module_function(input, "getMouseX", RFUNC(InputWrappers::rb_mouse_x), 0);
			rb_define_module_function(input, "getMouseY", RFUNC(InputWrappers::rb_mouse_y), 0);
			rb_define_module_function(input, "reconfigureJoysticks", RFUNC(InputWrappers::rb_reconfigure_joysticks), 0);
			rb_define_module_function(input, "getMaxJoysticks", RFUNC(InputWrappers::rb_joystick_max), 0);

		}
	}
}
