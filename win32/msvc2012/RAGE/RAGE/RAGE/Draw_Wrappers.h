/*
Copyright (c) 2013 Aleksandar Panic

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

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
			static VALUE rb_draw_triangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3, VALUE thickness);
			static VALUE rb_draw_triangle_filled(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3);
			static VALUE rb_draw_pieslice(VALUE self, VALUE cx, VALUE cy, VALUE r, VALUE s_theta, VALUE d_theta, VALUE thickness);
			static VALUE rb_draw_pieslice_filled(VALUE self, VALUE cx, VALUE cy, VALUE r, VALUE s_theta, VALUE d_theta);
			static VALUE rb_draw_arc_elliptical(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry, VALUE s_theta, VALUE d_theta, VALUE thickness);
			static VALUE rb_draw_spline(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3, VALUE x4, VALUE y4, VALUE thickness);
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
			static VALUE rb_get_font(VALUE self);
			static VALUE rb_get_bg_color(VALUE self);
			static VALUE rb_get_set_color(VALUE self);
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
