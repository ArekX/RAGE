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

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_MOUSE_EVENT

#define RAGE_EVENT_MOUSE_DOWN 4
#define RAGE_EVENT_MOUSE_UP 5
#define RAGE_EVENT_MOUSE_MOVE 6
#define RAGE_EVENT_MOUSE_ENTER 7
#define RAGE_EVENT_MOUSE_LEAVE 8

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
			VALUE get_observer_array(int type);
			~MouseEvent(void);
		};
	}
}

#endif