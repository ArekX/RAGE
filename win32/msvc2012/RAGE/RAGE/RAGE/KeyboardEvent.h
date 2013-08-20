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
#include "RubyInterpreter.h"

#define RAGE_EVENTS_KEY_UP 1
#define RAGE_EVENTS_KEY_DOWN 2
#define RAGE_EVENTS_KEY_CHAR 3

#include "BaseEvent.h"


namespace RAGE
{
	namespace Events
	{
		class KeyboardEvent : 
			public BaseEvent
		{
		private:
			void run_procs(VALUE *observer, int type, int *keycode);
			VALUE key;
			VALUE key_char_observer;
			VALUE key_up_observer;
			VALUE key_down_observer;
			bool unichar;
			bool keycode_names;
		public:
			KeyboardEvent(void);
			void register_proc(int type, VALUE proc);
			void unregister_proc(int type, VALUE proc);
			int get_proc_count(int type);
			void clear_procs(int type);
			void call_procs(int type, int keycode);
			void callback(ALLEGRO_EVENT *ev);
			void gc_mark(void);
			void dispose(void);
			bool get_unichar(void);
			void set_unichar(bool unichr);
			bool get_keycode_names(void);
			void set_keycode_names(bool kcode_names);
			VALUE get_observer_array(int type);
			~KeyboardEvent(void);
		};

	}
}
