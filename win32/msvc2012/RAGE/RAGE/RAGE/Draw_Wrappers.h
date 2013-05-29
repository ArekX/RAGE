#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Graphics
	{

		class DrawWrappers
		{
		private:
			static VALUE draw_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE color, VALUE thickness);
			static VALUE map_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);
		public:
			static void load_wrappers();
		};

	}
}
