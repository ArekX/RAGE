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

#include "JoyEvent.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_JOY_EVENT

namespace RAGE
{
	namespace Events
	{
		JoyEvent::JoyEvent(void)
		{
			disposed = false;
			joy_up_observer = rb_ary_new();
			joy_down_observer = rb_ary_new();
			joy_axis_observer = rb_ary_new();
			joy_reconf_observer = rb_ary_new();
		}

		void JoyEvent::register_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENTS_JOY_UP:
					RAGE_REGISTER_EVENT(joy_up_observer, proc);
					break;
				case RAGE_EVENTS_JOY_DOWN:
					RAGE_REGISTER_EVENT(joy_down_observer, proc);
					break;
				case RAGE_EVENTS_JOY_AXIS:
					RAGE_REGISTER_EVENT(joy_axis_observer, proc);
					break;
				case RAGE_EVENTS_JOY_CONFIG:
					RAGE_REGISTER_EVENT(joy_reconf_observer, proc);
					break;
			}
		}

		void JoyEvent::set_joystick(ALLEGRO_JOYSTICK *joy)
		{
			RAGE_CHECK_DISPOSED(disposed);

			event_set_joy = joy;
		}

		bool JoyEvent::is_joystick(ALLEGRO_JOYSTICK *check_joy)
		{
			return (check_joy == event_set_joy);
		}

		void JoyEvent::unregister_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENTS_JOY_UP:
					RAGE_UNREGISTER_EVENT(joy_up_observer, proc);
					break;
				case RAGE_EVENTS_JOY_DOWN:
					RAGE_UNREGISTER_EVENT(joy_down_observer, proc);
					break;
				case RAGE_EVENTS_JOY_AXIS:
					RAGE_UNREGISTER_EVENT(joy_axis_observer, proc);
					break;
				case RAGE_EVENTS_JOY_CONFIG:
					RAGE_UNREGISTER_EVENT(joy_reconf_observer, proc);
					break;
			}
		}

		int JoyEvent::get_proc_count(int type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			switch(type)
			{
				case RAGE_EVENTS_JOY_UP:
					return RARRAY_LEN(joy_up_observer);

				case RAGE_EVENTS_JOY_DOWN:
					return RARRAY_LEN(joy_down_observer);

				case RAGE_EVENTS_JOY_AXIS:
					return RARRAY_LEN(joy_axis_observer);

				case RAGE_EVENTS_JOY_CONFIG:
					return RARRAY_LEN(joy_reconf_observer);

				default:
					return -1;
			}
		}

		void JoyEvent::clear_procs(int type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENTS_JOY_UP:
					rb_ary_clear(joy_up_observer);
					break;
				case RAGE_EVENTS_JOY_DOWN:
					rb_ary_clear(joy_down_observer);
					break;
				case RAGE_EVENTS_JOY_AXIS:
					rb_ary_clear(joy_axis_observer);
					break;
				case RAGE_EVENTS_JOY_CONFIG:
					rb_ary_clear(joy_reconf_observer);
			}
		}
		
		void JoyEvent::call_procs_button(int type, int button_num)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (type == RAGE_EVENTS_JOY_UP)
				run_button_procs(&joy_up_observer, button_num);
			else if (type == RAGE_EVENTS_JOY_DOWN)
				run_button_procs(&joy_down_observer, button_num);
		}

		void JoyEvent::call_procs_axis(int stick_num, int axis_num, float axis_pos)
		{
			RAGE_CHECK_DISPOSED(disposed);

			run_axis_procs(stick_num, axis_num, axis_pos);
		}

		void JoyEvent::call_procs_reconfigured(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			run_reconf_procs();
		}

		void JoyEvent::run_button_procs(VALUE *observer, int button_num)
		{
			for (int i = 0; i < RARRAY_LEN(*observer); i++)
			{
				vals[0] = INT2FIX(button_num);
				rb_proc_call_with_block(rb_ary_entry(*observer, i), 1, vals, 
								        rb_ary_entry(*observer, i));
			}
		}

		void JoyEvent::run_axis_procs(int stick_num, int axis_num, float axis_pos)
		{
			
			for (int i = 0; i < RARRAY_LEN(joy_axis_observer); i++)
			{
				vals[0] = INT2FIX(stick_num);
				vals[1] = INT2FIX(axis_num);
				vals[2] = DBL2NUM(axis_pos);
				rb_proc_call_with_block(rb_ary_entry(joy_axis_observer, i), 3, vals, 
								        rb_ary_entry(joy_axis_observer, i));
			}
		}

		void JoyEvent::run_reconf_procs(void)
		{
			for (int i = 0; i < RARRAY_LEN(joy_reconf_observer); i++)
			{
				
				rb_proc_call_with_block(rb_ary_entry(joy_reconf_observer, i), 0, nullptr, 
								        rb_ary_entry(joy_reconf_observer, i));
			}
		}

		void JoyEvent::callback(ALLEGRO_EVENT *ev)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ev->type == ALLEGRO_EVENT_JOYSTICK_CONFIGURATION)
				run_reconf_procs();
			else
				event_set_joy = ev->joystick.id;

			if (ev->type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
				run_button_procs(&joy_down_observer, ev->joystick.button);
			
			else if (ev->type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
				run_button_procs(&joy_up_observer, ev->joystick.button);
			
			if (ev->type == ALLEGRO_EVENT_JOYSTICK_AXIS)
				run_axis_procs(ev->joystick.stick, ev->joystick.axis, ev->joystick.pos);
		}

		void JoyEvent::gc_mark(void)
		{
			rb_gc_mark(joy_up_observer);
			rb_gc_mark(joy_down_observer);
			rb_gc_mark(joy_axis_observer);
			rb_gc_mark(joy_reconf_observer);
			rb_gc_mark(vals[0]);
			rb_gc_mark(vals[1]);
			rb_gc_mark(vals[2]);
		}

		void JoyEvent::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rb_ary_clear(joy_up_observer);
			rb_ary_clear(joy_down_observer);
			rb_ary_clear(joy_axis_observer);
			rb_ary_clear(joy_reconf_observer);

			disposed = true;
		}

		VALUE JoyEvent::get_observer_array(int type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			switch(type)
			{
				case RAGE_EVENTS_JOY_UP:
					return rb_obj_clone(joy_up_observer);
					
				case RAGE_EVENTS_JOY_DOWN:
					return rb_obj_clone(joy_down_observer);
					
				case RAGE_EVENTS_JOY_AXIS:
					return rb_obj_clone(joy_axis_observer);
					
				case RAGE_EVENTS_JOY_CONFIG:
					return rb_obj_clone(joy_reconf_observer);

				default:
					return Qnil;
			}
		}

		JoyEvent::~JoyEvent(void)
		{
			if (!disposed)
				dispose();
		}

	}
}

#endif