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

#include "Input_Wrappers.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_INPUT

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


		void InputWrappers::load_wrappers(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Input")) return;

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

#endif
