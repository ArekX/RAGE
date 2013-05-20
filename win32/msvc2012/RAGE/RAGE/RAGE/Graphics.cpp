#include "Graphics.h"

namespace RAGE
{
	namespace Graphics
	{
		ALLEGRO_COLOR bg_color;

		Graphics::Graphics(GraphicsConfig config)
		{
			if (config.vsync == true)
				al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
			else
				al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);

			if (config.fullscreen == true)
				al_set_new_display_flags(ALLEGRO_FULLSCREEN);
			
			window_title = "RAGE Game";
			al_set_new_display_flags(ALLEGRO_OPENGL);
			
			ALLEGRO_DISPLAY* disp = al_create_display(config.width, config.height);
			al_get_window_position(disp, &window_x, &window_y);
			al_set_window_title(disp, window_title);
			al_set_target_backbuffer(disp); 
			al_flip_display();
			al_register_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(disp));
			
		}

		void Graphics::recreate_display()
		{
			ALLEGRO_DISPLAY *new_display, *old = al_get_current_display();
			int width = al_get_display_width(old);
			int height = al_get_display_height(old);
			al_unregister_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(old));
			al_destroy_display(old);
			new_display = al_create_display(width, height);
			al_set_window_title(new_display, window_title);
			al_set_window_position(new_display, window_x, window_y);
			al_flip_display();
			// TODO: Resource manager for bitmaps. When display is destroyed they are turned into memory bitmaps. 
			//       Need to reload them.
			al_register_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(new_display));
			
		}

		VALUE Graphics::rb_set_target(VALUE self, VALUE bitmap)
		{
			if (TYPE(bitmap) == T_NIL)
			{
				al_set_target_backbuffer(al_get_current_display());
			}
			else
			{
				Bitmap* bmp;
				Data_Get_Struct(bitmap, Bitmap, bmp);
				al_set_target_bitmap(bmp->bitmap);
			}

			return Qnil;
		}

		VALUE Graphics::rb_get_target(VALUE self)
		{
			Bitmap *bmp;
			VALUE ret_bmp = RAGE::Graphics::BitmapWrapper::new_ruby_class_instance();
			Data_Get_Struct(ret_bmp, Bitmap, bmp);
			bmp->bitmap = al_get_target_bitmap();
			return ret_bmp;
		}

		VALUE Graphics::rb_graphics_set_clipping_rect(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h)
		{
			al_set_clipping_rectangle(FIX2INT(x), FIX2INT(y), FIX2INT(w), FIX2INT(h));
			return Qnil;
		}

		VALUE Graphics::rb_graphics_reset_clipping_rect(VALUE self)
		{
			ALLEGRO_BITMAP *bmp = al_get_target_bitmap();
			al_set_clipping_rectangle(0, 0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp));
			return Qnil;
		}

		VALUE Graphics::rb_graphicsupdate(VALUE self)
		{
			al_flip_display();
			return Qnil;
		}

		VALUE Graphics::rb_graphics_clear(VALUE self)
		{
			
			al_clear_to_color(bg_color);
			return Qnil;
		}

		VALUE Graphics::rb_graphics_set_background_color(VALUE self, VALUE r, VALUE g, VALUE b)
		{
			bg_color = al_map_rgb(FIX2INT(r), FIX2INT(g), FIX2INT(b));
			return Qnil;
		}

		VALUE Graphics::rb_setTitle(VALUE self, VALUE title)
		{
			if (TYPE(title) == T_STRING)
			{
				window_title = StringValueCStr(title);
				rb_gc_force_recycle(title);
				al_set_window_title(al_get_current_display(), window_title);
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE Graphics::rb_setVSync(VALUE self, VALUE val)
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

		VALUE Graphics::rb_setFullscreen(VALUE self, VALUE val)
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

		VALUE Graphics::rb_setWindowPosition(VALUE self, VALUE x, VALUE y)
		{
			if ((TYPE(x) == T_FIXNUM) && (TYPE(y) == T_FIXNUM))
			{	
				window_x = FIX2UINT(x);
				window_y = FIX2UINT(y);
				al_set_window_position(al_get_current_display(), window_x, window_y);
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE Graphics::rb_cursorVisible(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
			{
				al_show_mouse_cursor(al_get_current_display());
				return Qtrue;
			}
			else if (TYPE(val) == T_FALSE)
			{
				al_hide_mouse_cursor(al_get_current_display());
				return Qtrue;
			}
			return Qfalse;
		}

	}
}
