/*
Copyright (c) 2014 Aleksandar Panic

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


#ifdef WIN32
#include <allegro5/platform/almsvc.h>
#include <allegro5/allegro_windows.h>

/* Common link dependencies */
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Iphlpapi.lib")


#if _MSC_VER == 1800
#pragma comment(lib, "msvcr120-ruby210-static.lib")
#pragma comment(lib, "allegro-5.0.10-monolith-static-mt.lib")
#pragma comment(lib, "openal-1.14-static-mt.lib")
#pragma comment(lib, "freetype-2.4.8-static-mt.lib")
#pragma comment(lib, "libFLAC-1.2.1-static-mt.lib")
#pragma comment(lib, "libogg-1.2.1-static-mt.lib")
#pragma comment(lib, "libvorbis-1.3.2-static-mt.lib")
#pragma comment(lib, "libvorbisfile-1.3.2-static-mt.lib")
#pragma comment(lib, "zlib-1.2.5-static-mt.lib")
#pragma comment(lib, "dumb-0.9.3-static-mt.lib")
#endif

#else
#include <allegro5/platform/alunix.h>
#endif

/*
Information about compilation:

When any of the RAGE_COMPILE_ defines are set to 1
they will be compiled and included in final executable.
Please note that some of the features are dependant on
others (i.e. Particle Engine is dependant on Bitmap),
and they too will not be compiled without them.
*/

/* Ruby Extensions */
#define RAGE_COMPILE_DL 1
#define RAGE_COMPILE_ZLIB 1
#define RAGE_COMPILE_STRINGIO 1
#define RAGE_COMPILE_STRSCAN 1
#define RAGE_COMPILE_DATE 1
#define RAGE_COMPILE_SOCKET 1
#define RAGE_COMPILE_DIGEST 1

/* Filesystem */
#define RAGE_COMPILE_FS 1

#define RAGE_COMPILE_FILES 1
#define RAGE_COMPILE_FILE 1
#define RAGE_COMPILE_MEM_FILE 1
#define RAGE_COMPILE_INI_FILE 1

/* Events */
#define RAGE_COMPILE_EVENTS 1
#define RAGE_COMPILE_TIMER_EVENT 1
#define RAGE_COMPILE_JOY_EVENT 1
#define RAGE_COMPILE_KEYBOARD_EVENT 1
#define RAGE_COMPILE_MOUSE_EVENT 1
#define RAGE_COMPILE_SCREEN_EVENT 1

/* Audio */
#define RAGE_COMPILE_AUDIO 1
#define RAGE_COMPILE_MUSIC 1
#define RAGE_COMPILE_SFX 1

/* Drawing routines */
#define RAGE_COMPILE_DRAW 1
#define RAGE_COMPILE_BITMAP 1
#define RAGE_COMPILE_FONT 1
#define RAGE_COMPILE_COLOR 1
#define RAGE_COMPILE_SHADER 1
#define RAGE_COMPILE_VERTEX_ARRAY 1
#define RAGE_COMPILE_PARTICLE_ENGINE 1

/* Network routines */
#define RAGE_COMPILE_NETWORK 1
#define RAGE_COMPILE_TCP_SERVER 1
#define RAGE_COMPILE_TCP_CLIENT 1
#define RAGE_COMPILE_UDP_SOCKET 1

/* Input */
#define RAGE_COMPILE_INPUT 1
#define RAGE_COMPILE_JOYSTICK 1

/* Logic */
#define RAGE_COMPILE_LOGIC 1

/* Physics */
#define RAGE_COMPILE_PHYSICS 0
#define RAGE_COMPILE_PHYS_DEBUG_DRAW 0

/* End of compilation configuration */

/* Ruby ext libs */
#if RAGE_COMPILE_SOCKET
#pragma comment(lib, "socket.lib")
#endif

/* Initializer methods */
#define RAGE_INIT_FS_MODULE 
#define RAGE_INIT_EVENTS_MODULE 
#define RAGE_INIT_INPUT_MODULE 
#define RAGE_INIT_AUDIO_MODULE 
#define RAGE_INIT_DRAW_MODULE 
#define RAGE_INIT_NETWORK_MODULE 
#define RAGE_INIT_LOGIC_MODULE 
#define RAGE_INIT_BASE_FILE_CLASS 
#define RAGE_INIT_FILE_CLASS 
#define RAGE_INIT_MEM_FILE_CLASS 
#define RAGE_INIT_INI_FILE_CLASS 
#define RAGE_INIT_BITMAP_CLASS 
#define RAGE_INIT_FONT_CLASS 
#define RAGE_INIT_COLOR_CLASS 
#define RAGE_INIT_SHADER_CLASS 
#define RAGE_INIT_VERTEX_ARRAY_CLASS 
#define RAGE_INIT_BASE_EVENT_CLASS 
#define RAGE_INIT_TIMER_EVENT_CLASS 
#define RAGE_INIT_JOY_EVENT_CLASS 
#define RAGE_INIT_KEYBOARD_EVENT_CLASS 
#define RAGE_INIT_MOUSE_EVENT_CLASS 
#define RAGE_INIT_SCREEN_EVENT_CLASS 
#define RAGE_INIT_MUSIC_CLASS 
#define RAGE_INIT_SFX_CLASS 
#define RAGE_INIT_JOYSTICK_CLASS 
#define RAGE_INIT_NETWORK_CLASS 
#define RAGE_INIT_TCP_CLIENT_CLASS 
#define RAGE_INIT_UDP_SOCKET_CLASS 
#define RAGE_INIT_PARTICLE_ENGINE_CLASS 


/* INIT METHODS */
#define RAGE_EVENT_MODULE_START 
#define RAGE_AUDIO_MODULE_START 
#define RAGE_DRAW_MODULE_START

/* FINALIZE METHODS */
#define RAGE_EVENT_MODULE_FINALIZE
#define RAGE_AUDIO_MODULE_FINALIZE

/* Redefinition methods */

#if RAGE_COMPILE_EVENTS
#undef RAGE_INIT_EVENTS_MODULE
#define RAGE_INIT_EVENTS_MODULE RAGE::Events::EventsWrapper::load_wrappers();
#endif

#if RAGE_COMPILE_INPUT
#undef RAGE_INIT_INPUT_MODULE
#define RAGE_INIT_INPUT_MODULE RAGE::Input::InputWrappers::load_wrappers();
#endif

#if RAGE_COMPILE_AUDIO
#undef RAGE_INIT_AUDIO_MODULE
#define RAGE_INIT_AUDIO_MODULE RAGE::Audio::AudioWrappers::load_wrappers();
#endif

#if RAGE_COMPILE_DRAW
#undef RAGE_INIT_DRAW_MODULE
#define RAGE_INIT_DRAW_MODULE RAGE::Graphics::DrawWrappers::load_wrappers();
#endif

#if RAGE_COMPILE_NETWORK
#undef RAGE_INIT_NETWORK_MODULE
#define RAGE_INIT_NETWORK_MODULE RAGE::Network::NetworkWrappers::load_wrappers();
#endif

#if RAGE_COMPILE_LOGIC
#undef RAGE_INIT_LOGIC_MODULE
#define RAGE_INIT_LOGIC_MODULE RAGE::Logic::LogicWrappers::load_wrappers();
#endif

#if RAGE_COMPILE_FILES
#undef RAGE_INIT_BASE_FILE_CLASS
#define RAGE_INIT_BASE_FILE_CLASS RAGE::Filesystem::BaseFileWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_FILES && RAGE_COMPILE_FILE
#undef RAGE_INIT_FILE_CLASS
#define RAGE_INIT_FILE_CLASS RAGE::Filesystem::FileWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_FILES && RAGE_COMPILE_MEM_FILE
#undef RAGE_INIT_MEM_FILE_CLASS
#define RAGE_INIT_MEM_FILE_CLASS RAGE::Filesystem::MemFileWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_FILES && RAGE_COMPILE_INI_FILE
#undef RAGE_INIT_INI_FILE_CLASS
#define RAGE_INIT_INI_FILE_CLASS RAGE::Filesystem::IniFileWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_BITMAP
#undef RAGE_INIT_BITMAP_CLASS
#define RAGE_INIT_BITMAP_CLASS RAGE::Graphics::BitmapWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_FONT
#undef RAGE_INIT_FONT_CLASS
#define RAGE_INIT_FONT_CLASS RAGE::Graphics::FontWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_COLOR
#undef RAGE_INIT_COLOR_CLASS
#define RAGE_INIT_COLOR_CLASS RAGE::Graphics::ColorWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_BITMAP && RAGE_COMPILE_SHADER
#undef RAGE_INIT_SHADER_CLASS
#define RAGE_INIT_SHADER_CLASS RAGE::Graphics::ShaderWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_VERTEX_ARRAY
#undef RAGE_INIT_VERTEX_ARRAY_CLASS
#define RAGE_INIT_VERTEX_ARRAY_CLASS RAGE::Graphics::VertexArrayWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS
#undef RAGE_INIT_BASE_EVENT_CLASS
#define RAGE_INIT_BASE_EVENT_CLASS RAGE::Events::EventWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_TIMER_EVENT
#undef RAGE_INIT_TIMER_EVENT_CLASS
#define RAGE_INIT_TIMER_EVENT_CLASS RAGE::Events::TimerEventWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_JOY_EVENT
#undef RAGE_INIT_JOY_EVENT_CLASS
#define RAGE_INIT_JOY_EVENT_CLASS RAGE::Events::JoyEventWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_KEYBOARD_EVENT
#undef RAGE_INIT_KEYBOARD_EVENT_CLASS
#define RAGE_INIT_KEYBOARD_EVENT_CLASS RAGE::Events::KeyboardEventWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_MOUSE_EVENT
#undef RAGE_INIT_MOUSE_EVENT_CLASS
#define RAGE_INIT_MOUSE_EVENT_CLASS RAGE::Events::MouseEventWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_SCREEN_EVENT
#undef RAGE_INIT_SCREEN_EVENT_CLASS
#define RAGE_INIT_SCREEN_EVENT_CLASS RAGE::Events::ScreenEventWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_MUSIC
#undef RAGE_INIT_MUSIC_CLASS
#define RAGE_INIT_MUSIC_CLASS RAGE::Audio::MusicWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_SFX
#undef RAGE_INIT_SFX_CLASS
#define RAGE_INIT_SFX_CLASS RAGE::Audio::SfxWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS && RAGE_COMPILE_JOYSTICK
#undef RAGE_INIT_JOYSTICK_CLASS
#define RAGE_INIT_JOYSTICK_CLASS RAGE::Input::JoystickWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_NETWORK
#undef RAGE_INIT_NETWORK_CLASS
#define RAGE_INIT_NETWORK_CLASS RAGE::Network::TCPServerWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_TCP_CLIENT
#undef RAGE_INIT_TCP_CLIENT_CLASS
#define RAGE_INIT_TCP_CLIENT_CLASS RAGE::Network::TCPClientWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_UDP_SOCKET
#undef RAGE_INIT_UDP_SOCKET_CLASS
#define RAGE_INIT_UDP_SOCKET_CLASS RAGE::Network::UDPSocketWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_NETWORK && RAGE_COMPILE_PARTICLE_ENGINE
#undef RAGE_INIT_PARTICLE_ENGINE_CLASS
#define RAGE_INIT_PARTICLE_ENGINE_CLASS RAGE::Graphics::ParticleEngineWrapper::load_ruby_class();
#endif

#if RAGE_COMPILE_EVENTS
#undef RAGE_EVENT_MODULE_START
#define RAGE_EVENT_MODULE_START RAGE::Events::EventsWrapper::init_queue();
#define RAGE_EVENT_MODULE_FINALIZE RAGE::Events::EventsWrapper::finalize_queue();
#endif

#if RAGE_COMPILE_AUDIO
#undef RAGE_AUDIO_MODULE_START
#define RAGE_AUDIO_MODULE_START RAGE::Audio::AudioWrappers::init_audio();
#define RAGE_AUDIO_MODULE_FINALIZE RAGE::Audio::AudioWrappers::finalize_audio();
#endif

#if RAGE_COMPILE_DRAW
#undef RAGE_DRAW_MODULE_START
#define RAGE_DRAW_MODULE_START RAGE::Graphics::DrawWrappers::init();
#endif