#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Network
	{
		class NetworkWrappers
		{
		private:
			
			static VALUE rb_get_string(int argc, VALUE *args, VALUE self);
			static VALUE rb_post_string(int argc, VALUE *args, VALUE self);
		public:
			static void load_wrappers(void);
		};
	}
}

