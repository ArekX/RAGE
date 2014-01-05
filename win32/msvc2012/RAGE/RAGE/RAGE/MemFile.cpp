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

#include "MemFile.h"

#if RAGE_COMPILE_FILES && RAGE_COMPILE_MEM_FILE

namespace RAGE
{
	namespace Filesystem
	{
		MemFile::MemFile(void)
		{
			disposed = false;
			file = nullptr;
			data = nullptr;
			len = 0;
		}

		void MemFile::load_from_rage_file(BaseFile *b_file, char* mode)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (b_file->disposed)
			{
				rb_raise(rb_eArgError, RAGE_ERROR_FS_DISPOSED_RAGE_FILE);
				return;
			}

			if (data != nullptr)
			{
				if (file != nullptr)
					al_fclose(file);

				al_free(data);
			}
			
			len = al_fsize(b_file->file);

			data = (char*)al_malloc(len);
			al_fread(b_file->file, data, len);

			file = al_open_memfile(data, len, mode);
		}

		void MemFile::load_from_string(char *l_data, size_t l_len, char *mode)
		{
			RAGE_CHECK_DISPOSED(disposed);
		
			if (data != nullptr)
			{
				if (file != nullptr)
					al_fclose(file);

				al_free(data);
			}

			data = (char*)al_malloc(l_len);

			memcpy(data, l_data, l_len);

			len = l_len;

			file = al_open_memfile(data, len, mode);
		}

		void MemFile::open(int64_t size, char* mode)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (data != nullptr)
			{
				if (file != nullptr)
					al_fclose(file);

				al_free(data);
			}

			data = (char*)al_malloc(size);
			memset(data, 0, size);
			len = size;

			file = al_open_memfile(data, size, mode);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_MEMFILE_CANNOT_OPEN);
				return;
			}
		}

		int MemFile::write_byte(char data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fputc(file, data);
		}

		int MemFile::write_word(int16_t data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		int MemFile::write_dword(int32_t data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		int MemFile::write_float(float data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		int MemFile::write_double(double data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		size_t MemFile::write(const char* data, size_t len)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, data, len);
		}

		char MemFile::read_byte(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fgetc(file);
		}

		int16_t MemFile::read_word(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			int16_t ret = 0;
			al_fread(file, &ret, sizeof(ret));
			return ret;
		}

		int32_t MemFile::read_dword(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			int32_t ret = 0;
			al_fread(file, &ret, sizeof(ret));
			return ret;
		}

		float MemFile::read_float(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			float ret = 0;
			al_fread(file, &ret, sizeof(ret));

			return ret;
		}

		double MemFile::read_double(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			double ret = 0;
			al_fread(file, &ret, sizeof(ret));

			return ret;
		}

		VALUE MemFile::read(size_t amount)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return Qnil;
			}

			char* data;

			if (amount == 0)
				amount = al_fsize(file);

			data = new char[amount + 1];
			
			int read = al_fread(file, data, amount);

			if (read == 0)
				return Qnil;
			else
			{
				data[amount] = 0;
				
				VALUE ret_string = rb_str_new(data, amount);
				delete[] data;

				return ret_string;
			}
			
		}

		int64_t MemFile::get_position(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_ftell(file);
		}

		void MemFile::set_position(int64_t pos)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return;
			}

			al_fseek(file, pos, ALLEGRO_SEEK_SET);
		}

		void MemFile::seek(int64_t offset, int seek_type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return;
			}

			al_fseek(file, offset, seek_type);
		}

		bool MemFile::is_eof(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (file == nullptr)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return false;
			}

			return al_feof(file);
		}

		void MemFile::close(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file != nullptr)
			{
				al_fclose(file);
				al_free(data);
				len = 0;
			}
			else
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
		}


		int64_t MemFile::get_size(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return len;
		}

		void MemFile::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (data != nullptr)
			{
				if (file != nullptr)
					al_fclose(file);

				al_free(data);
			}

			disposed = true;
		}

		MemFile::~MemFile(void)
		{
			if (!disposed)
				dispose();
		}
	}
}

#endif