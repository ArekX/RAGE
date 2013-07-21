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
			static VALUE rb_inhibit_screen_saver(VALUE self, VALUE val);

			static VALUE rb_set_mouse_xy(VALUE self, VALUE x, VALUE y);
			static VALUE rb_get_display_modes(VALUE self);

			static VALUE rb_set_mouse_cursor(VALUE self, VALUE cursor_index);
			static VALUE rb_set_mouse_bitmap(VALUE self, VALUE cursor_bitmap, VALUE focus_x, VALUE focus_y);

			static VALUE rb_set_grab_mouse(VALUE self, VALUE val);

			static VALUE rb_set_shader(VALUE self, VALUE shader);

			static VALUE rb_get_glsl_version(VALUE self);
			static VALUE rb_get_opengl_version(VALUE self);

			static VALUE rb_get_blending_mode(VALUE self);
			static VALUE rb_get_blending_mode_alpha(VALUE self);
			static VALUE rb_hold_bitmap_drawing(VALUE self, VALUE val);
			static VALUE rb_is_bitmap_drawing_held(VALUE self);
		public:
			static void load_wrappers(void);
			static void initialize_graphics(void);
			static void recreate_display(void);
			static void set_screen_processing(ALLEGRO_EVENT_QUEUE *queue, bool process_screen);
			static ALLEGRO_DISPLAY* get_display(void);
		};

	}
}