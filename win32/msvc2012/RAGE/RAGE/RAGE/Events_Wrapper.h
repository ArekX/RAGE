#pragma once
#include "RubyInterpreter.h"
#include "TimerEvent.h"

#define RAGE_RB_PROC_ERROR "You can only pass instances of Proc object as an argument."
#define RAGE_RB_TIMER_ERROR "You can only pass instances of RAGE::Timer object as an argument."

#define RAGE_KEY_UP_EVENT 1
#define RAGE_KEY_DOWN_EVENT 2
#define RAGE_KEY_PRESS_EVENT 3
#define RAGE_ENGINE_CLOSE_EVENT 4
#define RAGE_TIMER_EVENT 5


namespace RAGE
{
	namespace Events
	{
		class EventsWrapper
		{
		private:
			 
			 static VALUE rb_is_pressed(VALUE self, VALUE keycode);
			 static VALUE rb_register_event(VALUE self, VALUE event_type, VALUE proc);
			 static VALUE rb_unregister_event(VALUE self, VALUE event_type, VALUE proc);
			 static VALUE rb_clear_events(VALUE self, VALUE event_type);
			 static VALUE rb_freeze_events(VALUE self);
			 static VALUE rb_unfreeze_events(VALUE self);
			 static VALUE rb_use_keycode_names(VALUE self, VALUE val);
			 static void* rb_update_events(void* ptr);
			 static VALUE rb_register_timer(VALUE self, VALUE timer);
			 static VALUE rb_unregister_timer(VALUE self, VALUE timer);
			 static VALUE rb_clear_timers(VALUE self);
		public:
			static ALLEGRO_EVENT_QUEUE* get_queue();
			static void init_queue();
			static void finalize_queue();
			static void load_wrappers();
			static void create_threads();
		};
	}
}

