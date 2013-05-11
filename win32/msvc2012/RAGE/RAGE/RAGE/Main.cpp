#define ALLEGRO_STATICLINK
#include <iostream>
#include "RubyInterpreter.h"
#include "Graphics.h"

using namespace std;

static VALUE eval_wrap(VALUE arg) {
	return rb_funcall(rb_cObject, rb_intern("eval"), 1, arg);
}

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

	/* Initialize graphics */
	RAGE::Graphics::GraphicsConfig g;
	g.width = 800;
	g.height = 600;
	g.fullscreen = false;
	RAGE::Graphics::Graphics vg(g);

	/* Initialize and start Interpreter */
	RAGE::Interpreter::Ruby ri(argc, argv);

	/* Close down allegro game system */
	al_uninstall_system();

	return 0;
}