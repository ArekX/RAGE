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

#define RAGE_RB_PROC_ERROR "You can only pass instances of Proc object as an argument."

#define RAGE_REGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_FALSE) { if (rb_class_of(proc) != rb_cProc) rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); else rb_ary_push(observer, proc);}
#define RAGE_UNREGISTER_EVENT(observer, proc) if (TYPE(rb_ary_includes(observer, proc)) == T_TRUE) { if (rb_class_of(proc) != rb_cProc) rb_raise(rb_eTypeError, RAGE_RB_PROC_ERROR); else rb_ary_delete(observer, proc);}

#define DEVELOPMENT_VERSION 1