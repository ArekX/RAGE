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

#include "RubyInterpreter.h"

/* RAGE Classes and modules */
#include "Graphics_Wrappers.h"
#include "Font_Wrapper.h"
#include "Audio_Wrapper.h"
#include "Music_Wrapper.h"
#include "Sfx_Wrapper.h"
#include "Color_Wrapper.h"
#include "BaseFile_Wrapper.h"
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
#include "IniFile_Wrapper.h"
#include "FS_Wrappers.h"
#include "Joystick_Wrapper.h"
#include "VertexArray_Wrapper.h"
#include "ParticleEngine_Wrapper.h"
#include "Logic_Wrappers.h"
#include "MemFile_Wrapper.h"
#include "File_Wrapper.h"
#include "Network_Wrappers.h"
#include "TCPServer_Wrapper.h"
#include "TCPClient_Wrapper.h"
#include "UDPSocket_Wrapper.h"
#include <Box2D/Common/b2Settings.h>

#if RAGE_COMPILE_DL
#include <ext\dl\dl_ruby.h>
#endif

#if RAGE_COMPILE_DATE
#include <ext/date/date_ruby.h>
#endif

#if RAGE_COMPILE_PATHNAME
#include <ext/pathname/pathname_ruby.h>
#endif

#if RAGE_COMPILE_DIGEST
#include <ext/digest/digest_ruby.h>
#endif

extern "C"
{
#if RAGE_COMPILE_DL
	void Init_dl(void);
#endif

#if RAGE_COMPILE_ZLIB
	void Init_zlib(void);
#endif

#if RAGE_COMPILE_STRINGIO
	void Init_stringio(void);
#endif

#if RAGE_COMPILE_STRSCAN
	void Init_strscan(void);
#endif

#if RAGE_COMPILE_DATE
	void Init_date_core(void);
#endif

#if RAGE_COMPILE_PATHNAME
	void Init_pathname(void);
#endif

#if RAGE_COMPILE_DIGEST
	void Init_digest(void);
	void Init_bubblebabble(void);
	void Init_md5(void);
	void Init_rmd160(void);
	void Init_sha1(void);
	void Init_sha2(void);
#endif


	void Init_thread(void);
	void ruby_Init_Fiber_as_Coroutine(void);
}

namespace RAGE
{
	namespace Interpreter
	{
		bool configured = false;
		std::vector<std::string*> *loaded_files;
		RAGEConfiguration *gConfig;

		static VALUE rb_rage_about(VALUE self)
		{
			printf("RAGE Engine\nFull Name: Ruby Awesome Game Engine\nVersion: %s", RAGE_ENGINE_VERSION);
			printf(" [%s] \nCopyright (c) Panic Aleksandar[Ruby Interpreter]\n", RAGE_ENGINE_CODE_NAME);
			ruby_show_version();
			printf("Copyright (c) Yukihiro Matsumoto (a.k.a matz)\n\n");
			printf("[Allegro Game Library]\nAllegro Game Library Version: %s\nCopyright (c) Allegro Development Team\n\n", ALLEGRO_VERSION_STR);
			printf("[Box2D Physics Engine]\nBox2D Library Version: %ld\.%ld\.%ld\nDeveloped by Erin Catto.\n\n", b2_version.major, b2_version.minor, b2_version.revision);
			return Qnil;
		}

		static void set_default_config()
		{
			gConfig = new RAGEConfiguration(Qnil);
		}

		static VALUE rb_rage_require_wrapper(VALUE self, VALUE filename)
		{
			ALLEGRO_FILE *afile;
			char *absolute_file = Ruby::get_file_path(filename);
			if (absolute_file == NULL)
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}

			for (int i = 0; i < loaded_files->size(); i++)
				if (loaded_files->at(i)->compare(absolute_file) == 0) return Qtrue;

			afile = al_fopen(absolute_file, "rb");

			if ((afile == NULL) || al_ferror(afile))
			{
				rb_raise(rb_eArgError, RAGE_ERROR_FS_CANNOT_LOAD, StringValueCStr(filename));
				return Qfalse;
			}

			char *data = new char[al_fsize(afile) + 1];
			char buffer[2048];
			int64_t pos = 0;
			int i, error = 0;
			
			size_t read_bytes = al_fread(afile, buffer, 2048);

			while(read_bytes != 0)
			{
				for (i = 0; i < read_bytes; i++)
					data[pos++] = buffer[i];

				read_bytes = al_fread(afile, buffer, 2048);
			}

			data[al_fsize(afile)] = 0;

			al_fclose(afile);

			loaded_files->push_back(new std::string(absolute_file));

			rb_eval_string_protect(data, &error);

			delete[] data;
			
			#ifdef DEVELOPMENT_VERSION
			if (strcmp(StringValueCStr(filename), RAGE_BOOT_SCRIPT) == 0)
				PRINT(RAGE_DEV_END_TEXT);
			#endif
			return Qtrue;
		}

		static VALUE rb_rage_configure(VALUE self, VALUE config)
		{
			if (!configured)
			{
				gConfig = new RAGEConfiguration(config);

				configured = true;

				if (!gConfig->is_current_version()) PRINT(RAGE_RB_INCOMPATIBLE);
				
				return Qtrue;
			}

			return Qfalse;
		}

		static void load_protect(const char* filename)
		{
			VALUE fstring = rb_str_new_cstr(filename);
			VALUE full_file = rb_find_file(fstring);

			if (TYPE(full_file) != T_STRING)
			{
				PRINT(RAGE_RB_FILE_MISSING_ERROR, filename);
				getc(stdin);
				return;
			}

			ruby_set_script_name(fstring);
			int error = 0;

			rb_load_protect(full_file, 1, &error);

			#ifdef DEVELOPMENT_VERSION
			if (strcmp(filename, RAGE_BOOT_SCRIPT) == 0) 
				PRINT(RAGE_DEV_END_TEXT);
			#endif
		}

		int Ruby::file_exists(VALUE filename)
		{
			#if RAGE_COMPILE_FS
			if (RAGE::Filesystem::FSWrappers::is_physfs_on())
			{
				if (PHYSFS_exists(StringValueCStr(filename)))
					return 2;
				else
					return -2;
			}
			#endif

			/* Check Ruby search path */
			VALUE fname = rb_find_file(filename);

			if (TYPE(fname) != T_STRING)
				return -1;
			else
				return 1;
		}

		char* Ruby::get_file_path(VALUE filename)
		{
			#if RAGE_COMPILE_FS
			if (RAGE::Filesystem::FSWrappers::is_physfs_on())
			{
				if (PHYSFS_exists(StringValueCStr(filename)))
					return StringValueCStr(filename);
				else
					return NULL;
			}
			#endif

			/* Check Ruby search path */
			VALUE fname = rb_find_file(filename);

			if (TYPE(fname) != T_STRING)
				return NULL;
			else
				return StringValueCStr(fname);
		}

		RAGEConfiguration* Ruby::get_config(void)
		{
			return gConfig;
		}

		Ruby::Ruby(int argc, char** argv)
		{
			loaded_files = new std::vector<std::string*>();

			/* Initialize Ruby Interpreter */
			ruby_sysinit(&argc, &argv);
			{
				RUBY_INIT_STACK;
				ruby_init();

				/* Define Global Functions */
				VALUE rage = rb_define_module("RAGE");
				rb_define_module_function(rage, "require", RFUNC(rb_rage_require_wrapper), 1);
				rb_define_module_function(rage, "about", RFUNC(rb_rage_about), 0);
				rb_define_module_function(rage, "configure", RFUNC(rb_rage_configure), 1);

				/* Set search path to exe file */
				std::string str(*argv);
				rb_ary_push(rb_gv_get("$:"), rb_str_new_cstr(str.substr(0, str.find_last_of(DS) + 1).c_str()));

				#if RAGE_COMPILE_FS
				if (!PHYSFS_mount(argv[0], "/", 0))
				{
					if (al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_GAME_FILE).c_str()))
					{
						PHYSFS_mount(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_GAME_FILE).c_str(), "/", 0);
						RAGE::Filesystem::FSWrappers::force_physfs_on();
					}
					else
					{
						PHYSFS_mount(str.substr(0, str.find_last_of(DS) + 1).c_str(), "/", 0);
					}
				}
				else
					RAGE::Filesystem::FSWrappers::force_physfs_on();
				

				PHYSFS_setWriteDir(str.substr(0, str.find_last_of(DS) + 1).c_str());
				#endif

				/* Set Command line arguments */
				rb_gv_set(RAGE_ARGS_VAR, rb_ary_new());
				for (int i = 0; i < argc; i++)
					rb_ary_push(rb_gv_get(RAGE_ARGS_VAR), rb_str_new_cstr(argv[i]));
				
				#ifdef DEVELOPMENT_VERSION
				
				/* Set debug vars */
				rb_gv_set(RAGE_DEBUG_GLOBAL_VAR, Qtrue);

				PRINT(RAGE_DEV_TEXT);
				
				#endif
				
				/* Load config script */
				#if RAGE_COMPILE_FS
				if (!RAGE::Filesystem::FSWrappers::is_physfs_on() && al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_CONF_SCRIPT).c_str()))
					load_protect(RAGE_CONF_SCRIPT);
				else if (RAGE::Filesystem::FSWrappers::is_physfs_on() && PHYSFS_exists(RAGE_CONF_SCRIPT))
					rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_CONF_SCRIPT));
				#else
				if (al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_CONF_SCRIPT).c_str()))
					load_protect(RAGE_CONF_SCRIPT);
				#endif
				
				if (!configured)
					set_default_config();

				// Initialize Ruby Threads
				Init_thread();
				ruby_Init_Fiber_as_Coroutine();
				rb_provide("thread.so");

				/* Initialize ruby extensions */
				#if RAGE_COMPILE_ZLIB
				if (gConfig->is_on("Zlib"))
				{
					Init_zlib();
					rb_provide("zlib.so");
				}
					
				#endif

				#if RAGE_COMPILE_STRINGIO
				if (gConfig->is_on("StringIO"))
				{
					Init_stringio();
					rb_provide("stringio.so");
				}
				#endif

				#if RAGE_COMPILE_STRSCAN
				if (gConfig->is_on("StringScanner"))
				{
					Init_strscan();
					rb_provide("strscan.so");
				}
				#endif

				#if RAGE_COMPILE_DATE
				if (gConfig->is_on("Date"))
				{
					Init_date_core();
					rb_eval_string_protect(date_rb_data, nullptr);
					rb_provide("date_core.so");
				}
				#endif

				#if RAGE_COMPILE_PATHNAME
				if (gConfig->is_on("Pathname"))
				{
					Init_pathname();
					rb_eval_string_protect(pathname_rb_data, nullptr);
					rb_provide("pathname.so");
				}
				
				#endif

				#if RAGE_COMPILE_DL
				if (gConfig->is_on("DL"))
				{
					Init_dl();
					rb_eval_string_protect(dl_rb_data, nullptr);
					rb_provide("dl.so");
				}
				#endif


				#if RAGE_COMPILE_DIGEST
				if (gConfig->is_on("Digest"))
				{
					Init_digest();
					Init_bubblebabble();
					Init_md5();
					Init_rmd160();
					Init_sha1();
					Init_sha2();
					rb_eval_string_protect(digest_rb_data, nullptr);
					rb_provide("digest.so");
					rb_provide("bubblebabble.so");
					rb_provide("md5.so");
					rb_provide("rmd160.so");
					rb_provide("sha1.so");
					rb_provide("sha2.so");
				}
				#endif
				

				/* = Load RAGE modules = */
				RAGE::Graphics::GraphicsWrappers::load_wrappers();

				RAGE_INIT_FS_MODULE 
				RAGE_INIT_EVENTS_MODULE 
				RAGE_INIT_INPUT_MODULE 
				RAGE_INIT_AUDIO_MODULE 
				RAGE_INIT_DRAW_MODULE
				RAGE_INIT_NETWORK_MODULE 
				RAGE_INIT_LOGIC_MODULE 

				RAGE_INIT_BASE_FILE_CLASS 
				RAGE_INIT_FILE_CLASS 
				RAGE_INIT_MEM_FILE_CLASS 
				RAGE_INIT_INI_FILE_CLASS 
				RAGE_INIT_BITMAP_CLASS 
				RAGE_INIT_FONT_CLASS 
				RAGE_INIT_COLOR_CLASS 
				RAGE_INIT_SHADER_CLASS 
				RAGE_INIT_VERTEX_ARRAY_CLASS 
				RAGE_INIT_BASE_EVENT_CLASS 
				RAGE_INIT_TIMER_EVENT_CLASS 
				RAGE_INIT_JOY_EVENT_CLASS 
				RAGE_INIT_KEYBOARD_EVENT_CLASS 
				RAGE_INIT_MOUSE_EVENT_CLASS 
				RAGE_INIT_SCREEN_EVENT_CLASS 
				RAGE_INIT_MUSIC_CLASS 
				RAGE_INIT_SFX_CLASS 
				RAGE_INIT_JOYSTICK_CLASS 
				RAGE_INIT_NETWORK_CLASS 
				RAGE_INIT_TCP_CLIENT_CLASS 
				RAGE_INIT_UDP_SOCKET_CLASS 
				RAGE_INIT_PARTICLE_ENGINE_CLASS 

				/* Perform additional tasks */
				RAGE_EVENT_MODULE_START
				RAGE_AUDIO_MODULE_START

				RAGE::Graphics::GraphicsWrappers::initialize_graphics();
				
				RAGE_DRAW_MODULE_START

				/* Load boot script */

				#if RAGE_COMPILE_FS
				if (!RAGE::Filesystem::FSWrappers::is_physfs_on() && al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_BOOT_SCRIPT).c_str()))
					load_protect(RAGE_BOOT_SCRIPT);
				else if (RAGE::Filesystem::FSWrappers::is_physfs_on() && PHYSFS_exists(RAGE_BOOT_SCRIPT))
					rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_BOOT_SCRIPT));
				#else
				if (al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_BOOT_SCRIPT).c_str()))
					load_protect(RAGE_BOOT_SCRIPT);
				#endif

				#ifdef DEVELOPMENT_VERSION
				else
				{
					#ifdef WIN32
					MessageBox(al_get_win_window_handle(RAGE::Graphics::GraphicsWrappers::get_display()), RAGE_DEV_MESSAGE_W, L"RAGE Game Engine", MB_OK | MB_ICONINFORMATION);
					#else
					PRINT(RAGE_DEV_MESSAGE_L);
					#endif
					PRINT(RAGE_DEV_MESSAGE_EXIT);
					getc(stdin);
					
				}
				#endif

				/* Run Finalizer for modules */
				RAGE_EVENT_MODULE_FINALIZE
				RAGE_AUDIO_MODULE_FINALIZE

				/* Finalize graphics */
				RAGE::Graphics::GraphicsWrappers::finalize_graphics();
			}
		}


		Ruby::~Ruby(void)
		{
			for (int i = 0; i < loaded_files->size(); i++)
				delete loaded_files->at(i);

			delete loaded_files;

			delete gConfig;

			/* Close Ruby subsystem */
			ruby_finalize();
		}
	};
};