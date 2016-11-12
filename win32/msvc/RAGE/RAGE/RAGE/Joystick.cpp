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

#include "Joystick.h"

#if RAGE_COMPILE_INPUT && RAGE_COMPILE_JOYSTICK

namespace RAGE
{
	namespace Input
	{

		Joystick::Joystick(void)
		{
			disposed = false;
			buttons_num = 0;
			sticks_num = 0;

			memset(&js, 0, sizeof(ALLEGRO_JOYSTICK_STATE));
			memset(&js_old, 0, sizeof(ALLEGRO_JOYSTICK_STATE));
		}

		void Joystick::initialize(int joy_num)
		{
			joy = al_get_joystick(joy_num);

			if (joy == nullptr)
			{
				rb_raise(rb_eArgError, RAGE_JOYSTICK_NOT_FOUND_ERROR, joy_num);
				return;
			}

			buttons_num = al_get_joystick_num_buttons(joy);
			sticks_num = al_get_joystick_num_sticks(joy);

			axes_nums = new int[sticks_num];

			for (int i = 0; i < sticks_num; i++)
				axes_nums[i] = al_get_joystick_num_axes(joy, i);
		}

		bool Joystick::is_joystick_active(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return al_get_joystick_active(joy);
		}

		void Joystick::update(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			js_old = js;
			al_get_joystick_state(joy, &js);
		}

		bool Joystick::is_button_repeat(int button_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if ((button_num < 0) || (button_num >= buttons_num)) return false;

			if (js.button[button_num])
				return true;

			return false;
		}

		bool Joystick::is_button_down(int button_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if ((button_num < 0) || (button_num >= buttons_num)) return false;

			if (js.button[button_num] && !js_old.button[button_num])
				return true;

			return false;
		}

		bool Joystick::is_button_up(int button_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if ((button_num < 0) || (button_num >= buttons_num)) return false;

			if (!js.button[button_num] && js_old.button[button_num])
				return true;

			return false;
		}

		float Joystick::get_axis(int stick_num, int axis_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if ((stick_num < 0) || (stick_num >= sticks_num)) return 0;
			if ((axis_num < 0) || (axis_num >= axes_nums[stick_num])) return 0;

			return js.stick[stick_num].axis[axis_num];
		}

		const char* Joystick::get_name(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, nullptr);

			return al_get_joystick_name(joy);
		}

		const char* Joystick::get_button_name(int button_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, nullptr);

			return al_get_joystick_button_name(joy, button_num);
		}

		const char* Joystick::get_stick_name(int stick_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, nullptr);

			return al_get_joystick_stick_name(joy, stick_num);
		}

		const char* Joystick::get_axis_name(int stick_num, int axis_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, nullptr);

			return al_get_joystick_axis_name(joy, stick_num, axis_num);
		}

		int Joystick::get_button_max(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return buttons_num;
		}

		int Joystick::get_stick_max(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return sticks_num;
		}

		int Joystick::get_axis_max(int stick_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if ((stick_num < 0) || (stick_num >= sticks_num)) return 0;

			return axes_nums[stick_num];
		}

		void Joystick::dispose(void)
		{
			if (disposed)
				return;

			disposed = true;

			delete[] axes_nums;
		}

		Joystick::~Joystick(void)
		{
			if (!disposed)
				dispose();
		}

	}
}

#endif