#pragma once
#include "RubyInterpreter.h"
#include "TimerEvent.h"
#include "BaseEvent.h"

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
			 static VALUE rb_get_events_array(VALUE self);
			 static void* rb_update_event_objects(void* ptr);
		public:
			static ALLEGRO_EVENT_QUEUE* get_queue(void);
			static void unregister_event(VALUE ev);
			static bool get_use_keycode_names(void);
			static void init_queue(void);
			static void finalize_queue(void);
			static void load_wrappers(void);
			static void run_event_thread(void);
		};
	}
}

