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
		std::vector<std::string*> *loaded_files;
		RAGEConfiguration *gConfig;

		static void load_extension_rb_data()
		{
			int error = 0;

			rb_eval_string_protect(ruby_dl_extension_rb_data, &error);
			if (error) PRINT(RAGE_ERROR_DL_EXT_RB_DATA_FAILED);
		}

		static VALUE rb_rage_about(VALUE self)
		{
			PRINT("RAGE Engine\nFull Name: Ruby Awesome Game Engine\nVersion: %s\nCopyright (c) Panic Aleksandar\n\n", RAGE_ENGINE_VERSION);
			PRINT("[Ruby Interpreter]\n");
			ruby_show_version();
			PRINT("Copyright (c) Yukihiro Matsumoto (a.k.a matz)\n\n");
			PRINTF("[Allegro Game Library]\nAllegro Game Library Version: %s\nCopyright (c) Allegro Development Team\n\n", ALLEGRO_VERSION_STR);
			return Qnil;
		}

		static void set_default_config()
		{
			gConfig = new RAGEConfiguration(NULL);
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

			if (RAGE::Filesystem::FSWrappers::is_physfs_on())
			{
				if (PHYSFS_exists(StringValueCStr(filename)))
					return 2;
				else
					return -2;
			}

			/* Check Ruby search path */
			VALUE fname = rb_find_file(filename);

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
				if (!RAGE::Filesystem::FSWrappers::is_physfs_on() && al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_CONF_SCRIPT).c_str()))
					load_protect(RAGE_CONF_SCRIPT);
				else if (RAGE::Filesystem::FSWrappers::is_physfs_on() && PHYSFS_exists(RAGE_CONF_SCRIPT))
					rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_CONF_SCRIPT));

				if (!configured)
					set_default_config();

				/* Initialize ruby extensions */				
				if (gConfig->is_on("Zlib")) Init_zlib();

				if (gConfig->is_on("DL"))
				{
					Init_dl();
					load_extension_rb_data();
				}

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
				RAGE::Graphics::ShaderWrapper::load_ruby_class();
				RAGE::Audio::MusicWrapper::load_ruby_class();
				RAGE::Audio::SfxWrapper::load_ruby_class();

				RAGE::Events::EventWrapper::load_ruby_class();

				RAGE::Events::TimerEventWrapper::load_ruby_class();
				RAGE::Events::JoyEventWrapper::load_ruby_class();
				RAGE::Events::KeyboardEventWrapper::load_ruby_class();
				RAGE::Events::MouseEventWrapper::load_ruby_class();
				RAGE::Events::ScreenEventWrapper::load_ruby_class();
				RAGE::Filesystem::IniFileWrapper::load_ruby_class();
				RAGE::Filesystem::FileWrapper::load_ruby_class();
				RAGE::Input::JoystickWrapper::load_ruby_class();
				RAGE::Graphics::VertexArrayWrapper::load_ruby_class();
				RAGE::Network::TCPSocketWrapper::load_ruby_class();

				/* Perform additional tasks */
				RAGE::Events::EventsWrapper::init_queue();
				RAGE::Audio::AudioWrappers::init_audio();

				RAGE::Graphics::GraphicsWrappers::initialize_graphics();
				
				RAGE::Graphics::DrawWrappers::init();
				RAGE::Events::EventsWrapper::run_event_thread();

				/* Particle Engine Loading - Needs fixing */
				RAGE::Graphics::ParticleEngineWrapper::load_ruby_class();
				RAGE::Logic::LogicWrappers::load_wrappers();

				/* Load boot script */
				if (!RAGE::Filesystem::FSWrappers::is_physfs_on() && al_filename_exists(str.substr(0, str.find_last_of(DS) + 1).append(RAGE_BOOT_SCRIPT).c_str()))
					load_protect(RAGE_BOOT_SCRIPT);
				else if (RAGE::Filesystem::FSWrappers::is_physfs_on() && PHYSFS_exists(RAGE_BOOT_SCRIPT))
					rb_rage_require_wrapper(NULL, rb_str_new_cstr(RAGE_BOOT_SCRIPT));

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
			for (int i = 0; i < loaded_files->size(); i++)
				delete loaded_files->at(i);

			delete loaded_files;

			delete gConfig;

			/* Close Ruby subsystem */
			ruby_finalize();
		}
	};
};