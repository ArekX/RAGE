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
