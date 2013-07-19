#include "Joystick.h"

namespace RAGE
{
	namespace Input
	{

		Joystick::Joystick(void)
		{
			disposed = false;
		}

		void Joystick::initialize(int joy_num)
		{
			joy = al_get_joystick(joy_num);

			if (joy == NULL)
			{
				rb_raise(rb_eArgError, RAGE_JOYSTICK_NOT_FOUND_ERROR, joy_num);
				return;
			}
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

			if (button_num > _AL_MAX_JOYSTICK_BUTTONS) return false;

			if (js.button[button_num])
				return true;

			return false;
		}

		bool Joystick::is_button_down(int button_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (button_num > _AL_MAX_JOYSTICK_BUTTONS) return false;

			if (js.button[button_num] && !js_old.button[button_num])
				return true;

			return false;
		}

		bool Joystick::is_button_up(int button_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (button_num > _AL_MAX_JOYSTICK_BUTTONS) return false;

			if (!js.button[button_num] && js_old.button[button_num])
				return true;

			return false;
		}

		float Joystick::get_axis(int stick_num, int axis_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (stick_num > _AL_MAX_JOYSTICK_STICKS) return 0;
			if (axis_num > _AL_MAX_JOYSTICK_AXES) return 0;

			return js.stick[stick_num].axis[axis_num];
		}

		const char* Joystick::get_name(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			return al_get_joystick_name(joy);
		}

		const char* Joystick::get_button_name(int button_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			return al_get_joystick_button_name(joy, button_num);
		}

		const char* Joystick::get_stick_name(int stick_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			return al_get_joystick_stick_name(joy, stick_num);
		}

		const char* Joystick::get_axis_name(int stick_num, int axis_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			return al_get_joystick_axis_name(joy, stick_num, axis_num);
		}

		int Joystick::get_button_max(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_joystick_num_buttons(joy);
		}

		int Joystick::get_stick_max(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_joystick_num_sticks(joy);
		}

		int Joystick::get_axis_max(int stick_num)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_joystick_num_axes(joy, stick_num);
		}

		void Joystick::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			disposed = true;
		}

		Joystick::~Joystick(void)
		{
			if (!disposed)
				dispose();
		}

	}
}