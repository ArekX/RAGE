#include "RubyInterpreter.h"
#include <exts/dl/ruby_ext_dl_rb_data.h>

extern "C"
{
	void Init_dl(void);
	void Init_zlib(void);
}

namespace RAGE
{
	namespace Interpreter
	{
		bool configured = false;
		RAGEConfig gConfig;

		static void load_extension_rb_data()
		{
			int error = 0;

			rb_eval_string_protect(ruby_dl_extension_rb_data, &error);
			if (error) PRINT(RAGE_ERROR_DL_EXT_RB_DATA_FAILED);
		}

		static VALUE rb_rage_about(VALUE self)
		{
			PRINTF("RAGE Engine\nFull Name: Ruby Awesome Game Engine\nVersion: %s\nCopyright (c) Panic Aleksandar\n\n", RAGE_ENGINE_VERSION);
			PRINT("[Ruby Interpreter]\n");
			ruby_show_version();
			PRINT("Copyright (c) Yukihiro Matsumoto (a.k.a matz)\n\n");
			PRINTF("[Allegro Game Library]\nAllegro Game Library Version: %s\nCopyright (c) Allegro Development Team\n\n", ALLEGRO_VERSION_STR);
			return Qnil;
		}

		static void set_default_config()
		{
			gConfig.name = new char[10];
			strcpy(gConfig.name, "RAGE Game");

			gConfig.width = 640;
			gConfig.height = 480;
			gConfig.fullscreen = false;
			gConfig.vsync = false;
			gConfig.maximized_window = false;
			gConfig.use_rageBitmap = true;
			gConfig.use_rageSfx = true;
			gConfig.use_rageIniFile = true;
			gConfig.use_rageScreenEvent = true;
			gConfig.use_rageTimerEvent = true;
			gConfig.use_rageKeyEvent = true;
			gConfig.use_rageMouseEvent = true;
			gConfig.use_rageJoyEvent = true;
			gConfig.use_rageVertexArray = true;
			gConfig.use_rageShader = true;
			gConfig.use_rageFont = true;
			gConfig.use_rageColor = true;
			gConfig.use_rageJoystick = true;
			gConfig.use_rageEvents = true;
			gConfig.use_rageFS = true;
			gConfig.use_rageDraw = true;
			gConfig.use_rageInput = true;			
			gConfig.use_rageRubyDL = true;
			gConfig.use_rageRubyZlib = true;
		}

		static VALUE rb_rage_require_wrapper(VALUE self, VALUE filename)
		{
			int file_status = Ruby::file_exists(filename);
			ALLEGRO_FILE *afile;
			if ((file_status < 0) || ((file_status == 2) && !RAGE::Filesystem::FSWrappers::is_physfs_on()))
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}

			if (file_status == 1)
			{
				VALUE fname = rb_find_file(filename);
				afile = al_fopen(StringValueCStr(fname), "rb");
			}
			else
				afile = al_fopen(StringValueCStr(filename), "rb");

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

			rb_eval_string_protect(data, &error);
			
			#ifdef DEVELOPMENT_VERSION
			if (strcmp(StringValueCStr(filename), "boot.rb") == 0)
				PRINT(RAGE_DEV_END_TEXT);
			#endif

			return Qnil;
		}

		static VALUE rb_rage_configure(VALUE self, VALUE config)
		{
			if (!configured)
			{
				VALUE item = rb_hash_aref(config, rb_str_new2("name"));
			
				if (TYPE(item) != T_NIL)
				{
					gConfig.name = new char[RSTRING_LENINT(item)];
					strcpy(gConfig.name, StringValueCStr(item));
				}
				else
				{
					gConfig.name = new char[10];
					strcpy(gConfig.name, "RAGE Game");
				}

				CONFIG_SET(config, item, "width", gConfig.width, FIX2UINT(item), 640);
				CONFIG_SET(config, item, "height", gConfig.height, FIX2UINT(item), 480);
				CONFIG_SET(config, item, "fullscreen", gConfig.fullscreen, (TYPE(item) == T_TRUE), false);
				CONFIG_SET(config, item, "vsync", gConfig.vsync, (TYPE(item) == T_TRUE), false);
				CONFIG_SET(config, item, "maximizedWindow", gConfig.maximized_window, (TYPE(item) == T_TRUE), false);
				CONFIG_SET(config, item, "RAGE::Bitmap", gConfig.use_rageBitmap, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::Music", gConfig.use_rageMusic, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::Sfx", gConfig.use_rageSfx, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::IniFile", gConfig.use_rageIniFile, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::ScreenEvent", gConfig.use_rageScreenEvent, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::KeyEvent", gConfig.use_rageKeyEvent, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::MouseEvent", gConfig.use_rageMouseEvent, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::TimerEvent", gConfig.use_rageTimerEvent, (TYPE(item) == T_TRUE), true);
				CONFIG_SET(config, item, "RAGE::JoyEvent", gConfig.use_rageJoyEvent, (TYPE(item) == T_TRUE), true);
				CONFIG_SET(config, item, "RAGE::VertexArray", gConfig.use_rageVertexArray, (TYPE(item) == T_TRUE), true);
				CONFIG_SET(config, item, "RAGE::Shader", gConfig.use_rageShader, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::Font", gConfig.use_rageFont, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::Color", gConfig.use_rageColor, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::Joystick", gConfig.use_rageJoystick, (TYPE(item) == T_TRUE), true);
				CONFIG_SET(config, item, "RAGE::Events", gConfig.use_rageEvents, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::FS", gConfig.use_rageFS, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::Draw", gConfig.use_rageDraw, (TYPE(item) == T_TRUE), true);
			    CONFIG_SET(config, item, "RAGE::Input", gConfig.use_rageInput, (TYPE(item) == T_TRUE), true);
				CONFIG_SET(config, item, "DL", gConfig.use_rageRubyDL, (TYPE(item) == T_TRUE), true);
				CONFIG_SET(config, item, "Zlib", gConfig.use_rageRubyZlib, (TYPE(item) == T_TRUE), true);

				configured = true;

				item = rb_hash_aref(config, rb_str_new2("version"));

				if (TYPE(item) != T_NIL)
				{
					if (strcmp(StringValueCStr(item), RAGE_ENGINE_VERSION) != 0)
						PRINT(RAGE_RB_INCOMPATIBLE);
				}

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
			if (strcmp(filename, "boot.rb") == 0) 
				PRINT(RAGE_DEV_END_TEXT);
			#endif
		}

		int Ruby::file_exists(VALUE filename)
		{

			if (RAGE::Filesystem::FSWrappers::is_physfs_on())
			{
				if (PHYSFS_exists(StringValueCStr(filename)))
					return 2;
				else
					return -2;
			}

			/* Check Ruby search path */
			VALUE fname = rb_find_file(filename);

			rb_gc_register_address(&fname);

			if (TYPE(fname) != T_STRING)
				return -1;
			else
				return 1;
		}

		char* Ruby::get_file_path(VALUE filename)
		{

			if (RAGE::Filesystem::FSWrappers::is_physfs_on())
			{
				if (PHYSFS_exists(StringValueCStr(filename)))
					return StringValueCStr(filename);
				else
					return NULL;
			}

			/* Check Ruby search path */
			VALUE fname = rb_find_file(filename);

			rb_gc_register_address(&fname);

			if (TYPE(fname) != T_STRING)
				return NULL;
			else
				return StringValueCStr(fname);
		}

		Ruby::Ruby(int argc, char** argv)
		{
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

				if (!PHYSFS_mount(str.c_str(), "/", 0))
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
				if (al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_CONF_SCRIPT).c_str()))
				{
					if (RAGE::Filesystem::FSWrappers::is_physfs_on())
						rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_CONF_SCRIPT));
					else
						load_protect(RAGE_CONF_SCRIPT);
				}
				
				if (!configured)
					set_default_config();

				/* Initialize ruby extensions */				
				if (gConfig.use_rageRubyZlib) Init_zlib();

				if (gConfig.use_rageRubyDL)
				{
					Init_dl();
					load_extension_rb_data();
				}

				/* Load RAGE modules */
				RAGE::Graphics::GraphicsWrappers::load_wrappers();

				if (gConfig.use_rageEvents) RAGE::Events::EventsWrapper::load_wrappers();
				if (gConfig.use_rageInput) RAGE::Input::InputWrappers::load_wrappers();
				RAGE::Audio::AudioWrappers::load_wrappers();
				RAGE::Graphics::DrawWrappers::load_wrappers();
				if (gConfig.use_rageFS) RAGE::Filesystem::FSWrappers::load_wrappers();

				/* Load RAGE classes */
				if (gConfig.use_rageBitmap) RAGE::Graphics::BitmapWrapper::load_ruby_class();
				if (gConfig.use_rageFont) RAGE::Graphics::FontWrapper::load_ruby_class();
				if (gConfig.use_rageColor) RAGE::Graphics::ColorWrapper::load_ruby_class();
				if (gConfig.use_rageShader) RAGE::Graphics::ShaderWrapper::load_ruby_class();
				if (gConfig.use_rageMusic) RAGE::Audio::MusicWrapper::load_ruby_class();
				if (gConfig.use_rageSfx) RAGE::Audio::SfxWrapper::load_ruby_class();

				if (gConfig.use_rageTimerEvent || gConfig.use_rageJoyEvent || gConfig.use_rageKeyEvent || 
					gConfig.use_rageMouseEvent || gConfig.use_rageScreenEvent) 
						RAGE::Events::EventWrapper::load_ruby_class();

				if (gConfig.use_rageTimerEvent) RAGE::Events::TimerEventWrapper::load_ruby_class();
				if (gConfig.use_rageJoyEvent) RAGE::Events::JoyEventWrapper::load_ruby_class();
				if (gConfig.use_rageKeyEvent) RAGE::Events::KeyboardEventWrapper::load_ruby_class();
				if (gConfig.use_rageMouseEvent) RAGE::Events::MouseEventWrapper::load_ruby_class();
				if (gConfig.use_rageScreenEvent) RAGE::Events::ScreenEventWrapper::load_ruby_class();
				if (gConfig.use_rageIniFile) RAGE::Filesystem::IniFileWrapper::load_ruby_class();
				if (gConfig.use_rageJoystick) RAGE::Input::JoystickWrapper::load_ruby_class();
				if (gConfig.use_rageVertexArray) RAGE::Graphics::VertexArrayWrapper::load_ruby_class();

				/* Perform additional tasks */
				if (gConfig.use_rageEvents) RAGE::Events::EventsWrapper::init_queue();
				if (gConfig.use_rageMusic || gConfig.use_rageSfx) RAGE::Audio::AudioWrappers::init_audio();

				RAGE::Graphics::GraphicsWrappers::initialize_graphics(gConfig);
				
				if (gConfig.use_rageDraw) RAGE::Graphics::DrawWrappers::init();
				if (gConfig.use_rageEvents) RAGE::Events::EventsWrapper::run_event_thread();

				/* Particle Engine Loading - Needs fixing */
				RAGE::Graphics::ParticleEngineWrapper::load_ruby_class();
				RAGE::Logic::LogicWrappers::load_wrappers();

				/* Load boot script */
				if (al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_BOOT_SCRIPT).c_str()))
				{
					if (RAGE::Filesystem::FSWrappers::is_physfs_on())
						rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_BOOT_SCRIPT));
					else
						load_protect(RAGE_BOOT_SCRIPT);
				}
				#ifdef DEVELOPMENT_VERSION
				else
				{
					#ifdef WIN32
					MessageBox(al_get_win_window_handle(RAGE::Graphics::GraphicsWrappers::get_display()), RAGE_DEV_MESSAGE, L"RAGE Game Engine", MB_OK | MB_ICONINFORMATION);
					#else
					PRINT(RAGE_DEV_MESSAGE);
					#endif
					PRINT(RAGE_DEV_MESSAGE_EXIT);
					getc(stdin);
					
				}
				#endif
			}
		}


		Ruby::~Ruby(void)
		{
			/* Close Ruby subsystem */
			ruby_finalize();
		}
	};
};