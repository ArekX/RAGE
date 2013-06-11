#include "RubyInterpreter.h"


namespace RAGE
{
	namespace Interpreter
	{
		bool configured = false;
		RAGE::Graphics::GraphicsConfig gConfig;

		static VALUE rb_get_env(VALUE self, VALUE text)
		{
			#ifdef WIN32
			char *env[1024];
			size_t t = 1024;
			_dupenv_s(env, &t, StringValueCStr(text));
			return rb_str_new_cstr(env[0]);
			#else
			return rb_str_new_cstr(getenv(StringValueCStr(text)));
			#endif
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

		static VALUE rb_rage_require_wrapper(VALUE self, VALUE filename)
		{
			VALUE fname = rb_find_file(filename);

			// TODO: This will need revision when PhysicsFS comes, to check both in allegro and ruby path. 
			// -- Refactor this check-and-find into a function.

			if (TYPE(fname) != T_STRING)
			{
				
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}

			ALLEGRO_FILE *afile = al_fopen(StringValueCStr(fname), "rb");
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
					
					printf_s(RAGE_RB_SCRIPT_ERROR, StringValueCStr(klass), StringValueCStr(lasterr));
					getc(stdin);
			}

			return Qnil;
		}

		static VALUE rb_rage_configure(VALUE self, VALUE name, VALUE version, VALUE width, VALUE height, VALUE fullscreen, VALUE vsync)
		{
			if (!configured)
			{
				gConfig.name = StringValueCStr(name);
				gConfig.version = StringValueCStr(version);
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

		static void load_protect(char* filename)
		{
			VALUE str = rb_str_new_cstr(filename);
			ruby_set_script_name(str);
			int error;

			// TODO: This will need revision when PhysicsFS comes, to check both in allegro and ruby path. 
			// -- Refactor this check-and-find into a function.

			rb_gc_register_address(&str);
			rb_load_protect(str, 1, &error);

			if (error)
			{
					VALUE lasterr = rb_obj_as_string(rb_gv_get("$!"));
					VALUE klass = rb_class_path(CLASS_OF(rb_gv_get("$!")));
					
					printf_s(RAGE_RB_SCRIPT_ERROR, StringValueCStr(klass), StringValueCStr(lasterr));
					getc(stdin);

					exit(0);
			}
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
				rb_define_module_function(rage, "getEnvVar", RFUNC(rb_get_env), 1);
				rb_define_module_function(rage, "require", RFUNC(rb_rage_require_wrapper), 1);
				rb_define_module_function(rage, "about", RFUNC(rb_rage_about), 0);
				rb_define_module_function(rage, "configure", RFUNC(rb_rage_configure), 6);

				/* Load RAGE modules */
				RAGE::Graphics::GraphicsWrappers::load_wrappers();
				RAGE::Events::EventsWrapper::load_wrappers();
				RAGE::Input::InputWrappers::load_wrappers();
				RAGE::Audio::AudioWrappers::load_wrappers();
				RAGE::Graphics::DrawWrappers::load_wrappers();

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

				// TODO: Finish inserting wrappers here

				/* Set search path to exe file */
				std::string str(*argv);
				rb_ary_push(rb_gv_get("$:"), rb_str_new_cstr(str.substr(0, str.find_last_of(DS) + 1).c_str()));

				/* Set Command line arguments */
				rb_gv_set("$RARGV", rb_ary_new());
				for (int i = 0; i < argc; i++)
					rb_ary_push(rb_gv_get("$RARGV"), rb_str_new_cstr(argv[i]));
				
				#ifdef DEVELOPMENT_VERSION
				
				/* Set debug vars */
				rb_gv_set("$DEBUG", Qtrue);

				printf(RAGE_DEV_TEXT);
				
				#endif

				/* Load config script */
				load_protect("conf.rb");
				

				/* Perform additional tasks */
				RAGE::Events::EventsWrapper::init_queue();
				RAGE::Audio::AudioWrappers::init_audio();
				RAGE::Graphics::GraphicsWrappers::initialize_graphics(gConfig);
				RAGE::Graphics::DrawWrappers::init();
				RAGE::Events::EventsWrapper::run_event_thread();


				/* Load boot script */
				load_protect("boot.rb");
			}
		}


		Ruby::~Ruby(void)
		{
			/* Close Ruby subsystem */
			ruby_finalize();
		}
	};
};