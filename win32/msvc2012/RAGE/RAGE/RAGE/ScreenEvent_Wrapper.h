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

#include "RubyInterpreter.h"
#include "ScreenEvent.h"

#define RAGE_SCREEN_EVENT 1

namespace RAGE
{
	namespace Events
	{

		class ScreenEventWrapper
		{
		private:
			static VALUE rb_screen_event_alloc(VALUE self);
			static void rb_screen_event_gc_mark(void *value);
			static void rb_screen_event_destroy(void *value);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_register(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_unregister(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_clear(VALUE self, VALUE event_type);
			static VALUE rb_run(VALUE self, VALUE event_type);
			static VALUE rb_get_proc_count(VALUE self, VALUE event_type);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
			static VALUE rb_get_procs_array(VALUE self, VALUE event_type);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};

	}
}
