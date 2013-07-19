#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Graphics
	{

		class DrawWrappers
		{
		private:
			static VALUE rb_draw_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness);
			static VALUE rb_draw_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness);
			static VALUE rb_draw_filled_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
			static VALUE rb_draw_rounded_rect(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE rx, VALUE ry, VALUE thickness);
			static VALUE rb_draw_rounded_filled_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE rx, VALUE ry);
			static VALUE rb_draw_pixel(VALUE self, VALUE x, VALUE y);
			static VALUE rb_draw_pixel_c(VALUE self, VALUE x, VALUE y, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE rb_draw_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness);
			static VALUE rb_draw_filled_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
			static VALUE rb_draw_filled_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry);
			static VALUE rb_draw_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry, VALUE thickness);
			static VALUE rb_draw_text(VALUE self, VALUE x, VALUE y, VALUE text);
			static VALUE rb_draw_justified_text(VALUE self, VALUE x, VALUE y, VALUE width, VALUE diff, VALUE text);
			static VALUE rb_set_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE rb_draw_vertex(VALUE self, VALUE vertex_array, VALUE texture, VALUE start, VALUE end, VALUE type);
			static VALUE rb_draw_indexed_vertex(VALUE self, VALUE vertex_array, VALUE texture, VALUE indices_array, VALUE indices_num, VALUE type);
			static VALUE rb_set_color_o(VALUE self, VALUE scolor);
			static VALUE rb_set_font(VALUE self, VALUE sfont);
			static VALUE rb_set_background_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);
			static VALUE rb_set_background_color_o(VALUE self, VALUE color);
			static VALUE rb_clear(VALUE self);
			static VALUE rb_graphics_set_clipping_rect(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h);
			static VALUE rb_graphics_reset_clipping_rect(VALUE self);
		public:
			static void reset_font(void);
			static void init(void);
			static void load_wrappers(void);
		};

	}
}
