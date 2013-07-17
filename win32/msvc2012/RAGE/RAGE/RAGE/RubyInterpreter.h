#pragma once
#include "defines.h"

#include <iostream>
#include <vector>
#include <ruby.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/platform/almsvc.h>

#ifdef WIN32
#include <allegro5/allegro_windows.h>
#endif

#include <physfs.h>
#include <ruby/thread.h>
#include <exts/dl/dl.h>

typedef struct {
	char* name;
	int width;
	int height;
	bool fullscreen;
	bool vsync;
	bool maximized_window;
	bool use_rageBitmap;
	bool use_rageMusic;
	bool use_rageSfx;
	bool use_rageIniFile;  
	bool use_rageScreenEvent;
	bool use_rageKeyEvent;
	bool use_rageMouseEvent;
	bool use_rageTimerEvent;
	bool use_rageJoyEvent;
	bool use_rageVertexArray;
	bool use_rageShader;
	bool use_rageFont;
	bool use_rageColor;
	bool use_rageJoystick;
	bool use_rageEvents;
	bool use_rageFS;
	bool use_rageDraw;
	bool use_rageInput;
	bool use_rageRubyDL;
	bool use_rageRubyZlib;
} RAGEConfig;

/* Include Wrappers */
#include "Graphics_Wrappers.h"
#include "Font_Wrapper.h"
#include "Color_Wrapper.h"
#include "Draw_Wrappers.h"
#include "Bitmap_Wrapper.h"
#include "Shader_Wrapper.h"
#include "Events_Wrapper.h"
#include "Input_Wrappers.h"
#include "TimerEvent_Wrapper.h"
#include "Event_Wrapper.h"
#include "KeyboardEvent_Wrapper.h"
#include "MouseEvent_Wrapper.h"
#include "ScreenEvent_Wrapper.h"
#include "JoyEvent_Wrapper.h"
#include "Audio_Wrapper.h"
#include "Music_Wrapper.h"
#include "Sfx_Wrapper.h"
#include "IniFile_Wrapper.h"
#include "FS_Wrappers.h"
#include "Joystick_Wrapper.h"
#include "VertexArray_Wrapper.h"
#include "ParticleEngine_Wrapper.h"

namespace RAGE
{
	namespace Interpreter
	{
		class Ruby
		{
		private:
			static VALUE rb_require_protect(VALUE filename);
			
		public:
			static int file_exists(VALUE filename);
			static char* Ruby::get_file_path(VALUE filename);
			Ruby(int argc, char** argv);
			~Ruby(void);
		};
	}
}
