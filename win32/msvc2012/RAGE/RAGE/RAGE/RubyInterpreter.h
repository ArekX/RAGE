#pragma once
#include "defines.h"

#include <iostream>
#include <vector>
#include <ruby.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <ruby/encoding.h>
#include <ruby/thread.h>

/* Include Wrappers */
#include "Graphics_Wrappers.h"
#include "Draw_Wrappers.h"
#include "Bitmap_Wrapper.h"
#include "Events_Wrapper.h"
#include "Input_Wrappers.h"
#include "TimerEvent_Wrapper.h"
#include "Event_Wrapper.h"
#include "KeyboardEvent_Wrapper.h"
#include "MouseEvent_Wrapper.h"
#include "ScreenEvent_Wrapper.h"
#include "Audio_Wrapper.h"
#include "Music_Wrapper.h"
#include "Sfx_Wrapper.h"
#include "IniFile_Wrapper.h"

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
