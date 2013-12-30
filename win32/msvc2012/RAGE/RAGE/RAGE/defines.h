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

#define ALLEGRO_STATICLINK

#define RFUNC RUBY_METHOD_FUNC
#define RAGE_CHECK_DISPOSED(disposed_var) if (disposed_var) { rb_raise(rb_eException, RAGE_ERROR_DISPOSED_OBJECT); return; }
#define RAGE_CHECK_DISPOSED_RET(disposed_var, ret) if (disposed_var) { rb_raise(rb_eException, RAGE_ERROR_DISPOSED_OBJECT); return ret; }
#define RAGE_DESTROY_PTR(ptr, type) delete ptr; *((type*)ptr) = nullptr

#ifdef WIN32
#define DS '\\'
#define PRINT(data) printf_s(data)
#define PRINTF(data, arg) printf_s(data, arg)
#else
#define PRINT(data) printf(data)
#define PRINTF(data, arg) printf(data, arg)
#define DS '/'
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
#define RDEF_KEY(name, keycode) rb_define_const(input, name, INT2FIX(keycode));

#define RAGE_ENGINE_VERSION "1.0.0"
#define RAGE_DEV_CONSOLE_NAME_W L"RAGE Development Console"
#define RAGE_DEV_CONSOLE_NAME_L "RAGE Development Console"
#define RAGE_ENGINE_CODE_NAME "Flame"

#define RAGE_DEBUG_GLOBAL_VAR "$DEBUG"
#define RAGE_ARGS_VAR "$RARGV"

#define RAGE_GET_DATA(valueVar, asType, asVar) asType *asVar; Data_Get_Struct(valueVar, asType, asVar); 

#define RAGE_IS_CLASS_OF(var, klass) (rb_class_of(var) == klass::get_ruby_class())
#define RAGE_IS_SUPERCLASS_OF(var, klass) (rb_class_get_superclass(rb_class_of(var)) == klass::get_ruby_class())

#define RAGE_DEV_END_TEXT "Your game has ended. Interpreter returned -> %d\n\n", error
#define RAGE_DEV_MESSAGE_W L"Welcome to RAGE - Ruby Awesome Game Engine. To start making games you need a file called boot.rb which needs to be in the same folder as this executable.\n\nIf you need to make an initial configuration for your game you need another file called conf.rb in the same folder as this executable. To learn more about game making process, please refer to the developer documentation which should come together as this executable.\n\nHave fun using RAGE!"
#define RAGE_DEV_MESSAGE_L "Welcome to RAGE - Ruby Awesome Game Engine. To start making games you need a file called boot.rb which needs to be in the same folder as this executable.\n\nIf you need to make an initial configuration for your game you need another file called conf.rb in the same folder as this executable. To learn more about game making process, please refer to the developer documentation which should come together as this executable.\n\nHave fun using RAGE!"
#define RAGE_DEV_MESSAGE_EXIT "\n\nPress any key to close this engine."
#define RAGE_DEV_TEXT "You are using Development Version of RAGE.\nFor distribution please use Production Version of RAGE.\n\n"

/* Socket Defines */
#define RUBY_HASH_PASSTHROUGH rb_str_new2("passthrough")
#define SOCKET_POST_EQUALS "="
#define SOCKET_HTTP_REQ_END "\r\n\r\n"
#define SOCKET_POST_AND "&"
#define SOCKET_PORT_HTTP "http"
#define SOCKET_HTTP_STRIP "http://"
#define SOCKET_PORT_SEPARATOR ":"
#define SOCKET_URI_SEPARATOR "/"
#define SOCKET_HEADERS_GET "GET "
#define SOCKET_HEADERS_POST "POST "
#define SOCKET_HEADERS_1 " HTTP/1.1\r\nHost: "
#define SOCKET_HEADERS_2 "\r\nConnection: keep-alive\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nUser-Agent: RAGE\r\n\r\n"
#define SOCKET_HEADERS_POST_1 "\r\nContent-Type: application/x-www-form-urlencoded"
#define SOCKET_HEADERS_POST_LENGTH "\r\nContent-Length: "
#define SOCKET_HEADERS_POST_2 "\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nUser-Agent: RAGE\r\n\r\n"

#define BOOL2RB(x) ((x) ? Qtrue : Qfalse)
#define RB2BOOL(x) (TYPE(x) == T_TRUE)

#define random_float() (float)rand() / RAND_MAX
#define polar_radius(px, py) sqrt(px * px + py * py)
#define polar_angle(px, py) atan2(py, px)
#define rotated_x(px, py, rad_angle) sqrt(px * px + py * py) * sin(atan2(py, px) + rad_angle)
#define rotated_y(px, py, rad_angle) sqrt(px * px + py * py) * cos(atan2(py, px) + rad_angle)
