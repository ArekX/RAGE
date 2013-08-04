#include "Draw_Wrappers.h"

namespace RAGE
{
	namespace Graphics
	{
		ALLEGRO_COLOR bg_color;
		ALLEGRO_COLOR color;
		ALLEGRO_USTR *str;
		ALLEGRO_FONT *fnt, *def_font;
		Font *set_fnt = NULL;
		VALUE rb_font = Qnil;

		VALUE DrawWrappers::rb_draw_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness)
		{
			al_draw_line(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), color, NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness)
		{
			al_draw_rectangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), color, NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_filled_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
		{
			al_draw_filled_rectangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), color);
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_pixel(VALUE self, VALUE x, VALUE y)
		{
			al_draw_pixel(NUM2DBL(x), NUM2DBL(y), color);
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_pixel_c(VALUE self, VALUE x, VALUE y, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			al_draw_pixel(NUM2DBL(x), NUM2DBL(y), al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));
			return Qnil;
		}

		VALUE DrawWrappers::rb_set_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			color = al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)); 
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE thickness)
		{
			float cx = (NUM2DBL(x1) + NUM2DBL(x2)) / 2; 
			float cy = (NUM2DBL(y1) + NUM2DBL(y2)) / 2;
			al_draw_ellipse(cx, cy, abs(NUM2DBL(x1) - cx), abs(NUM2DBL(y1) - cy), color, NUM2DBL(thickness));
			
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry, VALUE thickness)
		{
			al_draw_ellipse(NUM2DBL(cx), NUM2DBL(cy), NUM2DBL(rx), NUM2DBL(ry), color, NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_filled_ellipse(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
		{
			float cx = (NUM2DBL(x1) + NUM2DBL(x2)) / 2; 
			float cy = (NUM2DBL(y1) + NUM2DBL(y2)) / 2;
			al_draw_filled_ellipse(cx, cy, abs(NUM2DBL(x1) - cx), abs(NUM2DBL(y1) - cy), color);
			
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_filled_ellipse2(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry)
		{

			al_draw_filled_ellipse(NUM2DBL(cx), NUM2DBL(cy), NUM2DBL(rx), NUM2DBL(ry), color);

			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_text(VALUE self, VALUE x, VALUE y, VALUE text)
		{
			al_ustr_assign_cstr(str, StringValueCStr(text));
			al_draw_ustr(fnt, color, NUM2DBL(x), NUM2DBL(y), 0, str);
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_justified_text(VALUE self, VALUE x, VALUE y, VALUE width, VALUE diff, VALUE text)
		{
			al_ustr_assign_cstr(str, StringValueCStr(text));
			
			al_draw_justified_ustr(fnt, color, NUM2DBL(x), NUM2DBL(x) + NUM2DBL(width), NUM2DBL(y), NUM2DBL(diff), 0, str);
			return Qnil;
		}

		VALUE DrawWrappers::rb_set_font(VALUE self, VALUE sfont)
		{			
			if (rb_class_of(sfont) != RAGE::Graphics::FontWrapper::get_ruby_class())
			{
				rb_raise(rb_eArgError, RAGE_FONT_ERROR);
				return Qnil;
			}

			Font *dfnt;
			Data_Get_Struct(sfont, Font, dfnt);

			if (dfnt->disposed)
			{
				rb_raise(rb_eException, RAGE_ERROR_CANNOT_SET_DISPOSED_OBJECTS);
				return Qnil;
			}

			rb_font = sfont;

			if (dfnt->font != NULL)
			{
				if (set_fnt != NULL)
					set_fnt->is_set = false;

				fnt = dfnt->font;
				dfnt->is_set = true;

				set_fnt = dfnt;
			}

			return Qnil;
		}

		VALUE DrawWrappers::rb_set_color_o(VALUE self, VALUE scolor)
		{
			if (rb_class_of(scolor) != RAGE::Graphics::ColorWrapper::get_ruby_class())
			{
				rb_raise(rb_eArgError, RAGE_COLOR_ERROR);
				return Qnil;
			}

			Color *cl;
			Data_Get_Struct(scolor, Color, cl);

			if (cl->disposed)
			{
				rb_raise(rb_eException, RAGE_ERROR_CANNOT_SET_DISPOSED_OBJECTS);
				return Qnil;
			}

			color = cl->color;

			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_rounded_rect(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE rx, VALUE ry, VALUE thickness)
		{
			al_draw_rounded_rectangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(rx), NUM2DBL(ry), color, NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_rounded_filled_rectangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE rx, VALUE ry)
		{
			al_draw_filled_rounded_rectangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(rx), NUM2DBL(ry), color);
			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_vertex(VALUE self, VALUE vertex_array, VALUE texture, VALUE start, VALUE end, VALUE type)
		{
			VertexArray *va;
			Data_Get_Struct(vertex_array, VertexArray, va);

			if (TYPE(texture) != T_NIL)
			{
				Bitmap *bmp;
				Data_Get_Struct(texture, Bitmap, bmp);

				return INT2FIX(al_draw_prim(va->ary, NULL, bmp->bitmap, FIX2INT(start), FIX2INT(end), FIX2INT(type)));
			}

			return INT2FIX(al_draw_prim(va->ary, NULL, NULL, FIX2INT(start), FIX2INT(end), FIX2INT(type)));
		}	

		VALUE DrawWrappers::rb_draw_indexed_vertex(VALUE self, VALUE vertex_array, VALUE texture, VALUE indices_array, VALUE indices_num, VALUE type)
		{
			if (TYPE(indices_array) != T_ARRAY)
			{
				rb_raise(rb_eArgError, RAGE_ERROR_INDICES_NOT_ARRAY);
				return Qnil;
			}

			VertexArray *va;
			Data_Get_Struct(vertex_array, VertexArray, va);
			
			int *indices = new int[RARRAY_LEN(indices_array)];

			for (int i = 0; i < RARRAY_LEN(indices_array); i++)
					indices[i] = FIX2INT(rb_ary_entry(indices_array, i));

			if (TYPE(texture) != T_NIL)
			{
				Bitmap *bmp;
				Data_Get_Struct(texture, Bitmap, bmp);

				return INT2FIX(al_draw_indexed_prim(va->ary, NULL, bmp->bitmap, indices, FIX2INT(indices_num), FIX2INT(type)));
			}

			return INT2FIX(al_draw_indexed_prim(va->ary, NULL, NULL, indices, FIX2INT(indices_num), FIX2INT(type)));

			delete[] indices;
		}

		VALUE DrawWrappers::rb_set_background_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			bg_color = al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a));

			return Qnil;
		}

		VALUE DrawWrappers::rb_set_background_color_o(VALUE self, VALUE color)
		{
			Color *cl;
			Data_Get_Struct(color, Color, cl);

			bg_color = cl->color;

			return Qnil;
		}

		VALUE DrawWrappers::rb_clear(VALUE self)
		{
			al_clear_to_color(bg_color);
			return Qnil;
		}

		VALUE DrawWrappers::rb_graphics_set_clipping_rect(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h)
		{
			al_set_clipping_rectangle(NUM2DBL(x), NUM2DBL(y), NUM2DBL(w), NUM2DBL(h));
			return Qnil;
		}

		VALUE DrawWrappers::rb_graphics_reset_clipping_rect(VALUE self)
		{
			al_reset_clipping_rectangle();
			return Qnil;
		}

		VALUE DrawWrappers::rb_get_font(VALUE self)
		{
			return rb_font;
		}

		VALUE DrawWrappers::rb_get_bg_color(VALUE self)
		{
			VALUE rt_color = ColorWrapper::new_ruby_class_instance();
			Color *cl;
			Data_Get_Struct(rt_color, Color, cl);

			cl->color = bg_color;

			return rt_color;
		}

		VALUE DrawWrappers::rb_get_set_color(VALUE self)
		{
			VALUE rt_color = ColorWrapper::new_ruby_class_instance();
			Color *cl;
			Data_Get_Struct(rt_color, Color, cl);

			cl->color = color;

			return rt_color;
		}

		VALUE DrawWrappers::rb_draw_triangle(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3, VALUE thickness)
		{
			al_draw_triangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3), color, NUM2DBL(thickness));

			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_triangle_filled(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3)
		{
			al_draw_filled_triangle(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3), color);

			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_pieslice(VALUE self, VALUE cx, VALUE cy, VALUE r, VALUE s_theta, VALUE d_theta, VALUE thickness)
		{
			al_draw_pieslice(NUM2DBL(cx), NUM2DBL(cy), NUM2DBL(r), NUM2DBL(s_theta), NUM2DBL(d_theta), color, NUM2DBL(thickness));   

			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_pieslice_filled(VALUE self, VALUE cx, VALUE cy, VALUE r, VALUE s_theta, VALUE d_theta)
		{
			al_draw_filled_pieslice(NUM2DBL(cx), NUM2DBL(cy), NUM2DBL(r), NUM2DBL(s_theta), NUM2DBL(d_theta), color);   

			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_arc_elliptical(VALUE self, VALUE cx, VALUE cy, VALUE rx, VALUE ry, VALUE s_theta, VALUE d_theta, VALUE thickness)
		{
			al_draw_elliptical_arc(NUM2DBL(cx), NUM2DBL(cy), NUM2DBL(rx), NUM2DBL(ry), NUM2DBL(s_theta), NUM2DBL(d_theta), color, NUM2DBL(thickness));

			return Qnil;
		}

		VALUE DrawWrappers::rb_draw_spline(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3, VALUE x4, VALUE y4, VALUE thickness)
		{
			float points[] = { NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(x3), NUM2DBL(y3), NUM2DBL(x4), NUM2DBL(y4) };
			
			al_draw_spline(points, color, NUM2DBL(thickness));
			
			return Qnil;
		}

		void DrawWrappers::reset_font(void)
		{
			fnt = def_font;
			rb_font = Qnil;
		}

		void DrawWrappers::init(void)
		{
			str = al_ustr_new("");
			def_font = al_create_builtin_font();
			fnt = def_font;
		}

		void DrawWrappers::load_wrappers(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Draw")) return;

			rb_gc_register_address(&rb_font);

			VALUE rage = rb_define_module("RAGE");
			VALUE draw = rb_define_module_under(rage, "Draw");
			
			rb_define_const(draw, "PRIM_POINT_LIST", INT2FIX(ALLEGRO_PRIM_POINT_LIST));
			rb_define_const(draw, "PRIM_LINE_LIST", INT2FIX(ALLEGRO_PRIM_LINE_LIST));
			rb_define_const(draw, "PRIM_LINE_STRIP", INT2FIX(ALLEGRO_PRIM_LINE_STRIP));
			rb_define_const(draw, "PRIM_LINE_LOOP", INT2FIX(ALLEGRO_PRIM_LINE_LOOP));
			rb_define_const(draw, "PRIM_TRIANGLE_LIST", INT2FIX(ALLEGRO_PRIM_TRIANGLE_LIST));
			rb_define_const(draw, "PRIM_TRIANGLE_STRIP", INT2FIX(ALLEGRO_PRIM_TRIANGLE_STRIP));
			rb_define_const(draw, "PRIM_TRIANGLE_FAN", INT2FIX(ALLEGRO_PRIM_TRIANGLE_FAN));

			rb_define_module_function(draw, "line", RFUNC(DrawWrappers::rb_draw_line), 5);
			rb_define_module_function(draw, "arc", RFUNC(DrawWrappers::rb_draw_arc_elliptical), 7);
			rb_define_module_function(draw, "spline", RFUNC(DrawWrappers::rb_draw_spline), 9);
			rb_define_module_function(draw, "triangle", RFUNC(DrawWrappers::rb_draw_triangle), 7);
			rb_define_module_function(draw, "filledTriangle", RFUNC(DrawWrappers::rb_draw_triangle), 6);
			rb_define_module_function(draw, "pieslice", RFUNC(DrawWrappers::rb_draw_pieslice), 6);
			rb_define_module_function(draw, "filledPieslice", RFUNC(DrawWrappers::rb_draw_pieslice_filled), 5);
			rb_define_module_function(draw, "clear", RFUNC(DrawWrappers::rb_clear), 0);
			rb_define_module_function(draw, "setClippingRect", RFUNC(DrawWrappers::rb_graphics_set_clipping_rect), 4);
			rb_define_module_function(draw, "resetClippingRect", RFUNC(DrawWrappers::rb_graphics_reset_clipping_rect), 0);
			rb_define_module_function(draw, "setBackgroundColor", RFUNC(DrawWrappers::rb_set_background_color), 4);
			rb_define_module_function(draw, "setBackgroundColorO", RFUNC(DrawWrappers::rb_set_background_color_o), 1);
			rb_define_module_function(draw, "rectangle", RFUNC(DrawWrappers::rb_draw_rectangle), 5);
			rb_define_module_function(draw, "fillRect", RFUNC(DrawWrappers::rb_draw_filled_rectangle), 4);
			rb_define_module_function(draw, "roundRect", RFUNC(DrawWrappers::rb_draw_rounded_rect), 7);
			rb_define_module_function(draw, "fillRound", RFUNC(DrawWrappers::rb_draw_rounded_filled_rectangle), 6);
			rb_define_module_function(draw, "ellipse", RFUNC(DrawWrappers::rb_draw_ellipse), 5);
			rb_define_module_function(draw, "ellipseM", RFUNC(DrawWrappers::rb_draw_ellipse2), 5);
			rb_define_module_function(draw, "fillEllipse", RFUNC(DrawWrappers::rb_draw_filled_ellipse), 4);
			rb_define_module_function(draw, "fillEllipseM", RFUNC(DrawWrappers::rb_draw_filled_ellipse2), 4);
			rb_define_module_function(draw, "prim", RFUNC(DrawWrappers::rb_draw_vertex), 5);
			rb_define_module_function(draw, "indexedPrim", RFUNC(DrawWrappers::rb_draw_indexed_vertex), 5);
			rb_define_module_function(draw, "pixel", RFUNC(DrawWrappers::rb_draw_pixel), 2);
			rb_define_module_function(draw, "pixelC", RFUNC(DrawWrappers::rb_draw_pixel_c), 6);
			rb_define_module_function(draw, "setColor", RFUNC(DrawWrappers::rb_set_color), 4);
			rb_define_module_function(draw, "setColorO", RFUNC(DrawWrappers::rb_set_color_o), 1);
			rb_define_module_function(draw, "setFont", RFUNC(DrawWrappers::rb_set_font), 1);
			rb_define_module_function(draw, "getFont", RFUNC(DrawWrappers::rb_get_font), 0);
			rb_define_module_function(draw, "getColor", RFUNC(DrawWrappers::rb_get_set_color), 0);
			rb_define_module_function(draw, "getBackgroundColor", RFUNC(DrawWrappers::rb_get_set_color), 0);
			rb_define_module_function(draw, "text", RFUNC(DrawWrappers::rb_draw_text), 3);
			rb_define_module_function(draw, "justifyText", RFUNC(DrawWrappers::rb_draw_justified_text), 5);
		}
	}
}
