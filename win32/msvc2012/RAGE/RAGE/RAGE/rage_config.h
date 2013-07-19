
#ifndef OLD_CONFIG
	#if XP_TARGETING
		#define PASAPI_VERSION 1
		#undef K32EnumProcesses
		#undef K32EnumProcessModules
		#undef K32EnumProcessModulesEx
		#undef K32GetModuleBaseNameA
		#undef K32GetModuleBaseNameW
		#undef K32GetModuleFileNameExA
		#undef K32GetModuleFileNameExW
		#undef K32GetModuleInformation
		#undef K32EmptyWorkingSet
		#undef K32QueryWorkingSet
		#undef K32QueryWorkingSetEx
		#undef K32InitializeProcessForWsWatch
		#undef K32GetWsChanges
		#undef K32GetWsChangesEx
		#undef K32GetMappedFileNameW
		#undef K32GetMappedFileNameA
		#undef K32EnumDeviceDrivers
		#undef K32GetDeviceDriverBaseNameA
		#undef K32GetDeviceDriverBaseNameW
		#undef K32GetDeviceDriverFileNameA
		#undef K32GetDeviceDriverFileNameW
		#undef K32GetProcessMemoryInfo
		#undef K32GetPerformanceInfo
		#undef K32EnumPageFilesW
		#undef K32EnumPageFilesA
		#undef K32GetProcessImageFileNameA
		#undef K32GetProcessImageFileNameW
	#endif

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

#ifdef WIN32
	#include <allegro5/allegro_windows.h>
#endif