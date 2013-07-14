#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Filesystem
	{
		class IniFile
		{
		private:
			ALLEGRO_CONFIG *ini;
		public:
			bool disposed;
			IniFile(void);
			void create_new(void);
			void load(char *filename);
			void save(char *filename);
			const char* get(char *section, char* key);
			void set(char *section, char *key, char* value);
			void dispose(void);
			~IniFile(void);
		};
	}
}
