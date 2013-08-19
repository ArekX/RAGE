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
		class GraphicsWrappers
		{

		private:
			static VALUE rb_set_title(VALUE self, VALUE title);
			static VALUE rb_get_title(VALUE self);
			static VALUE rb_set_blending_mode(VALUE self, VALUE rop, VALUE rsrc, VALUE rdst);
			static VALUE rb_set_blending_mode_alpha(VALUE self, VALUE rop, VALUE rsrc, VALUE rdst, VALUE aop, VALUE asrc, VALUE adst);
			static VALUE rb_set_vsync(VALUE self, VALUE val);
			static VALUE rb_set_fullscreen(VALUE self, VALUE val);
			static VALUE rb_set_fullscreen_window(VALUE self, VALUE val);
			static VALUE rb_set_window_position(VALUE self, VALUE x, VALUE y);
			static VALUE rb_cursor_visible(VALUE self, VALUE val);
			static VALUE rb_graphics_update(VALUE self);
			static VALUE rb_set_target(VALUE self, VALUE bitmap);
			static VALUE rb_get_target(VALUE self);
			static VALUE rb_set_display_size(VALUE self, VALUE width, VALUE height);
			static VALUE rb_get_time(VALUE self);

			static VALUE rb_get_pos_x(VALUE self);
			static VALUE rb_get_pos_y(VALUE self);
			static VALUE rb_get_screen_w(VALUE self);
			static VALUE rb_get_screen_h(VALUE self);

			static VALUE rb_set_icon(VALUE self, VALUE icon_bitmap);
			static VALUE rb_get_icon(VALUE self);

			static VALUE rb_inhibit_screen_saver(VALUE self, VALUE val);

			static VALUE rb_set_mouse_xy(VALUE self, VALUE x, VALUE y);
			static VALUE rb_get_display_modes(VALUE self);

			static VALUE rb_set_mouse_cursor(VALUE self, VALUE cursor_index);
			static VALUE rb_set_mouse_bitmap(VALUE self, VALUE cursor_bitmap, VALUE focus_x, VALUE focus_y);

			static VALUE rb_set_grab_mouse(VALUE self, VALUE val);

			static VALUE rb_set_shader(VALUE self, VALUE shader);
			static VALUE rb_get_shader(VALUE self);

			static VALUE rb_get_glsl_version(VALUE self);
			static VALUE rb_get_opengl_version(VALUE self);

			static VALUE rb_get_blending_mode(VALUE self);
			static VALUE rb_get_blending_mode_alpha(VALUE self);
			static VALUE rb_hold_bitmap_drawing(VALUE self, VALUE val);
			static VALUE rb_is_bitmap_drawing_held(VALUE self);

			static VALUE rb_set_bitmap_flags(VALUE self, VALUE flags);
		public:
			static void load_wrappers(void);
			static void initialize_graphics(void);
			static void recreate_display(void);
			static int get_bitmap_flags(void);
			static void set_screen_processing(ALLEGRO_EVENT_QUEUE *queue, bool process_screen);
			static ALLEGRO_DISPLAY* get_display(void);
		};

	}
}