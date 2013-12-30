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

#include "IniFile.h"

#if RAGE_COMPILE_FILES && RAGE_COMPILE_INI_FILE

namespace RAGE
{
	namespace Filesystem
	{
		IniFile::IniFile(void)
		{
			disposed = false;
			ini = NULL;
			rage_file = Qnil;
		}

		void IniFile::create_new(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rage_file = Qnil;

			if (ini != NULL)
				al_destroy_config(ini);

			ini = al_create_config();

			if (ini == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_INI_CREATE_FAIL);
				return;
			}
		}

		void IniFile::load(char *filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rage_file = Qnil;

			if (ini != NULL)
				al_destroy_config(ini);

			ini = al_load_config_file(filename);

			if (ini == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_INI_LOAD_FAIL, filename);
				return;
			}
		}

		void IniFile::load_rage_file(VALUE r_file)
		{
			RAGE_CHECK_DISPOSED(disposed);

			BaseFile *fl;
			Data_Get_Struct(r_file, BaseFile, fl);

			if (fl->disposed)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_DISPOSED_RAGE_FILE_READ);
				return;
			}

			if (fl->file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_RAGE_FILE_NOT_LOADED);
				return;
			}

			rage_file = r_file;

			if (ini != NULL)
				al_destroy_config(ini);

			ini = al_load_config_file_f(fl->file);

			if (ini == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_INI_LOAD_FAIL, RAGE_BASE_FILE);
				return;
			}
		}

		void IniFile::save_rage_file(BaseFile *fl)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ini != NULL)
				al_save_config_file_f(fl->file, ini);
		}

		void IniFile::save(char *filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ini != NULL)
					al_save_config_file(filename, ini);
		}

		const char* IniFile::get(char *section, char* key)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			if (rage_file != Qnil)
			{
				BaseFile *fl;
				Data_Get_Struct(rage_file, BaseFile, fl);

				if (fl->disposed)
				{
					rb_raise(rb_eException, RAGE_ERROR_FS_DISPOSED_RAGE_FILE_READ);
					return NULL;
				}
			}

			return al_get_config_value(ini, section, key);
		}

		void IniFile::set(char *section, char *key, char* value)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (rage_file != Qnil)
			{
				BaseFile *fl;
				Data_Get_Struct(rage_file, BaseFile, fl);

				if (fl->disposed)
				{
					rb_raise(rb_eException, RAGE_ERROR_FS_DISPOSED_RAGE_FILE_WRITE);
					return;
				}
			}

			al_set_config_value(ini, section, key, value);
		}

		void IniFile::gc_mark(void)
		{
			if (!disposed && (rage_file != Qnil))
				rb_gc_mark(rage_file);
		}

		void IniFile::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_destroy_config(ini);
			rage_file = Qnil;

			disposed = true;
		}

		IniFile::~IniFile(void)
		{
			if (!disposed)
				dispose();
		}
	}
}

#endif