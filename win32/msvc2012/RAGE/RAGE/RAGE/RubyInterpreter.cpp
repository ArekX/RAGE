#include "RubyInterpreter.h"

#define RAGE_ENGINE_VERSION "0.0.1-alpha"


namespace RAGE
{
	namespace Interpreter
	{

			
		static VALUE rb_draw_text(VALUE self, VALUE text)
		{
			
			ALLEGRO_FONT* f = al_load_ttf_font("c:/other/acmesa.ttf", 16, 0);
			ALLEGRO_USTR* u = al_ustr_new(StringValueCStr(text));
			al_draw_ustr(f, al_map_rgb(255,255, 255), 10, 10, 0, u);
			al_flip_display();
	
			return Qnil;
		}

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
			PRINTF("RAGE Engine\nFull Name: Ruby Awesome Game Engine\nVersion: %s\nRuby Version: ", RAGE_ENGINE_VERSION);
			ruby_show_version();
			PRINTF("Allegro Game Library Version: %s\n\n", ALLEGRO_VERSION_STR);
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
				rb_define_global_function("drawText", RFUNC(rb_draw_text), 1);
				rb_define_module_function(rage, "getEnvVar", RFUNC(rb_get_env), 1);
				rb_define_module_function(rage, "about", RFUNC(rb_rage_about), 0);

				/* Load all function wrappers */
				RAGE::Graphics::Graphics_Wrappers::load_wrappers();
				RAGE::Graphics::BitmapWrapper::load_ruby_class();
				RAGE::Events::EventsWrapper::load_wrappers();
				// TODO: Finish inserting wrappers here

				/* Perform additional tasks */
				RAGE::Events::EventsWrapper::create_threads();

				/* Set search path to exe file */
				std::string str(*argv);
				rb_ary_push(rb_gv_get("$:"), rb_str_new_cstr(str.substr(0, str.find_last_of(DS) + 1).c_str()));

				/* Set RAGE Args */
				rb_gv_set("$RARGV", rb_ary_new());
				for (int i = 0; i < argc; i++)
					rb_ary_push(rb_gv_get("$RARGV"), rb_str_new_cstr(argv[i]));
				
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