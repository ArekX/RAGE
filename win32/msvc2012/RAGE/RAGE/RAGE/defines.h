#define ALLEGRO_STATICLINK

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

#define RFUNC RUBY_METHOD_FUNC
#define RAGE_CHECK_DISPOSED(disposed_var) if (disposed_var) { rb_raise(rb_eException, "Cannot call methods of disposed objects."); return; }
#define RAGE_CHECK_DISPOSED_RET(disposed_var, ret) if (disposed_var) { rb_raise(rb_eException, "Cannot call methods of disposed objects."); return ret; }

#ifdef WIN32
#define DS '\\'
#define PRINTF(format, data) printf_s(format, data)
#define PRINT(data) printf_s(data)
#else
#define PRINTF(format, data) printf(format, data)
#define PRINT(data) printf(data)
#endif

/* Errors */
#include "rage_errors.h"

#define RAGE_CONF_SCRIPT "conf.rb"
#define RAGE_BOOT_SCRIPT "boot.rb"
#define RAGE_GAME_FILE "game.rage"

#define RAGE_MOUSE_BITMAP_CURSOR_INDEX -1

#define RAGE_REGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_FALSE) { if (rb_class_of(proc) != rb_cProc) rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); else rb_ary_push(observer, proc);}
#define RAGE_UNREGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_TRUE) { if (rb_class_of(proc) != rb_cProc) rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); else rb_ary_delete(observer, proc);}
#define CONFIG_SET(sconfig, sitem, scstr, sset, sval, sdefval) item = rb_hash_aref(sconfig, rb_str_new2(scstr)); if (TYPE(sitem) != T_NIL) { sset = sval; } else { sset = sdefval; }

#define RAGE_ENGINE_VERSION "0.0.3-beta"

#define RAGE_DEBUG_GLOBAL_VAR "$DEBUG"
#define RAGE_ARGS_VAR "$RARGV"

#define RAGE_DEV_END_TEXT "Your game has ended. Interpreter returned -> %d\n\n", error
#define RAGE_DEV_MESSAGE L"Welcome to RAGE - Ruby Awesome Game Engine. To start making games you need a file called boot.rb which needs to be in the same folder as this executable.\n\nIf you need to make an initial configuration for your game you need another file called conf.rb in the same folder as this executable. To learn more about game making process, please refer to the developer documentation which should come together as this executable.\n\nHave fun using RAGE!"
#define RAGE_DEV_MESSAGE_EXIT "\n\nPress any key to close this engine."
#define RAGE_DEV_TEXT "You are using Development Version of RAGE.\nFor distribution please use Production Version of RAGE.\n\n"