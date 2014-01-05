/*
Copyright (c) 2014 Aleksandar Panic

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

#include "IniFile_Wrapper.h"
#include "BaseFile_Wrapper.h"
#include "IniFile.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_FILES && RAGE_COMPILE_INI_FILE

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
			return Data_Wrap_Struct(self, IniFileWrapper::rb_mark, IniFileWrapper::rb_destroy, new IniFile());
		}

		void IniFileWrapper::rb_mark(void *ptr)
		{
			((IniFile*)ptr)->gc_mark();
		}

		VALUE IniFileWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc == 1)
				return rb_load(self, args[0]);
			
			return rb_create(self);
		}

		VALUE IniFileWrapper::rb_create(VALUE self)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			ini->create_new();
			return Qnil;
		}

		VALUE IniFileWrapper::rb_load(VALUE self, VALUE file)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);
			
			if (RAGE_IS_SUPERCLASS_OF(file, BaseFileWrapper))
			{	
				ini->load_rage_file(file);
			}
			else
			{
				char *absolute_file = Interpreter::Ruby::get_file_path(file);
				if (absolute_file == nullptr)
				{
				
					rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(file));
					return Qfalse;
				}

				ini->load(absolute_file);
			}

			return Qtrue;
		}

		VALUE IniFileWrapper::rb_save(VALUE self, VALUE file)
		{
			IniFile *ini;
			Data_Get_Struct(self, IniFile, ini);

			if (RAGE_IS_SUPERCLASS_OF(file, BaseFileWrapper))
			{
				BaseFile *fl;
				Data_Get_Struct(file, BaseFile, fl);

				ini->save_rage_file(fl);
			}
			else
				ini->save(StringValueCStr(file));

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

		void IniFileWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::IniFile")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rageIniFileClass = rb_define_class_under(rage, "IniFile", rb_cObject);

			rb_define_alloc_func(rb_rageIniFileClass, IniFileWrapper::rb_alloc);

			rb_define_method(rb_rageIniFileClass, "initialize", RFUNC(IniFileWrapper::rb_initialize), -1);
			rb_define_method(rb_rageIniFileClass, "create", RFUNC(IniFileWrapper::rb_create), 0);
			rb_define_method(rb_rageIniFileClass, "load", RFUNC(IniFileWrapper::rb_load), 1);
			rb_define_method(rb_rageIniFileClass, "save", RFUNC(IniFileWrapper::rb_save), 1);
			rb_define_method(rb_rageIniFileClass, "get", RFUNC(IniFileWrapper::rb_get), 2);
			rb_define_method(rb_rageIniFileClass, "set", RFUNC(IniFileWrapper::rb_set), 3);
			rb_define_method(rb_rageIniFileClass, "dispose", RFUNC(IniFileWrapper::rb_dispose), 0);
			rb_define_method(rb_rageIniFileClass, "disposed?", RFUNC(IniFileWrapper::rb_disposed), 0);
		}

		VALUE IniFileWrapper::get_ruby_class(void)
		{
			return rb_rageIniFileClass;
		}

		VALUE IniFileWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, nullptr, rb_rageIniFileClass);
		}
	}
}

#endif