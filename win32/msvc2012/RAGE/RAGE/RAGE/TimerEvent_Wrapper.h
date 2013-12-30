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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_TIMER_EVENT

#define RAGE_TIMER_EVENT 4

namespace RAGE
{
	namespace Events
	{
		class TimerEventWrapper
		{
		private:
			static VALUE rb_timer_alloc(VALUE self);
			static VALUE rb_timer_initialize(int argc, VALUE *args, VALUE self);
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
			static VALUE rb_timer_get_procs_array(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(int seconds);
		};
	}
}

#endif