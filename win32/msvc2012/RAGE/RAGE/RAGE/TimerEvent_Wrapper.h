#pragma once

#include "RubyInterpreter.h"
#include "TimerEvent.h"

#define RAGE_TIMER_EVENT 4

namespace RAGE
{
	namespace Events
	{
		class TimerEventWrapper
		{
		private:
			static VALUE rb_timer_alloc(VALUE self);
			static VALUE rb_timer_initialize(VALUE self, VALUE seconds);
			static void  rb_timer_gc_mark(void *value);
			static void  rb_timer_destroy(void *value);
			static VALUE rb_timer_register_proc(VALUE self, VALUE proc);
			static VALUE rb_timer_unregister_proc(VALUE self, VALUE proc);
			static VALUE rb_timer_get_started(VALUE self);
			static VALUE rb_timer_get_speed(VALUE self);
			static VALUE rb_timer_get_count(VALUE self);
			static VALUE rb_timer_get_proc_count(VALUE self);
			static VALUE rb_timer_run(VALUE self);
			static VALUE rb_timer_set_count(VALUE self, VALUE count);
			static VALUE rb_timer_set_speed(VALUE self, VALUE speed);
			static VALUE rb_timer_start(VALUE self);
			static VALUE rb_timer_stop(VALUE self);
			static VALUE rb_timer_clear(VALUE self);
			static VALUE rb_timer_dispose(VALUE self);
			static VALUE rb_timer_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(int seconds);
		};
	}
}

