#define ALLEGRO_STATICLINK
#include "Draw_Wrappers.h"

namespace RAGE
{
	namespace Graphics
	{

		ALLEGRO_COLOR color;
		ALLEGRO_FONT* font;
		ALLEGRO_USTR *str;

		VALUE DrawWrappers::draw_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness)
		{
			al_draw_line(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), color, NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::draw_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness)
		{
			al_draw_rectangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), color, NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::draw_filled_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
		{
			al_draw_filled_rectangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), color);
			return Qnil;
		}

		VALUE DrawWrappers::draw_pixel(VALUE self, VALUE x, VALUE y)
		{
			al_draw_pixel(NUM2DBL(x), NUM2DBL(y), color);
			return Qnil;
		}

		VALUE DrawWrappers::draw_pixel_c(VALUE self, VALUE x, VALUE y, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			al_draw_pixel(NUM2DBL(x), NUM2DBL(y), al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));
			return Qnil;
		}

		VALUE DrawWrappers::set_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			color = al_map_rgba_f(FIX2INT(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)); 
			return Qnil;
		}

		VALUE DrawWrappers::draw_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness)
		{
			float cx = (NUM2DBL(x1) + NUM2DBL(x2)) / 2; 
			float cy = (NUM2DBL(y1) + NUM2DBL(y2)) / 2;
			float rx = NUM2DBL(x1) + NUM2DBL(x2) - cx;
			float ry = NUM2DBL(y1) + NUM2DBL(y2) - cy;
			al_draw_ellipse(cx, cy, rx, ry, color, NUM2DBL(thickness));
			
			return Qnil;
		}

		VALUE DrawWrappers::draw_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry, VALUE thickness)
		{
			al_draw_ellipse(NUM2DBL(cx), NUM2DBL(cy), NUM2DBL(rx), NUM2DBL(ry), color, NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::draw_filled_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
		{
			float cx = (NUM2DBL(x1) + NUM2DBL(x2)) / 2; 
			float cy = (NUM2DBL(y1) + NUM2DBL(y2)) / 2;
			float rx = NUM2DBL(x1) + NUM2DBL(x2) - cx;
			float ry = NUM2DBL(y1) + NUM2DBL(y2) - cy;
			al_draw_filled_ellipse(cx, cy, rx, ry, color);
			
			return Qnil;
		}

		VALUE DrawWrappers::draw_filled_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry)
		{

			al_draw_filled_ellipse(NUM2DBL(cx), NUM2DBL(cy), NUM2DBL(rx), NUM2DBL(ry), color);

			return Qnil;
		}

		VALUE DrawWrappers::draw_text(VALUE self, VALUE x, VALUE y, VALUE text)
		{
			al_ustr_assign_cstr(str, StringValueCStr(text));
			al_draw_ustr(font, color, NUM2DBL(x), NUM2DBL(y), 0, str);
			return Qnil;
		}


		VALUE DrawWrappers::set_font(VALUE self, VALUE name, VALUE size)
		{
			VALUE fname = rb_find_file(name);
			if (TYPE(fname) != T_STRING)
			{
				
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(name));
				return Qfalse;
			}
			
			font = al_load_font(StringValueCStr(fname), FIX2UINT(size), 0);

			return Qnil;
		}

		void DrawWrappers::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE draw = rb_define_module_under(rage, "Draw");
			
			rb_define_module_function(draw, "line", RFUNC(DrawWrappers::draw_line), 5);
			rb_define_module_function(draw, "rectangle", RFUNC(DrawWrappers::draw_rectangle), 5);
			rb_define_module_function(draw, "fillRect", RFUNC(DrawWrappers::draw_filled_rectangle), 4);
			rb_define_module_function(draw, "ellipse", RFUNC(DrawWrappers::draw_ellipse), 5);
			rb_define_module_function(draw, "ellipseM", RFUNC(DrawWrappers::draw_ellipse2), 5);
			rb_define_module_function(draw, "fillEllipse", RFUNC(DrawWrappers::draw_filled_ellipse), 5);
			rb_define_module_function(draw, "fillEllipseM", RFUNC(DrawWrappers::draw_filled_ellipse2), 5);
			rb_define_module_function(draw, "pixel", RFUNC(DrawWrappers::draw_pixel), 2);
			rb_define_module_function(draw, "pixelC", RFUNC(DrawWrappers::draw_pixel_c), 6);
			rb_define_module_function(draw, "setColor", RFUNC(DrawWrappers::set_color), 4);
			rb_define_module_function(draw, "setFont", RFUNC(DrawWrappers::set_font), 2);
			rb_define_module_function(draw, "text", RFUNC(DrawWrappers::draw_text), 3);

			str = al_ustr_new("");
		}
	}
}
