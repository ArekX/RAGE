#include <iostream>
#include "RubyInterpreter.h"

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

	

	#ifdef DEVELOPMENT_VERSION
	SetConsoleTitle(L"RAGE Development Console");
	#endif

	/* FIXME: INI or ruby function loading of configuration? */

	// TODO: RAGE::Network module, 
	//       RAGE::FS (PhysicsFS) module, 
    //	     RAGE::Physics (Box2D) module,
	//       RAGE::Draw module, needs some work done but almost ready for first beta.
	//       RAGE::Font class, you create it and then set it to RAGE::Draw class - easier multiple font settings.
	//       RAGE::Color class - Do it nao!

	// FIXME: Events_Wrapper - RAGE::JoyEvent classes all extending RAGE::Event class
	//        RAGE::Graphics - (2) add color conversion routines, display driver informations.
	//        RAGE::Input - (3) needs finishing, joystick testing, joystick enumeration.
	//
	// NOTE: All event classes need method testing.

	// LATER: RM versions? Or adjust scripts towards RAGE?

	/* Initialize and start Interpreter */
	RAGE::Interpreter::Ruby ri(argc, argv);

	/* Destroy event queue */
	RAGE::Events::EventsWrapper::finalize_queue();

	/* Close down allegro game system */
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_joystick();
	al_uninstall_audio();
	al_uninstall_system();

	return 0;
}

