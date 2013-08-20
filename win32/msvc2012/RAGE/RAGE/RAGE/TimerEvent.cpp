/*
Copyright (c) 2013 Aleksandar Panic

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

#include "TimerEvent.h"

namespace RAGE
{
	namespace Events
	{

		TimerEvent::TimerEvent()
		{
			timer_observer = rb_ary_new();
			disposed = false;
			timer_queue = NULL;
			timer = NULL;
		}

		void TimerEvent::initialize(double seconds)
		{
			RAGE_CHECK_DISPOSED(disposed);

			timer = al_create_timer(seconds);

			if (timer == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_TIMER_FAIL);
				return;
			}
		}

		void TimerEvent::register_to_queue(ALLEGRO_EVENT_QUEUE *queue)
		{
			RAGE_CHECK_DISPOSED(disposed);

			timer_queue = queue;
			al_register_event_source(timer_queue, al_get_timer_event_source(timer));
		}

		void TimerEvent::unregister_from_queue(ALLEGRO_EVENT_QUEUE *queue)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (timer_queue != NULL)
				al_unregister_event_source(timer_queue, al_get_timer_event_source(timer));

			timer_queue = NULL;
		}

		void TimerEvent::clear(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rb_ary_clear(timer_observer);
		}

		void TimerEvent::start(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((timer != NULL) && !al_get_timer_started(timer))
				al_start_timer(timer);
		}

		void TimerEvent::stop(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((timer != NULL) && al_get_timer_started(timer))
				al_stop_timer(timer);
		}

		int64_t TimerEvent::get_count(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (timer != NULL)
				return al_get_timer_count(timer);
			else
				return -1;
		}

		int TimerEvent::get_proc_count(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (timer != NULL)
				return RARRAY_LEN(timer_observer);
			else
				return -1;
		}

		void TimerEvent::run_procs(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			for (int i = 0; i < RARRAY_LEN(timer_observer); i++)
			{
				rb_proc_call_with_block(rb_ary_entry(timer_observer, i), 0, NULL, 
										rb_ary_entry(timer_observer, i));
			}
		}

		void TimerEvent::set_count(int64_t count)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((timer != NULL) && al_get_timer_started(timer))
				al_set_timer_count(timer, count);
		}


		void TimerEvent::set_speed(double speed)
		{
			RAGE_CHECK_DISPOSED(disposed);
			if (timer != NULL)
				al_set_timer_speed(timer, speed);
		}

		double TimerEvent::get_speed(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (timer != NULL)
				return al_get_timer_speed(timer);
			else
				return 0;
		}

		bool TimerEvent::started(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (timer != NULL)
				return al_get_timer_started(timer);
			else 
				return false;
		}

		void TimerEvent::dispose(void)
		{
			if (timer_queue != NULL)
				al_unregister_event_source(timer_queue, al_get_timer_event_source(timer));

			if (timer != NULL)
				al_destroy_timer(timer);

			rb_ary_clear(timer_observer);
			rb_gc_force_recycle(timer_observer);

			disposed = true;
		}

		void TimerEvent::register_callback(VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (TYPE(rb_ary_includes(timer_observer, proc)) == T_FALSE) 
			{ 
				if (rb_class_of(proc) != rb_cProc) 
					rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); 
				else 
					rb_ary_push(timer_observer, proc);
			}
		}

		void TimerEvent::unregister_callback(VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (TYPE(rb_ary_includes(timer_observer, proc)) == T_TRUE) 
			{ 
				if (rb_class_of(proc) != rb_cProc) 
					rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); 
				else
					rb_ary_delete(timer_observer, proc);
			}
		}

		void TimerEvent::gc_mark(void)
		{
			rb_gc_mark(timer_observer);
		}

		void TimerEvent::callback(ALLEGRO_EVENT *ev)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((ev->type == ALLEGRO_EVENT_TIMER) && (ev->timer.source == timer))
				run_procs();
		}

		VALUE TimerEvent::get_observer_array(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			return rb_obj_clone(timer_observer);
		}

		TimerEvent::~TimerEvent(void)
		{
			if (!disposed)
				dispose();
		}

	}
}