/*
Copyright (c) 2014 Aleksandar Panic

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

#include "MouseEvent.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_MOUSE_EVENT

namespace RAGE
{
	namespace Events
	{

		MouseEvent::MouseEvent(void)
		{
			mouse_up_observer = rb_ary_new();
			mouse_down_observer = rb_ary_new();
			mouse_enter_observer = rb_ary_new();
			mouse_leave_observer = rb_ary_new();
			mouse_move_observer = rb_ary_new();
			mouse_args = new VALUE[4];

			disposed = false;
		}

		void MouseEvent::register_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENT_MOUSE_UP:
					RAGE_REGISTER_EVENT(mouse_up_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_DOWN:
					RAGE_REGISTER_EVENT(mouse_down_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_MOVE:
					RAGE_REGISTER_EVENT(mouse_move_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_ENTER:
					RAGE_REGISTER_EVENT(mouse_enter_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_LEAVE:
					RAGE_REGISTER_EVENT(mouse_leave_observer, proc);
			}
		}

		void MouseEvent::unregister_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENT_MOUSE_UP:
					RAGE_UNREGISTER_EVENT(mouse_up_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_DOWN:
					RAGE_UNREGISTER_EVENT(mouse_down_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_MOVE:
					RAGE_UNREGISTER_EVENT(mouse_move_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_ENTER:
					RAGE_UNREGISTER_EVENT(mouse_enter_observer, proc);
				break;
				case RAGE_EVENT_MOUSE_LEAVE:
					RAGE_UNREGISTER_EVENT(mouse_leave_observer, proc);
			}
		}

		int MouseEvent::get_proc_count(int type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			switch(type)
			{
				case RAGE_EVENT_MOUSE_UP:
					return RARRAY_LEN(mouse_up_observer);

				case RAGE_EVENT_MOUSE_DOWN:
					return RARRAY_LEN(mouse_down_observer);

				case RAGE_EVENT_MOUSE_MOVE:
					return RARRAY_LEN(mouse_move_observer);

				case RAGE_EVENT_MOUSE_ENTER:
					return RARRAY_LEN(mouse_enter_observer);

				case RAGE_EVENT_MOUSE_LEAVE:
					return RARRAY_LEN(mouse_leave_observer);

				default:
					return -1;
			}
		}

		void MouseEvent::clear_procs(int type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENT_MOUSE_UP:
					rb_ary_clear(mouse_up_observer);
				break;
				case RAGE_EVENT_MOUSE_DOWN:
					rb_ary_clear(mouse_down_observer);
				break;
				case RAGE_EVENT_MOUSE_MOVE:
					rb_ary_clear(mouse_move_observer);
				break;
				case RAGE_EVENT_MOUSE_ENTER:
					rb_ary_clear(mouse_enter_observer);
				break;
				case RAGE_EVENT_MOUSE_LEAVE:
					rb_ary_clear(mouse_leave_observer);
			}
		}

		void MouseEvent::call_procs(int type, unsigned int buttons, int x, int y, int wheel)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			switch(type)
			{
				case RAGE_EVENT_MOUSE_UP:
					run_procs(&mouse_up_observer, &buttons, &x, &y, &wheel);
				break;
				case RAGE_EVENT_MOUSE_DOWN:
					run_procs(&mouse_down_observer, &buttons, &x, &y, &wheel);
				break;
				case RAGE_EVENT_MOUSE_MOVE:
					run_procs(&mouse_move_observer, &buttons, &x, &y, &wheel);
				break;
				case RAGE_EVENT_MOUSE_ENTER:
					run_procs(&mouse_enter_observer, &buttons, &x, &y, &wheel);
				break;
				case RAGE_EVENT_MOUSE_LEAVE:
					run_procs(&mouse_leave_observer, &buttons, &x, &y, &wheel);
			}
		}

		void MouseEvent::run_procs(VALUE *observer, unsigned int *buttons, int *x, int *y, int *wheel)
		{
			for (int i = 0; i < RARRAY_LEN(*observer); i++)
			{
				mouse_args[0] = INT2FIX(*buttons);
				mouse_args[1] = INT2FIX(*x);
				mouse_args[2] = INT2FIX(*y);
				mouse_args[3] = INT2FIX(*wheel);

				rb_proc_call_with_block(rb_ary_entry(*observer, i), 4, mouse_args, 
								        rb_ary_entry(*observer, i));
			}

		}

		void MouseEvent::callback(ALLEGRO_EVENT *ev)
		{
			VALUE *observer;

			RAGE_CHECK_DISPOSED(disposed);

			run_procs(this->get_observer_by_type(ev->type), &ev->mouse.button, &ev->mouse.x, &ev->mouse.y, &ev->mouse.z);
		}

		VALUE* MouseEvent::get_observer_by_type(ALLEGRO_EVENT_TYPE type)
		{
			switch (type) {
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				return &mouse_up_observer;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				return &mouse_down_observer;
			case ALLEGRO_EVENT_MOUSE_AXES:
				return &mouse_move_observer;
			case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
				return &mouse_enter_observer;
			case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
				return &mouse_leave_observer;
			}

			return nullptr;
		}

		void MouseEvent::gc_mark(void)
		{
			rb_gc_mark(mouse_down_observer);
			rb_gc_mark(mouse_up_observer);
			rb_gc_mark(mouse_move_observer);
			rb_gc_mark(mouse_enter_observer);
			rb_gc_mark(mouse_leave_observer);
			rb_gc_mark(mouse_args[0]);
			rb_gc_mark(mouse_args[1]);
			rb_gc_mark(mouse_args[2]);
			rb_gc_mark(mouse_args[3]);
		}

		void MouseEvent::dispose(void)
		{
			if (disposed)
				return;

			rb_ary_clear(mouse_down_observer);
			rb_ary_clear(mouse_up_observer);
			rb_ary_clear(mouse_move_observer);
			rb_ary_clear(mouse_enter_observer);
			rb_ary_clear(mouse_leave_observer);

			delete[] mouse_args;

			disposed = true;
		}

		VALUE MouseEvent::get_observer_array(int type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			switch(type)
			{
				case RAGE_EVENT_MOUSE_UP:
					return rb_obj_clone(mouse_up_observer);

				case RAGE_EVENT_MOUSE_DOWN:
					return rb_obj_clone(mouse_down_observer);

				case RAGE_EVENT_MOUSE_MOVE:
					return rb_obj_clone(mouse_move_observer);

				case RAGE_EVENT_MOUSE_ENTER:
					return rb_obj_clone(mouse_enter_observer);

				case RAGE_EVENT_MOUSE_LEAVE:
					return rb_obj_clone(mouse_leave_observer);

				default:
					return Qnil;
			}
		}

		MouseEvent::~MouseEvent(void)
		{
			if (!disposed)
				dispose();
		}

	}
}

#endif