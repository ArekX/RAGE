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
	al_install_mouse();
    al_install_keyboard();
	al_install_joystick();
	al_install_audio();
	al_init_acodec_addon();

	/* Initialize events */
	RAGE::Events::EventsWrapper::init_queue();

	/* Initialize graphics */
	RAGE::Graphics::GraphicsConfig g;
	g.width = 800;
	g.height = 600;
	g.fullscreen = false;
	RAGE::Graphics::Graphics vg(g);

	/* Initialize and start Interpreter */
	RAGE::Interpreter::Ruby ri(argc, argv);

	/* Destroy event queue */
	RAGE::Events::EventsWrapper::finalize_queue();

	/* Uninstall input */
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_joystick();

	/* Close down allegro game system */
	al_uninstall_system();

	return 0;
}