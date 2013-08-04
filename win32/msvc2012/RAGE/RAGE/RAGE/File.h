#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Filesystem
	{
		class File
		{
		public:
			bool disposed;
			ALLEGRO_FILE *file;
			File(void);
			void load(char *filename, char *mode);
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
			~File(void);
		};

	}
}