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

#pragma once

#include "rage_standard_headers.h"
#include "BaseFile.h"

#if RAGE_COMPILE_FILES && RAGE_COMPILE_INI_FILE

namespace RAGE
{
	namespace Filesystem
	{
		class IniFile
		{
		private:
			ALLEGRO_CONFIG *ini;
			VALUE rage_file;
		public:
			bool disposed;
			IniFile(void);
			void create_new(void);
			void load_rage_file(VALUE r_file);
			void save_rage_file(BaseFile *fl);
			void load(char *filename);
			void save(char *filename);
			const char* get(char *section, char* key);
			void set(char *section, char *key, char* value);
			void gc_mark(void);
			void dispose(void);
			~IniFile(void);
		};
	}
}

#endif