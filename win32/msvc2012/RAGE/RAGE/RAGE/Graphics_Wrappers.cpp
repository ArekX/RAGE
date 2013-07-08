#include "Graphics_Wrappers.h"

namespace RAGE
{
	namespace Graphics
	{
		ALLEGRO_COLOR bg_color;
		RAGEConfig start_config;
		ALLEGRO_DISPLAY *display;
		ALLEGRO_MOUSE_CURSOR *mouse_bitmap_cursor = NULL;
		Shader *active_shader = NULL;

		int mouse_focus_x = 0;
		int mouse_focus_y = 0;
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

				if (bmp->bitmap == NULL)
				{
					rb_raise(rb_eException, RAGE_BITMAP_NOT_CREATED_ERROR);
					return Qnil;
				}

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

		VALUE GraphicsWrappers::rb_graphics_set_background_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			bg_color = al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a));
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_title(VALUE self, VALUE title)
		{
			if (TYPE(title) == T_STRING)
			{
				delete[] window_title;
				window_title = new char[RSTRING_LENINT(title)];
				strcpy(window_title, StringValueCStr(title));
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
			al_set_blender(FIX2UINT(rop), FIX2UINT(rsrc), FIX2UINT(rdst));

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

		VALUE GraphicsWrappers::rb_get_pos_x(VALUE self)
		{
			int x;

			al_get_window_position(display, &x, NULL);

			return INT2FIX(x);
		}

		VALUE GraphicsWrappers::rb_get_pos_y(VALUE self)
		{
			int y;

			al_get_window_position(display, NULL, &y);

			return INT2FIX(y);
		}

		VALUE GraphicsWrappers::rb_get_screen_w(VALUE self)
		{
			return INT2FIX(al_get_display_width(display));
		}

		VALUE GraphicsWrappers::rb_get_screen_h(VALUE self)
		{
			return INT2FIX(al_get_display_height(display));
		}

		VALUE GraphicsWrappers::rb_set_icon(VALUE self, VALUE icon_bitmap)
		{
			Bitmap *bmp;
			Data_Get_Struct(icon_bitmap, Bitmap, bmp);

			al_set_display_icon(display, bmp->bitmap);

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_inhibit_screen_saver(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
				al_inhibit_screensaver(true);
			else if (TYPE(val) == T_FALSE)
				al_inhibit_screensaver(false);

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_blending_mode_alpha(VALUE self, VALUE rop, VALUE rsrc, VALUE rdst, VALUE aop, VALUE asrc, VALUE adst)
		{
			al_set_separate_blender(FIX2UINT(rop), FIX2UINT(rsrc), FIX2UINT(rdst), FIX2UINT(aop), FIX2UINT(asrc), FIX2UINT(adst));

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_graphics_set_background_color_object(VALUE self, VALUE color)
		{
			
			if (rb_class_of(color) != RAGE::Graphics::ColorWrapper::get_ruby_class())
			{
				rb_raise(rb_eArgError, RAGE_COLOR_ERROR);
				return Qnil;
			}

			Color *clr;
			Data_Get_Struct(color, Color, clr);

			bg_color = clr->color;
			
			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_mouse_xy(VALUE self, VALUE x, VALUE y)
		{
			if (al_set_mouse_xy(display, FIX2INT(x), FIX2INT(y)))
				return Qtrue;

			return Qfalse;
		}

		VALUE GraphicsWrappers::rb_get_display_modes(VALUE self)
		{
			VALUE return_array = rb_ary_new();

			VALUE one_ary;
			ALLEGRO_DISPLAY_MODE dm;

		    int max_modes = al_get_num_display_modes();

			for (int i = 0; i < max_modes; i++)
			{
				al_get_display_mode(i, &dm);
				one_ary = rb_ary_new();

				rb_ary_push(one_ary, UINT2NUM(dm.width));
				rb_ary_push(one_ary, UINT2NUM(dm.height));
				rb_ary_push(one_ary, UINT2NUM(dm.refresh_rate));
				rb_ary_push(one_ary, UINT2NUM(dm.format));

				rb_gc_register_address(&one_ary);

				rb_ary_push(return_array, one_ary);
			}

			rb_gc_register_address(&return_array);

			return return_array;
		}

		VALUE GraphicsWrappers::rb_set_mouse_cursor(VALUE self, VALUE cursor_index)
		{
			int c_index = FIX2INT(cursor_index);

			if (c_index != -1)
				al_set_system_mouse_cursor(display, (ALLEGRO_SYSTEM_MOUSE_CURSOR)c_index);
			else if ((c_index == -1) && (mouse_bitmap_cursor != NULL))
				al_set_mouse_cursor(display, mouse_bitmap_cursor);

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_mouse_bitmap(VALUE self, VALUE cursor_bitmap, VALUE focus_x, VALUE focus_y)
		{
			Bitmap *bmp;

			Data_Get_Struct(cursor_bitmap, Bitmap, bmp);

			if (mouse_bitmap_cursor != NULL)
				al_destroy_mouse_cursor(mouse_bitmap_cursor);

			mouse_bitmap_cursor = al_create_mouse_cursor(bmp->bitmap, NUM2UINT(focus_x), NUM2UINT(focus_y));

			if (mouse_bitmap_cursor == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_MOUSE_CURSOR_CREATE_FAIL);
			}

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_grab_mouse(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
				al_grab_mouse(display);
			else if (TYPE(val) == T_TRUE)
				al_ungrab_mouse();

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_shader(VALUE self, VALUE shader)
		{
			if (active_shader != NULL)
				active_shader->is_active = false;

			if (TYPE(shader) == T_NIL)
			{
				glUseProgramObjectARB(0);
				return Qnil;
			}

			Shader *sh;

			Data_Get_Struct(shader, Shader, sh);

			if (sh->code_added)
			{
				glUseProgramObjectARB(sh->glsl_shader_program);
				sh->is_active = true;

				active_shader = sh;
			}
			else
				rb_raise(rb_eException, RAGE_ERROR_SHADER_CODE_NOT_ADDED);

			return Qnil;
		}

		VALUE GraphicsWrappers::rb_set_fullscreen_window(VALUE self, VALUE val)
		{
			if (TYPE(val) == T_TRUE)
			{
				al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_FULLSCREEN_WINDOW);
				recreate_display();
				return Qtrue;
			}
			else if (TYPE(val) == T_FALSE)
			{
				al_set_new_display_flags(al_get_new_display_flags() & 0xDFF);
				recreate_display();
				return Qtrue;
			}
			return Qfalse;
		}

		VALUE GraphicsWrappers::rb_get_glsl_version(VALUE self)
		{
			
			return rb_str_new2((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
		}

		VALUE GraphicsWrappers::rb_get_opengl_version(VALUE self)
		{
			return rb_str_new2((char*)glGetString(GL_VERSION));
		}

		void GraphicsWrappers::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE g = rb_define_module_under(rage, "Graphics");

			rb_define_const(g, "ADD", INT2FIX(ALLEGRO_ADD));
			rb_define_const(g, "SRC_MIN_DEST",  INT2FIX(ALLEGRO_SRC_MINUS_DEST));
			rb_define_const(g, "DEST_MIN_SRC", INT2FIX(ALLEGRO_DEST_MINUS_SRC));
			
			rb_define_const(g, "BLEND_ZERO", INT2FIX(ALLEGRO_ZERO));
			rb_define_const(g, "BLEND_ONE", INT2FIX(ALLEGRO_ONE));
			rb_define_const(g, "BLEND_ALPHA",  INT2FIX(ALLEGRO_ALPHA));
			rb_define_const(g, "BLEND_INV_ALPHA",  INT2FIX(ALLEGRO_INVERSE_ALPHA));

			rb_define_const(g, "BLEND_SRC_COLOR", INT2FIX(ALLEGRO_SRC_COLOR));
			rb_define_const(g, "BLEND_DEST_COLOR", INT2FIX(ALLEGRO_DEST_COLOR));
			rb_define_const(g, "BLEND_INV_SRC_COLOR",  INT2FIX(ALLEGRO_INVERSE_SRC_COLOR));
			rb_define_const(g, "BLEND_INV_DEST_COLOR",  INT2FIX(ALLEGRO_INVERSE_DEST_COLOR));

			/* Mouse cursor type defintions */
			rb_define_const(g, "MOUSE_NONE", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_NONE));
			rb_define_const(g, "MOUSE_DEFAULT", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT));
			rb_define_const(g, "MOUSE_ARROW", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW));
			rb_define_const(g, "MOUSE_ALT_SELECT", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_ALT_SELECT));
			rb_define_const(g, "MOUSE_BUSY", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_BUSY));
			rb_define_const(g, "MOUSE_EDIT", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_EDIT));
			rb_define_const(g, "MOUSE_LINK", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK));
			rb_define_const(g, "MOUSE_MOVE", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_MOVE));
			rb_define_const(g, "MOUSE_PRECISION", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_PRECISION));
			rb_define_const(g, "MOUSE_PROGRESS", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_PROGRESS));
			rb_define_const(g, "MOUSE_QUESTION", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_QUESTION));
			rb_define_const(g, "MOUSE_RESIZE_E", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_E));
			rb_define_const(g, "MOUSE_RESIZE_N", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_N));
			rb_define_const(g, "MOUSE_RESIZE_NE", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_NE));
			rb_define_const(g, "MOUSE_RESIZE_NW", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_NW));
			rb_define_const(g, "MOUSE_RESIZE_S", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_S));
			rb_define_const(g, "MOUSE_RESIZE_SE", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_SE));
			rb_define_const(g, "MOUSE_RESIZE_SW", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_SW));
			rb_define_const(g, "MOUSE_RESIZE_W", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_RESIZE_W));
			rb_define_const(g, "MOUSE_UNAVAILABLE", INT2FIX(ALLEGRO_SYSTEM_MOUSE_CURSOR_UNAVAILABLE));
			rb_define_const(g, "MOUSE_BITMAP", INT2FIX(RAGE_MOUSE_BITMAP_CURSOR_INDEX));

			/* GLSL shader type defintions */
			rb_define_const(g, "FRAGMENT_SHADER", INT2FIX(RAGE_FRAGMENT_SHADER));
			rb_define_const(g, "VERTEX_SHADER", INT2FIX(RAGE_VERTEX_SHADER));

			/* Define Module Functions */
			rb_define_module_function(g, "title=", RFUNC(GraphicsWrappers::rb_set_title), 1);
			rb_define_module_function(g, "title", RFUNC(GraphicsWrappers::rb_get_title), 0);
			rb_define_module_function(g, "setBlendingMode", RFUNC(GraphicsWrappers::rb_set_blending_mode), 3);
			rb_define_module_function(g, "setBlendingModeAlpha", RFUNC(GraphicsWrappers::rb_set_blending_mode_alpha), 6);
			rb_define_module_function(g, "setVSync", RFUNC(GraphicsWrappers::rb_set_vsync), 1);
			rb_define_module_function(g, "setFullscreen", RFUNC(GraphicsWrappers::rb_set_fullscreen), 1);
			rb_define_module_function(g, "setCursorVisible", RFUNC(GraphicsWrappers::rb_cursor_visible), 1);
			rb_define_module_function(g, "setWindowPosition", RFUNC(GraphicsWrappers::rb_set_window_position), 2);
			rb_define_module_function(g, "setWindowSize", RFUNC(GraphicsWrappers::rb_set_display_size), 2);
			rb_define_module_function(g, "setIcon", RFUNC(GraphicsWrappers::rb_set_icon), 1);
			
			rb_define_module_function(g, "positionX", RFUNC(GraphicsWrappers::rb_get_pos_x), 0);
			rb_define_module_function(g, "positionY", RFUNC(GraphicsWrappers::rb_get_pos_y), 0);
			rb_define_module_function(g, "screenWidth", RFUNC(GraphicsWrappers::rb_get_screen_w), 0);
			rb_define_module_function(g, "screenHeight", RFUNC(GraphicsWrappers::rb_get_screen_h), 0);
			
			rb_define_module_function(g, "inhibitScreenSaver", RFUNC(GraphicsWrappers::rb_inhibit_screen_saver), 1);

			rb_define_module_function(g, "update", RFUNC(GraphicsWrappers::rb_graphics_update), 0);
			rb_define_module_function(g, "clear", RFUNC(GraphicsWrappers::rb_graphics_clear), 0);
			rb_define_module_function(g, "setBackgroundColor", RFUNC(GraphicsWrappers::rb_graphics_set_background_color), 4);
			rb_define_module_function(g, "setBackgroundColorO", RFUNC(GraphicsWrappers::rb_graphics_set_background_color_object), 1);
			rb_define_module_function(g, "setTarget", RFUNC(GraphicsWrappers::rb_set_target), 1);
			rb_define_module_function(g, "getTarget", RFUNC(GraphicsWrappers::rb_get_target), 0);
			rb_define_module_function(g, "getTime", RFUNC(GraphicsWrappers::rb_get_time), 0);
			rb_define_module_function(g, "setClippingRect", RFUNC(GraphicsWrappers::rb_graphics_set_clipping_rect), 4);
			rb_define_module_function(g, "resetClippingRect", RFUNC(GraphicsWrappers::rb_graphics_reset_clipping_rect), 0);

			rb_define_module_function(g, "getDisplayModes", RFUNC(GraphicsWrappers::rb_get_display_modes), 0);
			rb_define_module_function(g, "setMousePosition", RFUNC(GraphicsWrappers::rb_set_mouse_xy), 2);
			rb_define_module_function(g, "setMouseCursor", RFUNC(GraphicsWrappers::rb_set_mouse_cursor), 1);
			rb_define_module_function(g, "setMouseBitmap", RFUNC(GraphicsWrappers::rb_set_mouse_bitmap), 3);
			rb_define_module_function(g, "setMouseGrab", RFUNC(GraphicsWrappers::rb_set_grab_mouse), 1);

			rb_define_module_function(g, "setShader", RFUNC(GraphicsWrappers::rb_set_shader), 1);

			rb_define_module_function(g, "setMaximizedWindow", RFUNC(GraphicsWrappers::rb_set_fullscreen_window), 1);
			
			rb_define_module_function(g, "getOpenGLVersion", RFUNC(GraphicsWrappers::rb_get_opengl_version), 0);
			rb_define_module_function(g, "getGLSLVersion", RFUNC(GraphicsWrappers::rb_get_glsl_version), 0);
		}

		void GraphicsWrappers::initialize_graphics(RAGEConfig cfg)
		{
			start_config = cfg;

			al_set_new_display_flags(ALLEGRO_OPENGL);

			if (cfg.vsync)
				al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
			else
				al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);

			if (cfg.fullscreen && !cfg.maximized_window)
				al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_FULLSCREEN);
			
			if (cfg.maximized_window)
				al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_FULLSCREEN_WINDOW);

			al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_OPENGL);

			window_title = cfg.name;
			display = al_create_display(cfg.width, cfg.height);
			al_get_window_position(display, &window_x, &window_y);
			al_set_window_title(display, cfg.name);
			al_set_target_backbuffer(display);
			al_flip_display();

			if (cfg.use_rageEvents)
			al_register_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(display));
		}

		void GraphicsWrappers::recreate_display()
		{
			int width = al_get_display_width(display);
			int height = al_get_display_height(display);

			if (start_config.use_rageEvents)
			al_unregister_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(display));
			
			al_destroy_display(display);
			al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_OPENGL);
			display = al_create_display(width, height);
			al_set_window_title(display, window_title);
			al_set_window_position(display, window_x, window_y);
			al_set_target_backbuffer(display);
			al_flip_display();

			if (start_config.use_rageEvents)
			al_register_event_source(RAGE::Events::EventsWrapper::get_queue(), al_get_display_event_source(display));
		}

		ALLEGRO_DISPLAY* GraphicsWrappers::get_display()
		{
			return display;
		}
	}
}


