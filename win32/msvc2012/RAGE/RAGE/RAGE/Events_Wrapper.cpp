#include "Events_Wrapper.h"

#define RAGE_REGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_FALSE) { if (rb_class_of(proc) != rb_cProc) rb_raise_proc_error(); else rb_ary_push(observer, proc);}
#define RAGE_UNREGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_TRUE) { if (rb_class_of(proc) != rb_cProc) rb_raise_proc_error(); else rb_ary_delete(observer, proc);}

namespace RAGE
{
	namespace Events
	{
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_KEYBOARD_STATE ks;

		VALUE eventsThread;
		bool  stopThread = false;
		bool  useKeyCodeNames = false;

		VALUE engineCloseObserver;
		VALUE keyUpObserver;
		VALUE keyDownObserver;
		VALUE keyPressObserver;

		void rb_raise_proc_error()
		{
			rb_raise(rb_eTypeError, "You can only pass instances of Proc object as an argument.");
		}


		void* EventsWrapper::rb_update_events(void* ptr)
		{
			ALLEGRO_EVENT ev;
			VALUE arg[1];
			register long i;
			while(1)
			{
				if (stopThread)
					rb_thread_stop();

				if (al_get_next_event(event_queue, &ev))
				{
					if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						if (RARRAY_LEN(engineCloseObserver) > 0)
						{
							for (i = 0; i < RARRAY_LEN(engineCloseObserver); i++)
							{
								rb_proc_call_with_block(rb_ary_entry(engineCloseObserver, i), 0, NULL, 
														rb_ary_entry(engineCloseObserver, i));
							}
						}
						else
							rb_exit(0);
					}
					
					if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						for (i = 0; i < RARRAY_LEN(keyDownObserver); i++)
						{
							if (useKeyCodeNames)
								arg[0] = rb_str_new_cstr(al_keycode_to_name(ev.keyboard.keycode));
							else
								arg[0] = INT2FIX(ev.keyboard.keycode);

							rb_proc_call_with_block(rb_ary_entry(keyDownObserver, i), 1, arg, 
								                    rb_ary_entry(keyDownObserver, i));
						}
					}
					
					if (ev.type == ALLEGRO_EVENT_KEY_UP)
					{
						for (i = 0; i < RARRAY_LEN(keyUpObserver); i++)
						{
							if (useKeyCodeNames)
								arg[0] = rb_str_new_cstr(al_keycode_to_name(ev.keyboard.keycode));
							else
								arg[0] = INT2FIX(ev.keyboard.keycode);

							rb_proc_call_with_block(rb_ary_entry(keyUpObserver, i), 1, arg, 
								                    rb_ary_entry(keyUpObserver, i));
						}
					}
					
					if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
					{
						for (i = 0; i < RARRAY_LEN(keyPressObserver); i++)
						{
							if (useKeyCodeNames)
								arg[0] = rb_str_new_cstr(al_keycode_to_name(ev.keyboard.keycode));
							else
								arg[0] = INT2FIX(ev.keyboard.keycode);

							rb_proc_call_with_block(rb_ary_entry(keyPressObserver, i), 1, arg, 
								                    rb_ary_entry(keyPressObserver, i));
						}
					}
				}
				rb_thread_schedule();	
			}
			return NULL;
		}

		VALUE EventsWrapper::rb_register_event(VALUE self, VALUE event_type, VALUE proc)
		{
			switch(FIX2INT(event_type))
			{
				case RAGE_KEY_UP_EVENT:
					RAGE_REGISTER_EVENT(keyUpObserver, proc);
					return Qtrue;
				case RAGE_KEY_DOWN_EVENT:
					RAGE_REGISTER_EVENT(keyDownObserver, proc);
					return Qtrue;
				case RAGE_KEY_PRESS_EVENT:
					RAGE_REGISTER_EVENT(keyPressObserver, proc);
					return Qtrue;
				case RAGE_ENGINE_CLOSE_EVENT:
					RAGE_REGISTER_EVENT(engineCloseObserver, proc);
					return Qtrue;
				default:
					return Qfalse;
			}
		}

		VALUE EventsWrapper::rb_unregister_event(VALUE self, VALUE event_type, VALUE proc)
		{
			switch(FIX2INT(event_type))
			{
				case RAGE_KEY_UP_EVENT:
					RAGE_UNREGISTER_EVENT(keyUpObserver, proc);
					return Qtrue;
				case RAGE_KEY_DOWN_EVENT:
					RAGE_UNREGISTER_EVENT(keyDownObserver, proc);
					return Qtrue;
				case RAGE_KEY_PRESS_EVENT:
					RAGE_UNREGISTER_EVENT(keyPressObserver, proc);
					return Qtrue;
				case RAGE_ENGINE_CLOSE_EVENT:
					RAGE_UNREGISTER_EVENT(engineCloseObserver, proc);
					return Qtrue;
				default:
					return Qfalse;
			}
			
		}

		VALUE EventsWrapper::rb_clear_events(VALUE self, VALUE event_type)
		{
			switch(FIX2INT(event_type))
			{
				case RAGE_KEY_UP_EVENT:
					rb_ary_clear(keyUpObserver);
					return Qtrue;
				case RAGE_KEY_DOWN_EVENT:
					rb_ary_clear(keyDownObserver);
					return Qtrue;
				case RAGE_KEY_PRESS_EVENT:
					rb_ary_clear(keyPressObserver);
					return Qtrue;
				case RAGE_ENGINE_CLOSE_EVENT:
					rb_ary_clear(engineCloseObserver);
					return Qtrue;
				default:
					return Qfalse;
			}
		}

		VALUE EventsWrapper::rb_use_keycode_names(VALUE self, VALUE val)
		{
			useKeyCodeNames = (TYPE(val) == T_TRUE);
			return Qnil;
		}

		VALUE EventsWrapper::rb_is_pressed(VALUE self, VALUE keycode)
		{
			al_get_keyboard_state(&ks);
			if (al_key_down(&ks, FIX2INT(keycode)))
				return Qtrue;
			else
				return Qfalse;
		}

		VALUE EventsWrapper::rb_freeze_events(VALUE self)
		{
			stopThread = true;
			return Qtrue;
		}

		VALUE EventsWrapper::rb_unfreeze_events(VALUE self)
		{
			stopThread = false;
			rb_thread_run(eventsThread);
			return Qtrue;
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

		void EventsWrapper::create_threads()
		{
			eventsThread = rb_thread_create(RFUNC(EventsWrapper::rb_update_events), al_get_current_display());
		}

		void EventsWrapper::finalize_queue()
		{
			if (event_queue != NULL)
			{
				al_destroy_event_queue(event_queue);
			}
		}

		void EventsWrapper::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE events = rb_define_module_under(rage, "Events");
			rb_define_const(events, "KEY_UP", INT2FIX(RAGE_KEY_UP_EVENT));
			rb_define_const(events, "KEY_DOWN", INT2FIX(RAGE_KEY_DOWN_EVENT));
			rb_define_const(events, "KEY_PRESS", INT2FIX(RAGE_KEY_PRESS_EVENT));
			rb_define_const(events, "ENGINE_CLOSE", INT2FIX(RAGE_ENGINE_CLOSE_EVENT));
			
			keyUpObserver = rb_ary_new();
			keyDownObserver = rb_ary_new();
			keyPressObserver = rb_ary_new();
			engineCloseObserver = rb_ary_new();
			
			rb_gc_register_address(&keyUpObserver);
			rb_gc_register_address(&keyDownObserver);
			rb_gc_register_address(&keyPressObserver);
			rb_gc_register_address(&engineCloseObserver);
			
			rb_define_module_function(events, "useKeyCodeNames", RFUNC(EventsWrapper::rb_use_keycode_names), 1);
			rb_define_module_function(events, "register", RFUNC(EventsWrapper::rb_register_event), 2);
			rb_define_module_function(events, "unregister", RFUNC(EventsWrapper::rb_unregister_event), 2);
			rb_define_module_function(events, "clear", RFUNC(EventsWrapper::rb_clear_events), 1);
			rb_define_module_function(events, "freeze", RFUNC(EventsWrapper::rb_freeze_events), 0);
			rb_define_module_function(events, "unfreeze", RFUNC(EventsWrapper::rb_unfreeze_events), 0);
			rb_define_module_function(events, "isDown", RFUNC(EventsWrapper::rb_is_pressed), 1);
			// TODO: Add timer, joystick, mouse and more display events
		}
	}
}
