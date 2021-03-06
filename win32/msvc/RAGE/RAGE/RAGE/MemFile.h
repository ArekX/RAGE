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

#if RAGE_COMPILE_FILES && RAGE_COMPILE_MEM_FILE

namespace RAGE
{
	namespace Filesystem
	{
		class MemFile : public BaseFile
		{
		private:
			char* data;
			int64_t len;
		public:
			MemFile(void);
			void load_from_rage_file(BaseFile *b_file, char* mode);
			void load_from_string(char *l_data, size_t l_len, char *mode);
			void open(int64_t size, char* mode);
			void close(void);
			void dispose(void);
			void seek(int64_t offset, int seek_type);
			size_t write(const char* data, size_t len);
			int write_byte(char data);
			int write_word(int16_t data);
			int write_dword(int32_t data);
			int write_float(float data);
			int write_double(double data);
			char read_byte(void);
			int16_t read_word(void);
			int32_t read_dword(void);
			float read_float(void);
			double read_double(void);
			int64_t get_size(void);
			int64_t get_position(void);
			void set_position(int64_t pos);
			bool is_eof(void);
			VALUE read(size_t amount);
			~MemFile(void);
		};
	}
}

#endif