#pragma once
#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Graphics
	{

		class BitmapWrapper
		{
		private:
			static VALUE rb_initialize(VALUE self, VALUE width, VALUE height);
			static VALUE rb_initialize_f(VALUE self, VALUE filename);
		public:
			static void LoadRubyClass();
		};
	}
}