#pragma once

#include "RubyInterpreter.h"

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

		static int window_x;
		static int window_y;
		static char* window_title;

		class Graphics
		{
		private:
			static void recreate_display();

		public:
			Graphics(GraphicsConfig config);

			/* Ruby functions */
			static VALUE rb_setTitle(VALUE self, VALUE title);
			static VALUE rb_setVSync(VALUE self, VALUE val);
			static VALUE rb_setFullscreen(VALUE self, VALUE val);
			static VALUE rb_setWindowPosition(VALUE self, VALUE x, VALUE y);
			static VALUE rb_cursorVisible(VALUE self, VALUE val);
			static VALUE rb_graphicsupdate(VALUE self);
			static VALUE rb_graphics_clear(VALUE self);
			static VALUE rb_graphics_clear2(VALUE self, VALUE r, VALUE g, VALUE b);
			static VALUE rb_graphics_set_clipping_rect(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h);
			static VALUE rb_graphics_reset_clipping_rect(VALUE self);
			static VALUE rb_set_target(VALUE self, VALUE bitmap);
			static VALUE rb_get_target(VALUE self);
		};
	}
}

