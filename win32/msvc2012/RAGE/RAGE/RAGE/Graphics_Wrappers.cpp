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

		VALUE GraphicsWrappers::rb_graphicsupdate(VALUE self)
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

		VALUE GraphicsWrappers::rb_setTitle(VALUE self, VALUE title)
		{
			if (TYPE(title) == T_STRING)
			{
				window_title = StringValueCStr(title);
				al_set_window_title(display, window_title);
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE GraphicsWrappers::rb_setVSync(VALUE self, VALUE val)
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

		VALUE GraphicsWrappers::rb_setFullscreen(VALUE self, VALUE val)
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

		VALUE GraphicsWrappers::rb_setWindowPosition(VALUE self, VALUE x, VALUE y)
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

		VALUE GraphicsWrappers::rb_cursorVisible(VALUE self, VALUE val)
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

		void GraphicsWrappers::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE g = rb_define_module_under(rage, "Graphics");

			/* Define Module Functions */
			rb_define_module_function(g, "setTitle", RFUNC(GraphicsWrappers::rb_setTitle), 1);
			rb_define_module_function(g, "setVsync", RFUNC(GraphicsWrappers::rb_setVSync), 1);
			rb_define_module_function(g, "setFullscreen", RFUNC(GraphicsWrappers::rb_setFullscreen), 1);
			rb_define_module_function(g, "setWindowPosition", RFUNC(GraphicsWrappers::rb_setWindowPosition), 2);
			rb_define_module_function(g, "cursorVisible", RFUNC(GraphicsWrappers::rb_cursorVisible), 1);
			rb_define_module_function(g, "update", RFUNC(GraphicsWrappers::rb_graphicsupdate), 0);
			rb_define_module_function(g, "clear", RFUNC(GraphicsWrappers::rb_graphics_clear), 0);
			rb_define_module_function(g, "setBackgroundColor", RFUNC(GraphicsWrappers::rb_graphics_set_background_color), 3);
			rb_define_module_function(g, "setTarget", RFUNC(GraphicsWrappers::rb_set_target), 1);
			rb_define_module_function(g, "getTarget", RFUNC(GraphicsWrappers::rb_get_target), 0);
			rb_define_module_function(g, "setClippingRect", RFUNC(GraphicsWrappers::rb_graphics_set_clipping_rect), 4);
			rb_define_module_function(g, "resetClippingRect", RFUNC(GraphicsWrappers::rb_graphics_reset_clipping_rect), 0);
			// TODO: Check to see if there is more stuff needed for Graphics module.
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


