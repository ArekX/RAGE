#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Filesystem
	{
		class IniFile
		{
		private:
			bool disposed;
			ALLEGRO_CONFIG *ini;
		public:
			IniFile(void);
			void create_new(void);
			void load(char *filename);
			void save(char *filename);
			const char* get(char *section, char* key);
			void set(char *section, char *key, char* value);
			void dispose();
			~IniFile(void);
		};
	}
}
