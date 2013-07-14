#pragma once

#include "RubyInterpreter.h"

#define RAGE_EVENT_MOUSE_DOWN 4
#define RAGE_EVENT_MOUSE_UP 5
#define RAGE_EVENT_MOUSE_MOVE 6
#define RAGE_EVENT_MOUSE_ENTER 7
#define RAGE_EVENT_MOUSE_LEAVE 8

#include "BaseEvent.h"

namespace RAGE
{
	namespace Events
	{
		class MouseEvent : public BaseEvent
		{
		private:
			void run_procs(VALUE *observer, unsigned int *buttons, int *x, int *y, int *wheel);
			VALUE *mouse_args;
			VALUE mouse_up_observer;
			VALUE mouse_down_observer;
			VALUE mouse_enter_observer;
			VALUE mouse_leave_observer;
			VALUE mouse_move_observer;
		public:
			MouseEvent(void);
			void register_proc(int type, VALUE proc);
			void unregister_proc(int type, VALUE proc);
			int get_proc_count(int type);
			void clear_procs(int type);
			void call_procs(int type, unsigned int buttons, int x, int y, int wheel);
			void callback(ALLEGRO_EVENT *ev);
			void gc_mark(void);
			void dispose(void);
			~MouseEvent(void);
		};
	}
}