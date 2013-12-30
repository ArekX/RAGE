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

#include "KeyboardEvent.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_KEYBOARD_EVENT

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

		bool KeyboardEvent::get_unichar(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return unichar;
		}

		void KeyboardEvent::set_unichar(bool unichr)
		{
			RAGE_CHECK_DISPOSED(disposed);

			unichar = unichr;
		}

		bool KeyboardEvent::get_keycode_names(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return keycode_names;
		}

		void KeyboardEvent::set_keycode_names(bool kcode_names)
		{
			RAGE_CHECK_DISPOSED(disposed);

			keycode_names = kcode_names;
		}

		VALUE KeyboardEvent::get_observer_array(int type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			switch(type)
			{
				case RAGE_EVENTS_KEY_CHAR:
					return rb_obj_clone(key_char_observer);

				case RAGE_EVENTS_KEY_UP:
					return rb_obj_clone(key_up_observer);
	
				case RAGE_EVENTS_KEY_DOWN:
					return rb_obj_clone(key_down_observer);

				default:
					return Qnil;
			}
		}

		KeyboardEvent::~KeyboardEvent(void)
		{
			if (!disposed)
				dispose();
		}

	}
}

#endif