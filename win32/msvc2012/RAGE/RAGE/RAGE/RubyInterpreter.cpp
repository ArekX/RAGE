#include "RubyInterpreter.h"


namespace RAGE
{
	namespace Interpreter
	{
		static VALUE rb_draw_text(VALUE self, VALUE text)
		{
			
			ALLEGRO_FONT* f = al_load_ttf_font("c:/other/acmesa.TTF", 16, 0);
			ALLEGRO_USTR* u = al_ustr_new(StringValueCStr(text));
			al_draw_ustr(f, al_map_rgb(255,255, 255), 10, 10, 0, u);
			al_flip_display();
	
			return Qnil;
		}

		VALUE Ruby::rb_require_protect(VALUE filename)
		{
			return rb_require(StringValueCStr(filename));
		}

		Ruby::Ruby(int argc, char** argv)
		{
			int error;

			/* Initialize Ruby Interpreter */
			ruby_sysinit(&argc, &argv);
			{
				RUBY_INIT_STACK;
				ruby_init();

				VALUE protected_objects = rb_hash_new();
				rb_gc_register_address(&protected_objects);
		
				/* Define Functions */
				rb_define_global_function("drawText", RFUNC(rb_draw_text), 1);
				
				/* Load all function wrappers */
				RAGE::Graphics::Graphics_Wrappers::LoadWrappers();
				RAGE::Graphics::BitmapWrapper::LoadRubyClass();
				// TODO: Finish inserting wrappers here

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
					
					getchar();
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