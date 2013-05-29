#pragma once
#include "RubyInterpreter.h"
#include "BaseEvent.h"

#define RAGE_EVENT_SCREEN_CLOSE 9
#define RAGE_EVENT_SCREEN_FOCUS 10
#define RAGE_EVENT_SCREEN_LOST 11
#define RAGE_EVENT_SCREEN_RESIZE 12

namespace RAGE
{
	namespace Events
	{

		class ScreenEvent :
			public BaseEvent
		{
		private:
			void run_procs(VALUE *observer);
			VALUE screen_close_observer;
			VALUE screen_focus_observer;
			VALUE screen_lost_observer;
			VALUE screen_resize_observer;
			bool disposed;
		public:
			ScreenEvent(void);
			void register_proc(int type, VALUE proc);
			void unregister_proc(int type, VALUE proc);
			int get_proc_count(int type);
			void clear_procs(int type);
			void call_procs(int type);
			void callback(ALLEGRO_EVENT *ev);
			void dispose();
			~ScreenEvent(void);
		};


	}
}