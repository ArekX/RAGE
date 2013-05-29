#pragma once
#include "RubyInterpreter.h"

#define RAGE_OP_ADD 1
#define RAGE_OP_DST_MIN_SRC 2
#define RAGE_OP_SRC_MIN_DST 3
#define RAGE_BLEND_ZERO 4
#define RAGE_BLEND_ONE 5
#define RAGE_BLEND_ALPHA 6 
#define RAGE_BLEND_INV_ALPHA 7

namespace RAGE
{
	namespace Graphics
	{

		typedef struct 
		{
		  int width;
		  int height;
		  bool vsync;
		  bool fullscreen;
		} GraphicsConfig;


		class GraphicsWrappers
		{

		private:
			static VALUE rb_set_title(VALUE self, VALUE title);
			static VALUE rb_get_title(VALUE self);
			static VALUE rb_set_blending_mode(VALUE self, VALUE rop, VALUE rsrc, VALUE rdst);
			static VALUE rb_set_vsync(VALUE self, VALUE val);
			static VALUE rb_set_fullscreen(VALUE self, VALUE val);
			static VALUE rb_set_window_position(VALUE self, VALUE x, VALUE y);
			static VALUE rb_cursor_visible(VALUE self, VALUE val);
			static VALUE rb_graphics_update(VALUE self);
			static VALUE rb_graphics_clear(VALUE self);
			static VALUE rb_graphics_set_background_color(VALUE self, VALUE r, VALUE g, VALUE b);
			static VALUE rb_graphics_set_clipping_rect(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h);
			static VALUE rb_graphics_reset_clipping_rect(VALUE self);
			static VALUE rb_set_target(VALUE self, VALUE bitmap);
			static VALUE rb_get_target(VALUE self);
			static VALUE rb_set_display_size(VALUE self, VALUE width, VALUE height);
		public:
			static void load_wrappers();
			static void initialize_graphics(GraphicsConfig cfg);
			static void recreate_display();
			static ALLEGRO_DISPLAY* get_display();
		};

	}
}