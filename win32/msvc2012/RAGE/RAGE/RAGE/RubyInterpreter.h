#pragma once
#include <iostream>
#include <ruby.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

/* Include Wrappers */
#include "Graphics_Wrappers.h"
#include "Bitmap_Wrapper.h"

#define RFUNC(x) (VALUE(*)(...))x

#ifdef WIN32
#define DS '\\'
#endif

namespace RAGE
{
	namespace Interpreter
	{
		class Ruby
		{
		private:
			static VALUE rb_require_protect(VALUE filename);
		public:
			Ruby(int argc, char** argv);
			~Ruby(void);
		};
	}
}
