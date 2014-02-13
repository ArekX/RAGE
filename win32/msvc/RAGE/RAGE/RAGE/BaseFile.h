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

#if RAGE_COMPILE_FILES

#define RAGE_BASE_FILE "RAGE::BaseFile"

namespace RAGE
{
	namespace Filesystem
	{
		class BaseFile
		{
		public:
			bool disposed;
			ALLEGRO_FILE *file;
			virtual void close(void) = 0;
			virtual void dispose(void) = 0;
			virtual void seek(int64_t offset, int seek_type) = 0;
			virtual size_t write(const char* data, size_t len) = 0;
			virtual int write_byte(char data) = 0;
			virtual int write_word(int16_t data) = 0;
			virtual int write_dword(int32_t data) = 0;
			virtual int write_float(float data) = 0;
			virtual int write_double(double data) = 0;
			virtual char read_byte(void) = 0;
			virtual int16_t read_word(void) = 0;
			virtual int32_t read_dword(void) = 0;
			virtual float read_float(void) = 0;
			virtual double read_double(void) = 0;
			virtual int64_t get_size(void) = 0;
			virtual int64_t get_position(void) = 0;
			virtual void set_position(int64_t pos) = 0;
			virtual bool is_eof(void) = 0;
			virtual VALUE read(size_t amount) = 0;
		};
	}
}

#endif