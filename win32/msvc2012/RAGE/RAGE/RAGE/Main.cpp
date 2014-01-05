/*
Copyright (c) 2013 Aleksandar Panic

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#include "rage_standard_headers.h"
#include "RubyInterpreter.h"

#ifdef WIN32
	#ifdef DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#include <stdlib.h>
	#endif
#endif

void sigsegv_handler(int param)
{	
	#ifdef DEBUG
	PRINT(RAGE_FATAL_ERROR_SIGSEGV_DEBUG);
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
	_CrtDumpMemoryLeaks();
	#else
	PRINT(RAGE_FATAL_ERROR_SIGSEGV);
	getc(stdin);
	exit(EXIT_FAILURE);
	#endif
}

/**
 * Main Initialize Function
 * Arguments:
 * argc, argv
**/
int main(int argc, char** argv)
{
	#ifdef WIN32
		#ifdef DEBUG
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
		#endif
	#endif

	// Removing Ruby VM debugger output when error happens.
	signal(SIGSEGV, sigsegv_handler);

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
	al_init_acodec_addon();// Vidi da li da ubacis conditional compile na ovo?

	#ifdef DEVELOPMENT_VERSION
        #ifdef WIN32
        SetConsoleTitle(RAGE_DEV_CONSOLE_NAME_W);
        #else
        printf("%c]0;%s%c", '\033', RAGE_DEV_CONSOLE_NAME_L, '\007');
        #endif
	#endif

	/*  Init PHYS_FS */
	PHYSFS_init(argv[0]);

	/* Initialize and start Interpreter */
	RAGE::Interpreter::Ruby ri(argc, argv);

	PHYSFS_deinit();

	/* Close down allegro game system */
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_joystick();
	al_uninstall_audio();
	al_uninstall_system();
	
	#ifdef WIN32
		#ifdef DEBUG
		_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
		_CrtDumpMemoryLeaks();
		#endif
	#endif

	return 0;
}

