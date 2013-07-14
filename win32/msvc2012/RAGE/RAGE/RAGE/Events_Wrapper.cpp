#include "Events_Wrapper.h"


namespace RAGE
{
	namespace Events
	{
		ALLEGRO_EVENT_QUEUE* event_queue;

		VALUE eventsThread;
		bool  stopThread = false;
		VALUE event_objects;

		void* EventsWrapper::rb_update_event_objects(void* ptr)
		{
			ALLEGRO_EVENT ev;
			register int i;
			BaseEvent *evnt;
			while(true)
			{
				if (stopThread)
					rb_thread_stop();

				if (al_get_next_event(event_queue, &ev))
				{
					for (i = 0; i < RARRAY_LEN(event_objects); i++)
					{
						Data_Get_Struct(rb_ary_entry(event_objects, i), BaseEvent, evnt);
						evnt->callback(&ev);
					}
				}
				else
					rb_thread_schedule();
			}

			return NULL;
		}

		VALUE EventsWrapper::rb_register_event(VALUE self, VALUE entry)
		{
			if (TYPE(rb_ary_includes(event_objects, entry)) == T_FALSE)
			{
				if (rb_class_get_superclass(rb_class_of(entry)) != EventWrapper::get_ruby_class())
					rb_raise(rb_eArgError, RAGE_RB_EVENT_REG_ERR);
				else
				{
					if (rb_class_of(entry) == TimerEventWrapper::get_ruby_class())
					{
						TimerEvent *tm;
						Data_Get_Struct(entry, TimerEvent, tm);
						tm->register_to_queue(event_queue);
					}
					rb_ary_push(event_objects, entry);
				}
			}
			return Qnil;
		}

		VALUE EventsWrapper::rb_unregister_event(VALUE self, VALUE entry)
		{
			if (TYPE(rb_ary_includes(event_objects, entry)) == T_TRUE)
			{
				if (rb_class_get_superclass(rb_class_of(entry)) != RAGE::Events::EventWrapper::get_ruby_class())
					rb_raise(rb_eArgError, RAGE_RB_EVENT_REG_ERR);
				else
				{
					if (rb_class_of(entry) == TimerEventWrapper::get_ruby_class())
					{
						TimerEvent *tm;
						Data_Get_Struct(entry, TimerEvent, tm);
						tm->unregister_from_queue(event_queue);
					}
					rb_ary_delete(event_objects, entry);
				}
			}
			return Qnil;
		}

		VALUE EventsWrapper::rb_clear_events(VALUE self, VALUE event_type)
		{
			VALUE klass, entry;
			switch(FIX2INT(event_type))
			{
				case RAGE_KEYBOARD_EVENT:
					klass = RAGE::Events::KeyboardEventWrapper::get_ruby_class();
					break;
				case RAGE_MOUSE_EVENT:
					klass = RAGE::Events::MouseEventWrapper::get_ruby_class();
					break;
				case RAGE_SCREEN_EVENT:
					klass = RAGE::Events::ScreenEventWrapper::get_ruby_class();
					break;
				case RAGE_TIMER_EVENT:
					klass = RAGE::Events::TimerEventWrapper::get_ruby_class();
					break;
				case RAGE_JOYSTICK_EVENT:
					klass = RAGE::Events::JoyEventWrapper::get_ruby_class();
					break;
			}

			for (int i = 0; i < RARRAY_LEN(event_objects); i++)
			{
				entry = rb_ary_entry(event_objects, i);
				if (rb_class_of(entry) == klass)
				{
					if (FIX2INT(event_type) == RAGE_TIMER_EVENT)
					{
						TimerEvent *tm;
						Data_Get_Struct(entry, TimerEvent, tm);
						tm->unregister_from_queue(event_queue);
					}
					rb_ary_delete(event_objects, entry);
				}
			}
			return Qnil;
		}

		VALUE EventsWrapper::rb_clear_events2(VALUE self)
		{
			for (int i = 0; i < RARRAY_LEN(event_objects); i++)
			{
				if (rb_class_of(rb_ary_entry(event_objects, i)) == RAGE::Events::TimerEventWrapper::get_ruby_class())
				{
					TimerEvent *tm;
					Data_Get_Struct(rb_ary_entry(event_objects, i), TimerEvent, tm);
					tm->unregister_from_queue(event_queue);
				}
			}
			rb_ary_clear(event_objects);
			return Qnil;
		}

		VALUE EventsWrapper::rb_freeze_events(VALUE self)
		{
			stopThread = true;
			return Qnil;
		}

		VALUE EventsWrapper::rb_unfreeze_events(VALUE self)
		{
			stopThread = false;
			rb_thread_run(eventsThread);
			return Qnil;
		}

		ALLEGRO_EVENT_QUEUE* EventsWrapper::get_queue()
		{
			return event_queue;
		}

		void EventsWrapper::init_queue(void)
		{
			event_queue = al_create_event_queue();
			event_objects = rb_ary_new();

			if (event_queue == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_EVENT_QUEUE_FAIL);
				return;
			}
		}

		void EventsWrapper::run_event_thread(void)
		{
			eventsThread = rb_thread_create(RFUNC(EventsWrapper::rb_update_event_objects), NULL);
		}

		void EventsWrapper::finalize_queue(void)
		{
			if (event_queue != NULL)
			{
				al_destroy_event_queue(event_queue);
			}
		}

		VALUE EventsWrapper::rb_process_keyboard(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
				al_register_event_source(event_queue, al_get_keyboard_event_source());
			else if (TYPE(val) == T_FALSE)
				al_unregister_event_source(event_queue, al_get_keyboard_event_source());
			return Qnil;
		}

		VALUE EventsWrapper::rb_process_mouse(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
				al_register_event_source(event_queue, al_get_mouse_event_source());
			else if (TYPE(val) == T_FALSE)
				al_unregister_event_source(event_queue, al_get_mouse_event_source());
			return Qnil;
		}

		VALUE EventsWrapper::rb_process_joystick(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
				al_register_event_source(event_queue, al_get_joystick_event_source());
			else if (TYPE(val) == T_FALSE)
				al_unregister_event_source(event_queue, al_get_joystick_event_source());
			return Qnil;
		}

		VALUE EventsWrapper::rb_process_display(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
				RAGE::Graphics::GraphicsWrappers::set_screen_processing(event_queue, true);
			else if (TYPE(val) == T_FALSE)
				RAGE::Graphics::GraphicsWrappers::set_screen_processing(event_queue, false);

			return Qnil;
		}

		VALUE EventsWrapper::rb_event_is_registered(VALUE self, VALUE entry)
		{
			if (TYPE(rb_ary_includes(event_objects, entry)) == T_TRUE)
				return Qtrue;
			return Qfalse;
		}

		void EventsWrapper::load_wrappers(void)
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE events = rb_define_module_under(rage, "Events");

			rb_define_module_function(events, "register", RFUNC(EventsWrapper::rb_register_event), 1);
			rb_define_module_function(events, "unregister", RFUNC(EventsWrapper::rb_unregister_event), 1);
			rb_define_module_function(events, "isRegistered?", RFUNC(EventsWrapper::rb_event_is_registered), 1);
			rb_define_module_function(events, "processKeyboard", RFUNC(EventsWrapper::rb_process_keyboard), 1);
			rb_define_module_function(events, "processMouse", RFUNC(EventsWrapper::rb_process_mouse), 1);
			rb_define_module_function(events, "processJoystick", RFUNC(EventsWrapper::rb_process_joystick), 1);
			rb_define_module_function(events, "processScreen", RFUNC(EventsWrapper::rb_process_display), 1);
			rb_define_module_function(events, "clear", RFUNC(EventsWrapper::rb_clear_events), 1);
			rb_define_module_function(events, "clearAll", RFUNC(EventsWrapper::rb_clear_events2), 0);
			rb_define_module_function(events, "freeze", RFUNC(EventsWrapper::rb_freeze_events), 0);
			rb_define_module_function(events, "unfreeze", RFUNC(EventsWrapper::rb_unfreeze_events), 0);
		}

		void EventsWrapper::unregister_event(VALUE ev)
		{
			rb_unregister_event(Qnil, ev);
		}
	}
}
