#include "Events_Wrapper.h"

namespace RAGE
{
	namespace Events
	{
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_EVENT keyEvent;

		VALUE EventsWrapper::rb_update_events(VALUE self)
		{
			ALLEGRO_EVENT event = {0};
			keyEvent = event;
			if (al_get_next_event(event_queue, &event))
			{
				if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					rb_exit(0);
				}
				else if (event.type == ALLEGRO_EVENT_KEY_CHAR)
				{
					keyEvent = event;
				}
			}
	
			return Qnil;
		}

		VALUE EventsWrapper::rb_get_key(VALUE self)
		{
			if (keyEvent.type == ALLEGRO_EVENT_KEY_CHAR)
				return INT2FIX(keyEvent.keyboard.keycode);
			else
				return Qnil;
		}

		ALLEGRO_EVENT_QUEUE* EventsWrapper::get_queue()
		{
			return event_queue;
		}

		void EventsWrapper::init_queue()
		{
			event_queue = al_create_event_queue();
			al_register_event_source(event_queue, al_get_keyboard_event_source());
			
		}

		void EventsWrapper::finalize_queue()
		{
			if (event_queue != NULL)
				al_destroy_event_queue(event_queue);
		}

		void EventsWrapper::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE events = rb_define_module_under(rage, "Events");
			rb_define_module_function(events, "update", RFUNC(EventsWrapper::rb_update_events), 0);
			rb_define_module_function(events, "getKeyCode", RFUNC(EventsWrapper::rb_get_key), 0);
		}
	}
}
