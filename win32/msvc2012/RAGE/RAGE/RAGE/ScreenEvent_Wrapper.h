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
			static void rb_screen_event_destroy(void *value);
			static VALUE rb_register(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_unregister(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_clear(VALUE self, VALUE event_type);
			static VALUE rb_run(VALUE self, VALUE event_type);
			static VALUE rb_get_proc_count(VALUE self, VALUE event_type);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};

	}
}
