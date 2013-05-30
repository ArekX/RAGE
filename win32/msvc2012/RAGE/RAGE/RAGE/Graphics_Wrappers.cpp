#include "Graphics_Wrappers.h"

namespace RAGE
{
	namespace Graphics
	{
		ALLEGRO_COLOR bg_color;
		GraphicsConfig start_config;
		ALLEGRO_DISPLAY *display;

		int window_x;
		int window_y;
		char* window_title;

		VALUE GraphicsWrappers::rb_set_target(VALUE self, VALUE bitmap)
		{
			if (TYPE(bitmap) == T_NIL)
			{
				al_set_target_backbuffer(display);
			}
			else
			{
				Bitmap* bmp;
				Data_Get_Struct(bitmap, Bitmap, bmp);
				al_set_target_bitmap(bmp->bitmap);
			}

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_get_target(VALUE self)
		{
			Bitmap *bmp;
			VALUE ret_bmp = RAGE::Graphics::BitmapWrapper::new_ruby_class_instance();
			Data_Get_Struct(ret_bmp, Bitmap, bmp);
			bmp->bitmap = al_get_target_bitmap();
			return ret_bmp;
		}

		VALUE GraphicsWrappers::rb_graphics_set_clipping_rect(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h)
		{
			al_set_clipping_rectangle(FIX2INT(x), FIX2INT(y), FIX2INT(w), FIX2INT(h));
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_graphics_reset_clipping_rect(VALUE self)
		{
			al_reset_clipping_rectangle();
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_graphics_update(VALUE self)
		{
			al_flip_display();
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_graphics_clear(VALUE self)
		{
			
			al_clear_to_color(bg_color);
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_graphics_set_background_color(VALUE self, VALUE r, VALUE g, VALUE b)
		{
			bg_color = al_map_rgb(FIX2INT(r), FIX2INT(g), FIX2INT(b));
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_title(VALUE self, VALUE title)
		{
			if (TYPE(title) == T_STRING)
			{
				window_title = StringValueCStr(title);
				al_set_window_title(display, window_title);
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE GraphicsWrappers::rb_get_title(VALUE self)
		{		
			return rb_str_new_cstr(window_title);
		}

		VALUE GraphicsWrappers::rb_set_blending_mode(VALUE self, VALUE rop, VALUE rsrc, VALUE rdst)
		{
			int op, src, dst;

			switch(FIX2INT(rop))
			{
				case RAGE_OP_ADD:
					op = ALLEGRO_ADD;
					break;
				case RAGE_OP_SRC_MIN_DST:
					op = ALLEGRO_SRC_MINUS_DEST;
					break;
				case RAGE_OP_DST_MIN_SRC:
					op = ALLEGRO_DEST_MINUS_SRC;
					break;
				default:
					op = ALLEGRO_ADD;
			}

			switch(FIX2INT(rsrc))
			{
				case RAGE_BLEND_ZERO:
					src = ALLEGRO_ZERO;
					break;
				case RAGE_BLEND_ONE:
					src = ALLEGRO_ONE;
					break;
				case RAGE_BLEND_ALPHA:
					src = ALLEGRO_ALPHA;
					break;
				case RAGE_BLEND_INV_ALPHA:
					src = ALLEGRO_INVERSE_ALPHA;
					break;
				default:
					src = ALLEGRO_ONE;
			}

			switch(FIX2INT(rdst))
			{
				case RAGE_BLEND_ZERO:
					dst = ALLEGRO_ZERO;
					break;
				case RAGE_BLEND_ONE:
					dst = ALLEGRO_ONE;
					break;
				case RAGE_BLEND_ALPHA:
					dst = ALLEGRO_ALPHA;
					break;
				case RAGE_BLEND_INV_ALPHA:
					dst = ALLEGRO_INVERSE_ALPHA;
					break;
				default:
					dst = ALLEGRO_INVERSE_ALPHA;
			}

			al_set_blender(op, src, dst);

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_vsync(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
			{
				al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
				recreate_display();
				return Qtrue;
			}
			else if (TYPE(val) == T_FALSE)
			{
				al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
				recreate_display();
				return Qtrue;
			}
			return Qfalse;
			
		}

		VALUE GraphicsWrappers::rb_set_fullscreen(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
			{
				al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_FULLSCREEN);
				recreate_display();
				return Qtrue;
			}
			else if (TYPE(val) == T_FALSE)
			{
				al_set_new_display_flags(al_get_new_display_flags() & 0xFFD);
				recreate_display();
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE GraphicsWrappers::rb_set_window_position(VALUE self, VALUE x, VALUE y)
		{
			if ((TYPE(x) == T_FIXNUM) && (TYPE(y) == T_FIXNUM))
			{	
				window_x = FIX2UINT(x);
				window_y = FIX2UINT(y);
				al_set_window_position(display, window_x, window_y);
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE GraphicsWrappers::rb_cursor_visible(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
			{
			
				al_show_mouse_cursor(display);
				return Qtrue;
			}
			else if (TYPE(val) == T_FALSE)
			{
				al_hide_mouse_cursor(display);
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE GraphicsWrappers::rb_set_display_size(VALUE self, VALUE width, VALUE height)
		{
			al_resize_display(display, FIX2UINT(width), FIX2UINT(height));
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_get_time(VALUE self)
		{
			return DBL2NUM(al_get_time());
		}

		void GraphicsWrappers::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE g = rb_define_module_under(rage, "Graphics");

			rb_define_const(g, "ADD", INT2FIX(RAGE_OP_ADD));
			rb_define_const(g, "DEST_MIN_SRC", INT2FIX(RAGE_OP_DST_MIN_SRC));
			rb_define_const(g, "SRC_MIN_DEST",  INT2FIX(RAGE_OP_SRC_MIN_DST));

			rb_define_const(g, "BLEND_ZERO", INT2FIX(RAGE_BLEND_ZERO));
			rb_define_const(g, "BLEND_ONE", INT2FIX(RAGE_BLEND_ONE));
			rb_define_const(g, "BLEND_ALPHA",  INT2FIX(RAGE_BLEND_ALPHA));
			rb_define_const(g, "BLEND_INV_ALPHA",  INT2FIX(RAGE_BLEND_INV_ALPHA));

			/* Define Module Functions */
			rb_define_module_function(g, "title=", RFUNC(GraphicsWrappers::rb_set_title), 1);
			rb_define_module_function(g, "title", RFUNC(GraphicsWrappers::rb_get_title), 0);
			rb_define_module_function(g, "setBlendingMode", RFUNC(GraphicsWrappers::rb_set_blending_mode), 3);
			rb_define_module_function(g, "setVSync", RFUNC(GraphicsWrappers::rb_set_vsync), 1);
			rb_define_module_function(g, "setFullscreen", RFUNC(GraphicsWrappers::rb_set_fullscreen), 1);
			rb_define_module_function(g, "setCursorVisible", RFUNC(GraphicsWrappers::rb_cursor_visible), 1);
			rb_define_module_function(g, "setWindowPosition", RFUNC(GraphicsWrappers::rb_set_window_position), 2);
			rb_define_module_function(g, "setWindowSize", RFUNC(GraphicsWrappers::rb_set_display_size), 2);
			rb_define_module_function(g, "update", RFUNC(GraphicsWrappers::rb_graphics_update), 0);
			rb_define_module_function(g, "clear", RFUNC(GraphicsWrappers::rb_graphics_clear), 0);
			rb_define_module_function(g, "setBackgroundColor", RFUNC(GraphicsWrappers::rb_graphics_set_background_color), 3);
			rb_define_module_function(g, "setTarget", RFUNC(GraphicsWrappers::rb_set_target), 1);
			rb_define_module_function(g, "getTarget", RFUNC(GraphicsWrappers::rb_get_target), 0);
			rb_define_module_function(g, "getTime", RFUNC(GraphicsWrappers::rb_get_time), 0);
			rb_define_module_function(g, "setClippingRect", RFUNC(GraphicsWrappers::rb_graphics_set_clipping_rect), 4);
			rb_define_module_function(g, "resetClippingRect", RFUNC(GraphicsWrappers::rb_graphics_reset_clipping_rect), 0);
		}

		void GraphicsWrappers::initialize_graphics(GraphicsConfig cfg)
		{
			start_config = cfg;

			if (cfg.vsync == true)
				al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
			else
				al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);

			if (cfg.fullscreen == true)
				al_set_new_display_flags(ALLEGRO_FULLSCREEN);
			
			window_title = "RAGE Game";
			al_set_new_display_flags(ALLEGRO_OPENGL);
			display = al_create_display(cfg.width, cfg.height);
			al_get_window_position(display, &window_x, &window_y);
			al_set_window_title(display, window_title);
			al_set_target_backbuffer(display); 
			al_flip_display();
			al_register_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(display));
		}

		void GraphicsWrappers::recreate_display()
		{
			int width = al_get_display_width(display);
			int height = al_get_display_height(display);
			al_unregister_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(display));
			al_destroy_display(display);
			display = al_create_display(width, height);
			al_set_window_title(display, window_title);
			al_set_window_position(display, window_x, window_y);
			al_flip_display();
			// TODO: Resource manager for bitmaps. When display is destroyed they are turned into memory bitmaps. 
			//       Need to reload them.
			al_register_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(display));
		}

		ALLEGRO_DISPLAY* GraphicsWrappers::get_display()
		{
			return display;
		}
	}
}


