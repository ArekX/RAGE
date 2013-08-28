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
#include <allegro5/allegro_memfile.h>
#include <physfs.h>
#include <ruby/thread.h>
#include <exts/dl/dl.h>

/* Compilation cofiguration */
#include "rage_config.h"

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
#include "Logic_Wrappers.h"
#include "BaseFile_Wrapper.h"
#include "MemFile_Wrapper.h"
#include "File_Wrapper.h"
#include "Network_Wrappers.h"
#include "TCPServer_Wrapper.h"
#include "TCPClient_Wrapper.h"
#include "UDPSocket_Wrapper.h"

/* Box2D Wrappers */


/* Include configuration class */
#include "RAGEConfiguration.h"

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
			static char* get_file_path(VALUE filename);
			static RAGEConfiguration* get_config(void);
			Ruby(int argc, char** argv);
			~Ruby(void);
		};
	}
}
