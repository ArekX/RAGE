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
			static VALUE draw_rounded_rect(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE rx, VALUE ry, VALUE thickness);
			static VALUE draw_rounded_filled_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE rx, VALUE ry);
			static VALUE draw_pixel(VALUE self, VALUE x, VALUE y);
			static VALUE draw_pixel_c(VALUE self, VALUE x, VALUE y, VALUE r, VALUE g, VALUE b, VALUE a);

			static VALUE draw_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness);
			static VALUE draw_filled_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
			static VALUE draw_filled_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry);
			static VALUE draw_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry, VALUE thickness);
			static VALUE draw_text(VALUE self, VALUE x, VALUE y, VALUE text);
			static VALUE draw_justified_text(VALUE self, VALUE x, VALUE y, VALUE width, VALUE diff, VALUE text);
			static VALUE set_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE draw_vertex(VALUE self, VALUE vertex_array, VALUE texture, VALUE start, VALUE end, VALUE type);
			static VALUE draw_indexed_vertex(VALUE self, VALUE vertex_array, VALUE texture, VALUE indices_array, VALUE indices_num, VALUE type);
			static VALUE set_color_o(VALUE self, VALUE scolor);
			static VALUE set_font(VALUE self, VALUE sfont);
		public:
			static void reset_font(void);
			static void init(void);
			static void load_wrappers(void);
		};

	}
}
