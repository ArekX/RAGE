#pragma once
#include "RubyInterpreter.h"
#include "TimerEvent.h"
#include "BaseEvent.h"

#define RAGE_RB_TIMER_ERROR "You can only pass instances of RAGE::Timer object as an argument."
#define RAGE_RB_EVENT_REG_ERR "You can register only instances of RAGE::Event objects."

namespace RAGE
{
	namespace Events
	{
		class EventsWrapper
		{
		private:
			 static VALUE rb_register_event(VALUE self, VALUE entry);
			 static VALUE rb_unregister_event(VALUE self, VALUE entry);
			 static VALUE rb_event_is_registered(VALUE self, VALUE entry);
			 static VALUE rb_clear_events(VALUE self, VALUE event_type);
			 static VALUE rb_clear_events2(VALUE self);
			 static VALUE rb_freeze_events(VALUE self);
			 static VALUE rb_unfreeze_events(VALUE self);
			 static VALUE rb_process_keyboard(VALUE self, VALUE val);
			 static VALUE rb_process_mouse(VALUE self, VALUE val);
			 static VALUE rb_process_joystick(VALUE self, VALUE val);
			 static VALUE rb_process_display(VALUE self, VALUE val);
			 static void* rb_update_event_objects(void* ptr);
		public:
			static ALLEGRO_EVENT_QUEUE* get_queue();
			static bool get_use_keycode_names();
			static void init_queue();
			static void finalize_queue();
			static void load_wrappers();
			static void run_event_thread();
		};
	}
}

