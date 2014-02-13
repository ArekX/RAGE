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

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_SCREEN_EVENT

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
		public:
			ScreenEvent(void);
			void register_proc(int type, VALUE proc);
			void unregister_proc(int type, VALUE proc);
			int get_proc_count(int type);
			void clear_procs(int type);
			void call_procs(int type);
			void callback(ALLEGRO_EVENT *ev);
			void gc_mark(void);
			void dispose(void);
			VALUE get_observer_array(int type);
			~ScreenEvent(void);
		};


	}
}

#endif