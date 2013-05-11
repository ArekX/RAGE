#include "Graphics_Wrappers.h"

namespace RAGE
{
	namespace Graphics
	{

		void Graphics_Wrappers::LoadWrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE g = rb_define_module_under(rage, "Graphics");

			/* Define Module Functions */
			rb_define_module_function(g, "setTitle", RFUNC(RAGE::Graphics::Graphics::rb_setTitle), 1);
			rb_define_module_function(g, "setVsync", RFUNC(RAGE::Graphics::Graphics::rb_setVSync), 1);
			rb_define_module_function(g, "setFullscreen", RFUNC(RAGE::Graphics::Graphics::rb_setFullscreen), 1);
			rb_define_module_function(g, "setWindowPosition", RFUNC(RAGE::Graphics::Graphics::rb_setWindowPosition), 2);
			rb_define_module_function(g, "cursorVisible", RFUNC(RAGE::Graphics::Graphics::rb_cursorVisible), 1);
		}
	}
}


