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

	// TODO: RAGE::Network module
    //	     RAGE::Physics (Box2D) module

	// FIXME: Events_Wrapper - RAGE::JoyEvent class.
	//        RAGE::Graphics - display driver informations.
	//        RAGE::Input - (3) needs finishing, joystick testing, joystick enumeration.

	// LATER: RM versions? Or adjust scripts towards RAGE?

	/*  Init PHYS_FS */
	PHYSFS_init(argv[0]);

	/* Initialize and start Interpreter */
	RAGE::Interpreter::Ruby ri(argc, argv);

	/* Destroy event queue */
	RAGE::Events::EventsWrapper::finalize_queue();

	PHYSFS_deinit();

	/* Close down allegro game system */
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_joystick();
	al_uninstall_audio();
	al_uninstall_system();

	return 0;
}

