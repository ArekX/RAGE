#define ALLEGRO_STATICLINK

#if _MSC_VER == 1700
#pragma comment(lib, "msvcr110-ruby200-static.lib")
#pragma comment(lib, "allegro-5.0.9-monolith-static-mt.lib")
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
#pragma comment(lib, "allegro-5.0.9-monolith-static-mt-10.lib")
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
#define RAGE_RB_PROC_ERROR "You can only pass instances of Proc object as an argument."
#define RAGE_RB_INCOMPATIBLE "This game may be incompatible with this version of RAGE.\n\n"
#define RAGE_RB_SCRIPT_ERROR "Script Error!\n\t%s: %s\n"
#define RAGE_RB_FILE_MISSING_ERROR "File '%s' not found."
#define RAGE_EVENT_ERROR "Cannot call methods from abstract RAGE::Event class."
#define RAGE_BITMAP_ERROR "Width and Height values need to be Fixnum."
#define RAGE_BITMAP_PARENT_ERROR "Parent argument must be an instance of RAGE::Bitmap."
#define RAGE_BITMAP_NOT_CREATED_ERROR "Cannot set nil bitmap as drawing target. Create or load a bitmap first."
#define RAGE_COLOR_ERROR "Argument must be an instance of RAGE::Color class."
#define RAGE_FONT_ERROR "Argument must be an instance of RAGE::Font class."

#define RAGE_REGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_FALSE) { if (rb_class_of(proc) != rb_cProc) rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); else rb_ary_push(observer, proc);}
#define RAGE_UNREGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_TRUE) { if (rb_class_of(proc) != rb_cProc) rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); else rb_ary_delete(observer, proc);}

#define RAGE_SET_BLENDING_OP(check, op, def) switch(FIX2INT(check)) { case RAGE_OP_ADD: op = ALLEGRO_ADD; break; case RAGE_OP_SRC_MIN_DST: op = ALLEGRO_SRC_MINUS_DEST; break; case RAGE_OP_DST_MIN_SRC: op = ALLEGRO_DEST_MINUS_SRC; break; default: op = def;}
#define RAGE_SET_BLENDING(check, set, def) switch(FIX2INT(check)) {case RAGE_BLEND_ZERO:set = ALLEGRO_ZERO;break;case RAGE_BLEND_ONE:src = ALLEGRO_ONE;break;case RAGE_BLEND_ALPHA:set = ALLEGRO_ALPHA;break;case RAGE_BLEND_INV_ALPHA: set = ALLEGRO_INVERSE_ALPHA; break;default:set = def;}

#define RAGE_ENGINE_VERSION "0.0.1-beta"

#define RAGE_DEV_TEXT "You are using Development Version of RAGE.\nFor distribution please use Production Version of RAGE.\n\n"