#include "ScreenEvent.h"

namespace RAGE
{
	namespace Events
	{
		ScreenEvent::ScreenEvent(void)
		{
			disposed = false;
			screen_close_observer = rb_ary_new();
			screen_focus_observer = rb_ary_new();
			screen_lost_observer = rb_ary_new();
			screen_resize_observer = rb_ary_new();
			rb_gc_register_address(&screen_close_observer);
			rb_gc_register_address(&screen_focus_observer);
			rb_gc_register_address(&screen_lost_observer);
			rb_gc_register_address(&screen_resize_observer);
			
		}

		void ScreenEvent::run_procs(VALUE *observer)
		{
			RAGE_CHECK_DISPOSED(disposed);

			for (int i = 0; i < RARRAY_LEN(*observer); i++)
			{
				rb_proc_call_with_block(rb_ary_entry(*observer, i), 0, NULL, 
								        rb_ary_entry(*observer, i));
			}
		}

		void ScreenEvent::register_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENT_SCREEN_CLOSE:
					RAGE_REGISTER_EVENT(screen_close_observer, proc);
					break;
				case RAGE_EVENT_SCREEN_FOCUS:
					RAGE_REGISTER_EVENT(screen_focus_observer, proc);
					break;
				case RAGE_EVENT_SCREEN_LOST:
					RAGE_REGISTER_EVENT(screen_lost_observer, proc);
					break;
				case RAGE_EVENT_SCREEN_RESIZE:
					RAGE_REGISTER_EVENT(screen_resize_observer, proc);
			}

		}

		void ScreenEvent::unregister_proc(int type, VALUE proc)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENT_SCREEN_CLOSE:
					RAGE_UNREGISTER_EVENT(screen_close_observer, proc);
					break;
				case RAGE_EVENT_SCREEN_FOCUS:
					RAGE_UNREGISTER_EVENT(screen_focus_observer, proc);
					break;
				case RAGE_EVENT_SCREEN_LOST:
					RAGE_UNREGISTER_EVENT(screen_lost_observer, proc);
					break;
				case RAGE_EVENT_SCREEN_RESIZE:
					RAGE_UNREGISTER_EVENT(screen_resize_observer, proc);
			}
		}

		int ScreenEvent::get_proc_count(int type)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			switch(type)
			{
				case RAGE_EVENT_SCREEN_CLOSE:
					return RARRAY_LEN(screen_close_observer);
				case RAGE_EVENT_SCREEN_FOCUS:
					return RARRAY_LEN(screen_focus_observer);
				case RAGE_EVENT_SCREEN_LOST:
					return RARRAY_LEN(screen_lost_observer);
				case RAGE_EVENT_SCREEN_RESIZE:
					return RARRAY_LEN(screen_resize_observer);
				default:
					return -1;
			}
		}

		void ScreenEvent::clear_procs(int type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENT_SCREEN_CLOSE:
					rb_ary_clear(screen_close_observer);
					break;
				case RAGE_EVENT_SCREEN_FOCUS:
					rb_ary_clear(screen_focus_observer);
					break;
				case RAGE_EVENT_SCREEN_LOST:
					rb_ary_clear(screen_lost_observer);
					break;
				case RAGE_EVENT_SCREEN_RESIZE:
					rb_ary_clear(screen_resize_observer);
			}

		}

		void ScreenEvent::call_procs(int type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch(type)
			{
				case RAGE_EVENT_SCREEN_CLOSE:
					run_procs(&screen_close_observer);
					break;
				case RAGE_EVENT_SCREEN_FOCUS:
					run_procs(&screen_focus_observer);
					break;
				case RAGE_EVENT_SCREEN_LOST:
					run_procs(&screen_lost_observer);
					break;
				case RAGE_EVENT_SCREEN_RESIZE:
					run_procs(&screen_resize_observer);
			}
		}

		void ScreenEvent::callback(ALLEGRO_EVENT *ev)
		{
			
			RAGE_CHECK_DISPOSED(disposed);
			
			switch(ev->type)
			{
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					run_procs(&screen_close_observer);
					break;
				case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
					run_procs(&screen_focus_observer);
					break;
				case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
					run_procs(&screen_lost_observer);
					break;
				case ALLEGRO_EVENT_DISPLAY_RESIZE:
					run_procs(&screen_resize_observer);
			}
		}

		void ScreenEvent::dispose()
		{
			RAGE_CHECK_DISPOSED(disposed);

			rb_ary_clear(screen_close_observer);
			rb_ary_clear(screen_focus_observer);
			rb_ary_clear(screen_lost_observer);
			rb_ary_clear(screen_resize_observer);

			disposed = true;
		}



		ScreenEvent::~ScreenEvent(void)
		{
			if (!disposed)
				dispose();
		}
	}
}