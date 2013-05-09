#define ALLEGRO_STATICLINK
#include <iostream>
#include <ruby.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

static VALUE rb_draw_text(VALUE self, VALUE text)
{
	ALLEGRO_FONT* f = al_load_ttf_font("c:/other/acmesa.TTF", 16, 0);
	ALLEGRO_USTR* u = al_ustr_new(StringValueCStr(text));
	al_draw_ustr(f, al_map_rgb(255,255, 255), 10, 10, 0, u);
	al_flip_display();
	return Qnil;
}

#define RFUNC(x) (VALUE(*)(...))x

/**
 * Main Initialize Function
 * Arguments:
 * argc, argv
**/
int main(int argc, char** argv)
{
	/* Initialize Allegro Game Library */
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY* d = al_create_display(640, 480);

	//al_draw_bitmap(b, 0, 0, 0);
	al_flip_display();


	/* Initialize Ruby Interpreter */
	ruby_sysinit(&argc, &argv);
    {
		RUBY_INIT_STACK;
		ruby_init();
		ruby_init_loadpath();

		VALUE protected_objects = rb_hash_new();
		rb_gc_register_address(&protected_objects);
		
		rb_define_global_function("drawText", RFUNC(rb_draw_text), 1);

		rb_eval_string("drawText 'Welcome to Ruby Awesome Game Engine! Written in C++, support to Ruby.'\ngets");
    }

	/* Close down allegro game system */
	al_uninstall_system();

	return 0;
}