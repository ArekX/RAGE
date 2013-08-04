#include "File.h"
namespace RAGE
{
	namespace Filesystem
	{
		File::File(void)
		{
			file = NULL;
			disposed = false;
		}

		void File::load(char *filename, char *mode)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file != NULL)
				al_fclose(file);

			file = al_fopen(filename, mode);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_CANNOT_LOAD, filename);
				disposed = true;
				return;
			}
		}

		int File::write_byte(char data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fputc(file, data);
		}

		int File::write_word(int16_t data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		int File::write_dword(int32_t data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		int File::write_float(float data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		int File::write_double(double data)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, &data, sizeof(data));
		}

		size_t File::write(const char* data, size_t len)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fwrite(file, data, len);
		}

		char File::read_byte(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_fgetc(file);
		}

		int16_t File::read_word(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			int16_t ret = 0;
			al_fread(file, &ret, sizeof(ret));
			return ret;
		}

		int32_t File::read_dword(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			int32_t ret = 0;
			al_fread(file, &ret, sizeof(ret));
			return ret;
		}

		float File::read_float(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			float ret = 0;
			al_fread(file, &ret, sizeof(ret));

			return ret;
		}

		double File::read_double(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			double ret = 0;
			al_fread(file, &ret, sizeof(ret));

			return ret;
		}

		VALUE File::read(size_t amount)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, Qnil);

			if (file == NULL)
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
				
				VALUE ret_string = rb_str_new2(data);
				delete[] data;

				return ret_string;
			}
			
		}

		int64_t File::get_size(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file != NULL)
				return al_fsize(file);
			else
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);

			return 0;
		}

		int64_t File::get_position(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return 0;
			}

			return al_ftell(file);
		}

		void File::set_position(int64_t pos)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return;
			}

			al_fseek(file, pos, ALLEGRO_SEEK_SET);
		}

		void File::seek(int64_t offset, int seek_type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return;
			}

			al_fseek(file, offset, seek_type);
		}

		bool File::is_eof(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			if (file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
				return false;
			}

			return al_feof(file);
		}

		void File::close(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file != NULL)
				al_fclose(file);
			else
				rb_raise(rb_eException, RAGE_ERROR_FS_FILE_NOT_LOADED);
		}

		void File::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (file != NULL)
			{
				al_fclose(file);
				file = NULL;
			}
		}

		File::~File(void)
		{
			if (!disposed)
				dispose();
		}
	}
}
