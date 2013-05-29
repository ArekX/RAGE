#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Events
	{
		class EventWrapper
		{
		private:
			static VALUE rb_err(VALUE self);
		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};
	}
}
