#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Input
	{

		class Joystick
		{
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