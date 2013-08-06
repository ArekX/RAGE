#pragma once
#include "RubyInterpreter.h"

#define RAGE_EVENTS_JOY_UP 13
#define RAGE_EVENTS_JOY_DOWN 14
#define RAGE_EVENTS_JOY_AXIS 15
#define RAGE_EVENTS_JOY_CONFIG 16

#include "BaseEvent.h"


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
