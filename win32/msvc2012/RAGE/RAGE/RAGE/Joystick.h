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

#if RAGE_COMPILE_INPUT && RAGE_COMPILE_JOYSTICK

namespace RAGE
{
	namespace Input
	{

		class Joystick
		{
		private:
			int buttons_num;
			int sticks_num;
			int *axes_nums;
		public:
			bool disposed;
			ALLEGRO_JOYSTICK *joy;
			ALLEGRO_JOYSTICK_STATE js, js_old;
			void initialize(int joy_num);
			bool is_joystick_active(void);
			bool is_button_repeat(int button_num);
			bool is_button_down(int button_num);
			bool is_button_up(int button_num);
			float get_axis(int stick_num, int axis_num);
			const char* get_name(void);
			const char* get_button_name(int button_num);
			const char* get_stick_name(int stick_num);
			const char* get_axis_name(int stick_num, int axis_num);
			int get_button_max(void);
			int get_stick_max(void);
			int get_axis_max(int stick_num);
			void update(void);
			void dispose(void);
			Joystick(void);
			~Joystick(void);
		};

	}

}
#endif