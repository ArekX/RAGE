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

#pragma once

#include "rage_standard_headers.h"
#include "BaseEvent.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_TIMER_EVENT

namespace RAGE
{
	namespace Events
	{

		class TimerEvent : public BaseEvent
		{
		private:
			ALLEGRO_EVENT_QUEUE *timer_queue;
			ALLEGRO_TIMER *timer;
			VALUE timer_observer;
		public:
			TimerEvent(void);
			void initialize(double seconds);
			void register_to_queue(ALLEGRO_EVENT_QUEUE *queue);
			void unregister_from_queue(ALLEGRO_EVENT_QUEUE *queue);
			void start(void);
			void stop(void);
			int64_t get_count(void);
			int get_proc_count(void);
			void set_count(int64_t count);
			void set_speed(double speed);
			double get_speed(void);
			bool started(void);
			void gc_mark(void);
			void dispose(void);
			void clear(void);
			void run_procs(void);
			void register_callback(VALUE proc);
			void unregister_callback(VALUE proc);
			void callback(ALLEGRO_EVENT *ev);
			VALUE get_observer_array(void);
			~TimerEvent(void);
		};

	}
}

#endif