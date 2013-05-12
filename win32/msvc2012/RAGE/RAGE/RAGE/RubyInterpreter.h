#pragma once
#include <iostream>
#include <vector>
#include <ruby.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

/* Include Wrappers */
#include "Graphics_Wrappers.h"
#include "Bitmap_Wrapper.h"
#include "Events_Wrapper.h"

#define RFUNC RUBY_METHOD_FUNC

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
			static void Ruby::init_queue();
			static ALLEGRO_EVENT_QUEUE* get_queue();
		};
	}
}
