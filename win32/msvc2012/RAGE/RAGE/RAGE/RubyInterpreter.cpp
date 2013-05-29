#include "RubyInterpreter.h"

#define RAGE_ENGINE_VERSION "0.0.1-alpha"


namespace RAGE
{
	namespace Interpreter
	{
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

		Ruby::Ruby(int argc, char** argv)
		{
			int error;

			/* Initialize Ruby Interpreter */
			ruby_sysinit(&argc, &argv);
			{
				RUBY_INIT_STACK;
				ruby_init();
				
				/* Define Global Functions */
				VALUE rage = rb_define_module("RAGE");
				rb_define_module_function(rage, "getEnvVar", RFUNC(rb_get_env), 1);
				rb_define_module_function(rage, "about", RFUNC(rb_rage_about), 0);

				/* Load RAGE modules */
				RAGE::Graphics::GraphicsWrappers::load_wrappers();
				RAGE::Events::EventsWrapper::load_wrappers();
				RAGE::Input::InputWrappers::load_wrappers();
				RAGE::Audio::AudioWrappers::load_wrappers();
				RAGE::Graphics::DrawWrappers::load_wrappers();

				/* Load RAGE classes */
				RAGE::Graphics::BitmapWrapper::load_ruby_class();
				RAGE::Audio::MusicWrapper::load_ruby_class();
				RAGE::Audio::SfxWrapper::load_ruby_class();
				RAGE::Events::EventWrapper::load_ruby_class();
				RAGE::Events::TimerEventWrapper::load_ruby_class();
				RAGE::Events::KeyboardEventWrapper::load_ruby_class();
				RAGE::Events::MouseEventWrapper::load_ruby_class();
				RAGE::Events::ScreenEventWrapper::load_ruby_class();

				// TODO: Finish inserting wrappers here

				/// DEV
				RAGE::Graphics::GraphicsConfig g;
				g.width = 800;
				g.height = 600;
				g.fullscreen = false;
				g.vsync = false;

				/* Perform additional tasks */
				RAGE::Events::EventsWrapper::init_queue();
				RAGE::Audio::AudioWrappers::init_audio();
				RAGE::Graphics::GraphicsWrappers::initialize_graphics(g);
				RAGE::Events::EventsWrapper::run_event_thread();

				/* Set search path to exe file */
				std::string str(*argv);
				rb_ary_push(rb_gv_get("$:"), rb_str_new_cstr(str.substr(0, str.find_last_of(DS) + 1).c_str()));

				/* Set Command line arguments */
				rb_gv_set("$RARGV", rb_ary_new());
				for (int i = 0; i < argc; i++)
					rb_ary_push(rb_gv_get("$RARGV"), rb_str_new_cstr(argv[i]));
				
				#ifdef DEVELOPMENT_VERSION
				
				/* Set debug version vars: */
				rb_gv_set("$DEBUG", Qtrue);

				printf("You are using Development Version of RAGE.\nFor distribution please use Production Version of RAGE.\n\n");
				
				#endif
				
				/* Load boot script */
				VALUE bootfile = rb_str_new_cstr("boot.rb");
				ruby_set_script_name(bootfile);
				rb_load_protect(bootfile, 1, &error);


				/* In case of error show it - do not exit the application */
				if (error)
				{
						VALUE lasterr = rb_obj_as_string(rb_gv_get("$!"));
						VALUE klass = rb_class_path(CLASS_OF(rb_gv_get("$!")));
					
						printf_s("Script Error!\n\t%s: %s\n", StringValueCStr(klass), StringValueCStr(lasterr));
						getc(stdin);
				}

			}
		}


		Ruby::~Ruby(void)
		{
			/* Close Ruby subsystem */
			ruby_finalize();
		}
	};
};