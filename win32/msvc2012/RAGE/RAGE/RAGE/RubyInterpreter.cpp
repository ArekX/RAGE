#include "RubyInterpreter.h"

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
		RAGE::Graphics::GraphicsConfig gConfig;

		static VALUE rb_rage_about(VALUE self)
		{
			PRINTF("RAGE Engine\nFull Name: Ruby Awesome Game Engine\nVersion: %s\nCopyright (c) Panic Aleksandar\n\n", RAGE_ENGINE_VERSION);
			PRINT("[Ruby Interpreter]\n");
			ruby_show_version();
			PRINT("Copyright (c) Yukihiro Matsumoto (a.k.a matz)\n\n");
			PRINTF("[Allegro Game Library]\nAllegro Game Library Version: %s\nCopyright (c) Allegro Development Team\n\n", ALLEGRO_VERSION_STR);
			return Qnil;
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
			
			if (error)
			{
					VALUE lasterr = rb_obj_as_string(rb_gv_get("$!"));
					VALUE klass = rb_class_path(CLASS_OF(rb_gv_get("$!")));
					
					PRINT(RAGE_RB_SCRIPT_ERROR, StringValueCStr(klass), StringValueCStr(lasterr));
					getc(stdin);
					exit(0);
			}

			return Qnil;
		}

		static VALUE rb_rage_configure(VALUE self, VALUE name, VALUE version, VALUE width, VALUE height, VALUE fullscreen, VALUE vsync)
		{
			if (!configured)
			{
				
				gConfig.name = StringValueCStr(name);

				gConfig.width = FIX2UINT(width);
				gConfig.height = FIX2UINT(height);
				gConfig.fullscreen = (TYPE(fullscreen) == T_TRUE);
				gConfig.vsync = (TYPE(vsync) == T_TRUE);
				configured = true;

				if (strcmp(StringValueCStr(version), RAGE_ENGINE_VERSION) != 0)
					PRINT(RAGE_RB_INCOMPATIBLE);

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
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, filename);
				getc(stdin);
				return;
			}

			ruby_set_script_name(fstring);
			int error = 0;

			rb_load_protect(full_file, 1, &error);

			if (error)
			{
					VALUE lasterr = rb_obj_as_string(rb_gv_get("$!"));
					VALUE klass = rb_class_path(CLASS_OF(rb_gv_get("$!")));
					
					PRINT(RAGE_RB_SCRIPT_ERROR, StringValueCStr(klass), StringValueCStr(lasterr));
					getc(stdin);
					exit(0);
			}
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

				/* Initialize ruby extensions */
				Init_dl();
				Init_zlib();

				/* Define Global Functions */
				VALUE rage = rb_define_module("RAGE");
				rb_define_module_function(rage, "require", RFUNC(rb_rage_require_wrapper), 1);
				rb_define_module_function(rage, "about", RFUNC(rb_rage_about), 0);
				rb_define_module_function(rage, "configure", RFUNC(rb_rage_configure), 6);

				/* Load RAGE modules */
				RAGE::Graphics::GraphicsWrappers::load_wrappers();
				RAGE::Events::EventsWrapper::load_wrappers();
				RAGE::Input::InputWrappers::load_wrappers();
				RAGE::Audio::AudioWrappers::load_wrappers();
				RAGE::Graphics::DrawWrappers::load_wrappers();
				RAGE::Filesystem::FSWrappers::load_wrappers();

				/* Load RAGE classes */
				RAGE::Graphics::BitmapWrapper::load_ruby_class();
				RAGE::Graphics::FontWrapper::load_ruby_class();
				RAGE::Graphics::ColorWrapper::load_ruby_class();
				RAGE::Audio::MusicWrapper::load_ruby_class();
				RAGE::Audio::SfxWrapper::load_ruby_class();
				RAGE::Events::EventWrapper::load_ruby_class();
				RAGE::Events::TimerEventWrapper::load_ruby_class();
				RAGE::Events::KeyboardEventWrapper::load_ruby_class();
				RAGE::Events::MouseEventWrapper::load_ruby_class();
				RAGE::Events::ScreenEventWrapper::load_ruby_class();
				RAGE::Filesystem::IniFileWrapper::load_ruby_class();

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
				if (RAGE::Filesystem::FSWrappers::is_physfs_on())
					rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_CONF_SCRIPT));
				else
					load_protect(RAGE_CONF_SCRIPT);
				
				/* Perform additional tasks */
				RAGE::Events::EventsWrapper::init_queue();
				RAGE::Audio::AudioWrappers::init_audio();
				RAGE::Graphics::GraphicsWrappers::initialize_graphics(gConfig);
				RAGE::Graphics::DrawWrappers::init();
				RAGE::Events::EventsWrapper::run_event_thread();

				/* Load boot script */
				if (RAGE::Filesystem::FSWrappers::is_physfs_on())
					rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_BOOT_SCRIPT));
				else
					load_protect(RAGE_BOOT_SCRIPT);
			}
		}


		Ruby::~Ruby(void)
		{
			/* Close Ruby subsystem */
			ruby_finalize();
		}
	};
};