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
			static void recreateDisplay();

		public:
			Graphics(GraphicsConfig config);
			~Graphics(void);

			/* Ruby functions */
			static VALUE rb_setTitle(VALUE self, VALUE title);
			static VALUE rb_setVSync(VALUE self, VALUE val);
			static VALUE rb_setFullscreen(VALUE self, VALUE val);
			static VALUE rb_setWindowPosition(VALUE self, VALUE x, VALUE y);
			static VALUE rb_cursorVisible(VALUE self, VALUE val);
			static VALUE rb_graphicsupdate(VALUE self);
		};
	}
}

