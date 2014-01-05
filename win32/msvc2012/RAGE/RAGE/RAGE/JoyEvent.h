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
#include "BaseEvent.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_JOY_EVENT

#define RAGE_EVENTS_JOY_UP 13
#define RAGE_EVENTS_JOY_DOWN 14
#define RAGE_EVENTS_JOY_AXIS 15
#define RAGE_EVENTS_JOY_CONFIG 16

namespace RAGE
{
	namespace Events
	{
		class JoyEvent : 
			public BaseEvent
		{
		private:
			void run_button_procs(VALUE *observer, int button_num);
			void run_axis_procs(int stick_num, int axis_num, float axis_pos);
			void run_reconf_procs(void);
			VALUE joy_up_observer;
			VALUE joy_down_observer;
			VALUE joy_axis_observer;
			VALUE joy_reconf_observer;
			VALUE vals[3];
			ALLEGRO_JOYSTICK *event_set_joy;
		public:
			JoyEvent(void);
			bool is_joystick(ALLEGRO_JOYSTICK *check_joy);
			void register_proc(int type, VALUE proc);
			void unregister_proc(int type, VALUE proc);
			int get_proc_count(int type);
			void clear_procs(int type);
			void call_procs_button(int type, int button_num);
			void call_procs_axis(int stick_num, int axis_num, float axis_pos);
			void call_procs_reconfigured(void);
			void callback(ALLEGRO_EVENT *ev);
			void gc_mark(void);
			void dispose(void);
			void set_joystick(ALLEGRO_JOYSTICK *joy);
			VALUE get_observer_array(int type);
			~JoyEvent(void);
		};

	}
}

#endif