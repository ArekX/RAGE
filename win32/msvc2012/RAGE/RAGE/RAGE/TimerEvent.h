#pragma once

#include "RubyInterpreter.h"

#include "BaseEvent.h"

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
