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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_INPUT

#define RAGE_MOUSE_BUTTON_1 1
#define RAGE_MOUSE_BUTTON_2 2
#define RAGE_MOUSE_BUTTON_3 4

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
			static void load_wrappers(void);
		};

	}
}

#endif