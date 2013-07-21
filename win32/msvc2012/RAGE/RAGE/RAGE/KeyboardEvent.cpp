#include "KeyboardEvent.h"

namespace RAGE
{
	namespace Events
	{
		KeyboardEvent::KeyboardEvent(void)
		{
			disposed = false;
			unichar = false;
			keycode_names = false;
			key_up_observer = rb_ary_new();
			key_down_observer = rb_ary_new();
			key_char_observer = rb_ary_new();
		}

		void KeyboardEvent::register_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENTS_KEY_CHAR:
					RAGE_REGISTER_EVENT(key_char_observer, proc);
					break;
				case RAGE_EVENTS_KEY_UP:
					RAGE_REGISTER_EVENT(key_up_observer, proc);
					break;
				case RAGE_EVENTS_KEY_DOWN:
					RAGE_REGISTER_EVENT(key_down_observer, proc);
					break;
			}
		}

		void KeyboardEvent::unregister_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENTS_KEY_CHAR:
					RAGE_UNREGISTER_EVENT(key_char_observer, proc);
					break;
				case RAGE_EVENTS_KEY_UP:
					RAGE_UNREGISTER_EVENT(key_up_observer, proc);
					break;
				case RAGE_EVENTS_KEY_DOWN:
					RAGE_UNREGISTER_EVENT(key_down_observer, proc);
					break;
			}
		}

		int KeyboardEvent::get_proc_count(int type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			switch(type)
			{
				case RAGE_EVENTS_KEY_CHAR:
					return RARRAY_LEN(key_char_observer);
					break;
				case RAGE_EVENTS_KEY_UP:
					return RARRAY_LEN(key_up_observer);
					break;
				case RAGE_EVENTS_KEY_DOWN:
					return RARRAY_LEN(key_down_observer);
					break;

				default:
					return -1;
			}
		}

		void KeyboardEvent::clear_procs(int type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENTS_KEY_CHAR:
					rb_ary_clear(key_char_observer);
					break;
				case RAGE_EVENTS_KEY_UP:
					rb_ary_clear(key_up_observer);
					break;
				case RAGE_EVENTS_KEY_DOWN:
					rb_ary_clear(key_down_observer);
					break;
			}
		}

		void KeyboardEvent::call_procs(int type, int keycode)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENTS_KEY_CHAR:
					run_procs(&key_char_observer, RAGE_EVENTS_KEY_CHAR, &keycode);
					break;
				case RAGE_EVENTS_KEY_UP:
					run_procs(&key_up_observer, RAGE_EVENTS_KEY_UP, &keycode);
					break;
				case RAGE_EVENTS_KEY_DOWN:
					run_procs(&key_down_observer, RAGE_EVENTS_KEY_DOWN, &keycode);
					break;
			}
		}

		void KeyboardEvent::run_procs(VALUE *observer, int type, int *keycode)
		{
			for (int i = 0; i < RARRAY_LEN(*observer); i++)
			{

				if (keycode_names)
					key = rb_str_new_cstr(al_keycode_to_name(*keycode));
				else if (unichar)
					key = rb_str_new_cstr((char*)keycode);
				else
					key = INT2FIX(*keycode);
				
				rb_proc_call_with_block(rb_ary_entry(*observer, i), 1, &key, 
								        rb_ary_entry(*observer, i));
			}
		}

		void KeyboardEvent::callback(ALLEGRO_EVENT *ev)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
				run_procs(&key_down_observer, RAGE_EVENTS_KEY_DOWN, (unichar) ? &ev->keyboard.unichar : &ev->keyboard.keycode);

			else if (ev->type == ALLEGRO_EVENT_KEY_UP)
				run_procs(&key_up_observer, RAGE_EVENTS_KEY_UP, (unichar) ? &ev->keyboard.unichar : &ev->keyboard.keycode);

			if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
				run_procs(&key_char_observer, RAGE_EVENTS_KEY_CHAR, (unichar) ? &ev->keyboard.unichar : &ev->keyboard.keycode);
		}

		void KeyboardEvent::gc_mark(void)
		{
			rb_gc_mark(key_char_observer);
			rb_gc_mark(key_up_observer);
			rb_gc_mark(key_down_observer);
			rb_gc_mark(key);
		}

		void KeyboardEvent::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rb_ary_clear(key_char_observer);
			rb_ary_clear(key_up_observer);
			rb_ary_clear(key_down_observer);

			rb_gc_force_recycle(key_char_observer);
			rb_gc_force_recycle(key_up_observer);
			rb_gc_force_recycle(key_down_observer);
			rb_gc_force_recycle(key);

			disposed = true;
		}

		KeyboardEvent::~KeyboardEvent(void)
		{
			if (!disposed)
				dispose();
		}

	}
}