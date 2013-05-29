#pragma once

#include "RubyInterpreter.h"
#include "KeyboardEvent.h"

#define RAGE_KEYBOARD_EVENT 2

namespace RAGE
{
	namespace Events
	{
		class KeyboardEventWrapper
		{
		private:
			static VALUE rb_key_event_alloc(VALUE self);
			static void rb_key_event_destroy(void *value);
			static VALUE rb_use_keycode_names(VALUE self, VALUE val);
			static VALUE rb_use_typed_char(VALUE self, VALUE val);
			static VALUE rb_register(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_unregister(VALUE self, VALUE event_type, VALUE proc);
			static VALUE rb_clear(VALUE self, VALUE event_type);
			static VALUE rb_run(VALUE self, VALUE event_type, VALUE keycode);
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