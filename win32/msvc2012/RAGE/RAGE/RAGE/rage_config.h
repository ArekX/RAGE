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

#define OLD_CONFIG 1

#ifdef WIN32
#include <allegro5/platform/almsvc.h>
#include <allegro5/allegro_windows.h>
#else
#include <allegro5/platform/alunix.h>
#endif

#ifndef OLD_CONFIG
	#pragma comment(lib, "msvcr110-ruby200-static.lib")
	#pragma comment(lib, "openal-1.14-static-mt.lib")
	#pragma comment(lib, "freetype-2.4.8-static-mt.lib")
	#pragma comment(lib, "libFLAC-1.2.1-static-mt.lib")
	#pragma comment(lib, "libogg-1.2.1-static-mt.lib")
	#pragma comment(lib, "libvorbis-1.3.2-static-mt.lib")
	#pragma comment(lib, "libvorbisfile-1.3.2-static-mt.lib")
	#pragma comment(lib, "zlib-1.2.5-static-mt.lib")
	#pragma comment(lib, "dumb-0.9.3-static-mt.lib")
	
	#if XP_TARGETING
		#define PASAPI_VERSION 1
		#pragma comment(lib, "allegro-5.0.10-monolith-static-mt.lib")
	#else
		#pragma comment(lib, "allegro-5.0.10-monolith-static-mt.lib")
	#endif

#else
	#if _MSC_VER == 1700
		#pragma comment(lib, "msvcr110-ruby200-static.lib")
		#pragma comment(lib, "allegro-5.0.10-monolith-static-mt.lib")
		#pragma comment(lib, "openal-1.14-static-mt.lib")
		#pragma comment(lib, "freetype-2.4.8-static-mt.lib")
		#pragma comment(lib, "libFLAC-1.2.1-static-mt.lib")
		#pragma comment(lib, "libogg-1.2.1-static-mt.lib")
		#pragma comment(lib, "libvorbis-1.3.2-static-mt.lib")
		#pragma comment(lib, "libvorbisfile-1.3.2-static-mt.lib")
		#pragma comment(lib, "zlib-1.2.5-static-mt.lib")
		#pragma comment(lib, "dumb-0.9.3-static-mt.lib")
	#endif

	#if _MSC_VER == 1600
	#define PSAPI_VERSION 1
		#pragma comment(lib, "msvcr100-ruby200-static.lib")
		#pragma comment(lib, "allegro-5.0.10-monolith-static-mt-10.lib")
		#pragma comment(lib, "openal-1.14-static-mt-10.lib")
		#pragma comment(lib, "freetype-2.4.8-static-mt-10.lib")
		#pragma comment(lib, "libFLAC-1.2.1-static-mt-10.lib")
		#pragma comment(lib, "libogg-1.2.1-static-mt-10.lib")
		#pragma comment(lib, "libvorbis-1.3.2-static-mt-10.lib")
		#pragma comment(lib, "libvorbisfile-1.3.2-static-mt-10.lib")
		#pragma comment(lib, "zlib-1.2.5-static-mt-10.lib")
		#pragma comment(lib, "dumb-0.9.3-static-mt-10.lib")
	#endif
#endif