#pragma once

#include "RubyInterpreter.h"
#include "MouseEvent.h"

#define RAGE_MOUSE_EVENT 3

namespace RAGE
{
	namespace Events
	{

		class MouseEventWrapper
		{
		private:
			static VALUE rb_mouse_event_alloc(VALUE self);
			static void rb_mouse_event_gc_mark(void *value);
			static void rb_mouse_event_destroy(void *value);
			static VALUE rb_register(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_unregister(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_clear(VALUE self, VALUE event_type);
			static VALUE rb_run(VALUE self, VALUE event_type, VALUE buttons, VALUE x, VALUE y, VALUE wheel);
			static VALUE rb_get_proc_count(VALUE self, VALUE event_type);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};

	}
}
