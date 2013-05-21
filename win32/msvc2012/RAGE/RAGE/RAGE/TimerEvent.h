#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Events
	{

		class TimerEvent
		{
		private:
			ALLEGRO_EVENT_QUEUE *timer_queue;
			ALLEGRO_TIMER *timer;
			VALUE timerObserver;
			bool disposed;
		public:
			TimerEvent();
			void initialize(double seconds);
			void register_to_queue(ALLEGRO_EVENT_QUEUE *queue);
			void unregister_from_queue(ALLEGRO_EVENT_QUEUE *queue);
			void start();
			void stop();
			int64_t get_count();
			void set_count(int64_t count);
			void set_speed(double speed);
			double get_speed();
			bool started();
			void dispose();
			void clear();
			void register_callback(VALUE proc);
			void unregister_callback(VALUE proc);
			void callback(ALLEGRO_EVENT *ev);
			~TimerEvent(void);
		};

	}
}
