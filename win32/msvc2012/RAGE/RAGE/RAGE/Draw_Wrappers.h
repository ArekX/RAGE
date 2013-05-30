#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Graphics
	{

		class DrawWrappers
		{
		private:
			static VALUE draw_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness);
			static VALUE draw_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness);
			static VALUE draw_filled_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
			static VALUE draw_pixel(VALUE self, VALUE x, VALUE y);
			static VALUE draw_pixel_c(VALUE self, VALUE x, VALUE y, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE draw_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness);
			static VALUE draw_filled_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
			static VALUE draw_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry, VALUE thickness);
			static VALUE set_line_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE set_line_color_f(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);
		public:
			static void load_wrappers();
		};

	}
}
