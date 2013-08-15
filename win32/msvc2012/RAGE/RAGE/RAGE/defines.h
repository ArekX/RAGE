#define ALLEGRO_STATICLINK

#define RFUNC RUBY_METHOD_FUNC
#define RAGE_CHECK_DISPOSED(disposed_var) if (disposed_var) { rb_raise(rb_eException, RAGE_ERROR_DISPOSED_OBJECT); return; }
#define RAGE_CHECK_DISPOSED_RET(disposed_var, ret) if (disposed_var) { rb_raise(rb_eException, RAGE_ERROR_DISPOSED_OBJECT); return ret; }

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

#define RAGE_DEV_END_TEXT "Your game has ended. Interpreter returned -> %d\n\n", error
#define RAGE_DEV_MESSAGE_W L"Welcome to RAGE - Ruby Awesome Game Engine. To start making games you need a file called boot.rb which needs to be in the same folder as this executable.\n\nIf you need to make an initial configuration for your game you need another file called conf.rb in the same folder as this executable. To learn more about game making process, please refer to the developer documentation which should come together as this executable.\n\nHave fun using RAGE!"
#define RAGE_DEV_MESSAGE_L "Welcome to RAGE - Ruby Awesome Game Engine. To start making games you need a file called boot.rb which needs to be in the same folder as this executable.\n\nIf you need to make an initial configuration for your game you need another file called conf.rb in the same folder as this executable. To learn more about game making process, please refer to the developer documentation which should come together as this executable.\n\nHave fun using RAGE!"
#define RAGE_DEV_MESSAGE_EXIT "\n\nPress any key to close this engine."
#define RAGE_DEV_TEXT "You are using Development Version of RAGE.\nFor distribution please use Production Version of RAGE.\n\n"

#define random_float() (float)rand() / RAND_MAX
#define polar_radius(px, py) sqrt(px * px + py * py)
#define polar_angle(px, py) atan2(py, px)
#define rotated_x(px, py, rad_angle) sqrt(px * px + py * py) * sin(atan2(py, px) + rad_angle)
#define rotated_y(px, py, rad_angle) sqrt(px * px + py * py) * cos(atan2(py, px) + rad_angle)
