#include "Graphics.h"

namespace RAGE
{
	namespace Graphics
	{
		Graphics::Graphics(GraphicsConfig config)
		{
			if (config.vsync == true)
				al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);

			if (config.fullscreen == true)
				al_set_new_display_flags(ALLEGRO_FULLSCREEN);
			
			window_title = "RAGE Game";
			ALLEGRO_DISPLAY* disp = al_create_display(config.width, config.height);
			al_get_window_position(disp, &window_x, &window_y);
			al_set_window_title(disp, window_title);
			al_flip_display();
		}

		Graphics::~Graphics(void)
		{

		}

		void Graphics::recreateDisplay()
		{
			ALLEGRO_DISPLAY *new_display, *old = al_get_current_display();
			int width = al_get_display_width(old);
			int height = al_get_display_height(old);
			al_destroy_display(old);
			new_display = al_create_display(width, height);
			al_set_target_backbuffer(new_display);
			al_set_window_title(new_display, window_title);
			al_set_window_position(new_display, window_x, window_y);
			al_flip_display();
			// TODO: Events
			// TODO: Resource manager for bitmaps. When display is destroyed they are turned into memory bitmaps. 
			//       Need to reload them.
			
		}

		VALUE Graphics::rb_setTitle(VALUE self, VALUE title)
		{
			if (TYPE(title) == T_STRING)
			{
				window_title = StringValueCStr(title);
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
				recreateDisplay();
				return Qtrue;
			}
			else if (TYPE(val) == T_FALSE)
			{
				al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
				recreateDisplay();
				return Qtrue;
			}
			return Qfalse;
			
		}

		VALUE Graphics::rb_setFullscreen(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
			{
				al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_FULLSCREEN);
				recreateDisplay();
				return Qtrue;
			}
			else if (TYPE(val) == T_FALSE)
			{
				al_set_new_display_flags(al_get_new_display_flags() & 0xFFD);
				recreateDisplay();
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
