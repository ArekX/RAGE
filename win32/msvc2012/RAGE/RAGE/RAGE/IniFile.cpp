#include "IniFile.h"

namespace RAGE
{
	namespace Filesystem
	{
		IniFile::IniFile(void)
		{
			disposed = false;
			ini = NULL;
		}

		void IniFile::create_new(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ini != NULL)
				al_destroy_config(ini);

			ini = al_create_config();
		}

		void IniFile::load(char *filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (ini != NULL)
				al_destroy_config(ini);

			ini = al_load_config_file(filename);
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

			return al_get_config_value(ini, section, key);
		}

		void IniFile::set(char *section, char *key, char* value)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_config_value(ini, section, key, value);
		}

		void IniFile::dispose()
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_destroy_config(ini);

			disposed = true;
		}

		IniFile::~IniFile(void)
		{
			if (!disposed)
				dispose();
		}
	}
}