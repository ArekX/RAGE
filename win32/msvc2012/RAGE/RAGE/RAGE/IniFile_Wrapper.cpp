#include "IniFile_Wrapper.h"

namespace RAGE
{
	namespace Filesystem
	{
		VALUE rb_rageIniFileClass;

		void IniFileWrapper::rb_destroy(void *value)
		{
			free(value);
		}

		VALUE IniFileWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, IniFileWrapper::rb_destroy, new IniFile());
		}

		VALUE IniFileWrapper::rb_create(VALUE self)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			ini->create_new();
			return Qnil;
		}

		VALUE IniFileWrapper::rb_load(VALUE self, VALUE filename)
		{
			char *absolute_file = Interpreter::Ruby::get_file_path(filename);
			if (absolute_file == NULL)
			{
				
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}
			
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);

			ini->load(absolute_file);

			return Qtrue;
		}

		VALUE IniFileWrapper::rb_save(VALUE self, VALUE filename)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			ini->save(StringValueCStr(filename));

			return Qnil;
		}

		VALUE IniFileWrapper::rb_get(VALUE self, VALUE section, VALUE key)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			return rb_str_new_cstr(ini->get(StringValueCStr(section), StringValueCStr(key)));
		}

		VALUE IniFileWrapper::rb_set(VALUE self, VALUE section, VALUE key, VALUE val)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			ini->set(StringValueCStr(section), StringValueCStr(key), StringValueCStr(val));
			return Qnil;
		}

		VALUE IniFileWrapper::rb_dispose(VALUE self)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			
			ini->dispose();

			return Qnil;
		}

		VALUE IniFileWrapper::rb_disposed(VALUE self)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			
			return (ini->disposed) ? Qtrue : Qfalse;
		}

		void IniFileWrapper::load_ruby_class()
		{
			VALUE rage = rb_define_module("RAGE");
			rb_rageIniFileClass = rb_define_class_under(rage, "IniFile", rb_cObject);

			rb_define_alloc_func(rb_rageIniFileClass, IniFileWrapper::rb_alloc);

			rb_define_method(rb_rageIniFileClass, "create", RFUNC(IniFileWrapper::rb_create), 0);
			rb_define_method(rb_rageIniFileClass, "load", RFUNC(IniFileWrapper::rb_load), 1);
			rb_define_method(rb_rageIniFileClass, "save", RFUNC(IniFileWrapper::rb_save), 1);
			rb_define_method(rb_rageIniFileClass, "get", RFUNC(IniFileWrapper::rb_get), 2);
			rb_define_method(rb_rageIniFileClass, "set", RFUNC(IniFileWrapper::rb_set), 3);
			rb_define_method(rb_rageIniFileClass, "dispose", RFUNC(IniFileWrapper::rb_dispose), 0);
			rb_define_method(rb_rageIniFileClass, "disposed?", RFUNC(IniFileWrapper::rb_disposed), 0);
		}

		VALUE IniFileWrapper::get_ruby_class()
		{
			return rb_rageIniFileClass;
		}

		VALUE IniFileWrapper::new_ruby_class_instance()
		{
			return rb_class_new_instance(0, NULL, rb_rageIniFileClass);
		}
	}
}