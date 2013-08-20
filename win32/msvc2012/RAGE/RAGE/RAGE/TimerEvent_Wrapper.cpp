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

#include "TimerEvent_Wrapper.h"

namespace RAGE
{
	namespace Events
	{
		VALUE rb_rage_TimerClass;

		VALUE TimerEventWrapper::rb_timer_alloc(VALUE self)
		{
			
			return Data_Wrap_Struct(self, TimerEventWrapper::rb_timer_gc_mark, TimerEventWrapper::rb_timer_destroy, new TimerEvent());
		}

		void TimerEventWrapper::rb_timer_gc_mark(void *value)
		{
			((TimerEvent*)value)->gc_mark();
		}

		VALUE TimerEventWrapper::rb_timer_initialize(int argc, VALUE *args, VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			if (argc == 1)
			{
				tm->initialize(NUM2DBL(args[0]));
			}
			else if (argc == 2)
			{
				tm->initialize(NUM2DBL(args[0]));
				rb_timer_register_proc(self, args[1]);
			}
			else
			{
				rb_raise(rb_eException, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 2);
			}
			
			return Qnil;
		}

		void TimerEventWrapper::rb_timer_destroy(void *value)
		{
			delete value;
		}

		VALUE TimerEventWrapper::rb_timer_register_proc(VALUE self, VALUE proc)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);
			tm->register_callback(proc);
			return Qtrue;
		}

		VALUE TimerEventWrapper::rb_timer_unregister_proc(VALUE self, VALUE proc)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);
			tm->unregister_callback(proc);
			return Qtrue;
		}

		VALUE TimerEventWrapper::rb_timer_clear(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);
			tm->clear();
			return Qnil;
		}

		VALUE TimerEventWrapper::rb_timer_dispose(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			EventsWrapper::unregister_event(self);

			tm->dispose();

			return Qnil;
		}

		VALUE TimerEventWrapper::rb_timer_get_started(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			return (tm->started()) ? Qtrue : Qfalse;
		}

		VALUE TimerEventWrapper::rb_timer_get_speed(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			return DBL2NUM(tm->get_speed());
		}

		VALUE TimerEventWrapper::rb_timer_get_count(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			return LL2NUM(tm->get_count());
		}

		VALUE TimerEventWrapper::rb_timer_set_count(VALUE self, VALUE count)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			tm->set_count(NUM2LL(count));

			return Qnil;
		}

		VALUE TimerEventWrapper::rb_timer_set_speed(VALUE self, VALUE speed)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			tm->set_speed(NUM2DBL(speed));

			return Qnil;
		}

		VALUE TimerEventWrapper::rb_timer_start(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			tm->start();

			return Qnil;
		}

		VALUE TimerEventWrapper::rb_timer_stop(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			tm->stop();

			return Qnil;
		}

	   VALUE TimerEventWrapper::rb_timer_get_proc_count(VALUE self)
	   {
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);
			return INT2FIX(tm->get_proc_count());
	   }

	   VALUE TimerEventWrapper::rb_timer_run(VALUE self)
	   {
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);
			tm->run_procs();
			return Qnil;
	   }

		VALUE TimerEventWrapper::rb_timer_disposed(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);
			
			return tm->disposed ? Qtrue : Qfalse;
		}

		VALUE TimerEventWrapper::rb_timer_get_procs_array(VALUE self)
		{
			TimerEvent *tm;
			Data_Get_Struct(self, TimerEvent, tm);

			return tm->get_observer_array();
		}

		void TimerEventWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::TimerEvent")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rage_TimerClass = rb_define_class_under(rage, "TimerEvent", EventWrapper::get_ruby_class());

			rb_define_const(rb_define_module_under(rage, "Events"), "TIMER", INT2FIX(RAGE_TIMER_EVENT));

			rb_define_alloc_func(rb_rage_TimerClass, TimerEventWrapper::rb_timer_alloc);
			
			rb_define_method(rb_rage_TimerClass, "initialize", RFUNC(TimerEventWrapper::rb_timer_initialize), -1);
			rb_define_method(rb_rage_TimerClass, "register", RFUNC(TimerEventWrapper::rb_timer_register_proc), 1);
			rb_define_method(rb_rage_TimerClass, "unregister", RFUNC(TimerEventWrapper::rb_timer_unregister_proc), 1);
			rb_define_method(rb_rage_TimerClass, "start", RFUNC(TimerEventWrapper::rb_timer_start), 0);
			rb_define_method(rb_rage_TimerClass, "stop", RFUNC(TimerEventWrapper::rb_timer_stop), 0);
			rb_define_method(rb_rage_TimerClass, "started?", RFUNC(TimerEventWrapper::rb_timer_get_started), 0);
			rb_define_method(rb_rage_TimerClass, "count", RFUNC(TimerEventWrapper::rb_timer_get_count), 0);
			rb_define_method(rb_rage_TimerClass, "getProcCount", RFUNC(TimerEventWrapper::rb_timer_get_proc_count), 0);
			rb_define_method(rb_rage_TimerClass, "getProcsAsArray", RFUNC(TimerEventWrapper::rb_timer_get_procs_array), 0);
			rb_define_method(rb_rage_TimerClass, "count=", RFUNC(TimerEventWrapper::rb_timer_set_count), 1);
			rb_define_method(rb_rage_TimerClass, "speed", RFUNC(TimerEventWrapper::rb_timer_get_speed), 0);
			rb_define_method(rb_rage_TimerClass, "speed=", RFUNC(TimerEventWrapper::rb_timer_set_speed), 1);
			rb_define_method(rb_rage_TimerClass, "run", RFUNC(TimerEventWrapper::rb_timer_run), 0);
			rb_define_method(rb_rage_TimerClass, "clear", RFUNC(TimerEventWrapper::rb_timer_clear), 0);
			rb_define_method(rb_rage_TimerClass, "dispose", RFUNC(TimerEventWrapper::rb_timer_dispose), 0);
			rb_define_method(rb_rage_TimerClass, "disposed?", RFUNC(TimerEventWrapper::rb_timer_disposed), 0);
		}

		VALUE TimerEventWrapper::get_ruby_class(void)
		{
			return rb_rage_TimerClass;
		}

		VALUE TimerEventWrapper::new_ruby_class_instance(int seconds)
		{
			VALUE secs = INT2FIX(seconds);
			return rb_class_new_instance(1, &secs, rb_rage_TimerClass);
		}
	}
}
