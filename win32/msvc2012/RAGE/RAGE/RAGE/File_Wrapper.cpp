#include "File_Wrapper.h"

namespace RAGE
{
	namespace Filesystem
	{
		VALUE rb_rageFileClass;

		VALUE FileWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, FileWrapper::rb_destroy, new File());
		}

		void FileWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE FileWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc == 2)
			{
				File *fl;
				Data_Get_Struct(self, File, fl);

				fl->load(StringValueCStr(args[0]), StringValueCStr(args[1]));
			}

			return Qnil;
		}

		VALUE FileWrapper::rb_open(VALUE self, VALUE filename, VALUE mode)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			fl->load(StringValueCStr(filename), StringValueCStr(mode));
			
			return Qnil;
		}

		VALUE FileWrapper::rb_write(VALUE self, VALUE data)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			const char *c_data = StringValueCStr(data);

			return LL2NUM(fl->write(c_data, strlen(c_data)));
		}

		VALUE FileWrapper::rb_close(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			fl->close();

			return Qnil;
		}

		VALUE FileWrapper::rb_read(int argc, VALUE *args, VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			if (argc == 1)
				return fl->read(NUM2LL(args[0]));
			else if (argc > 1)
			{
				rb_raise(rb_eException, RAGE_VAR_FUNCTION_TOO_MANY_ARGS);
				return Qnil;
			}
			else
				return fl->read(0);	
		}

		VALUE FileWrapper::rb_is_open(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return (fl->file != NULL) ? Qtrue : Qfalse;
		}

		VALUE FileWrapper::rb_write_byte(VALUE self, VALUE byte)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->write_byte(FIX2INT(byte)));
		}

		VALUE FileWrapper::rb_write_word(VALUE self, VALUE word)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->write_word(FIX2SHORT(word)));
		}

		VALUE FileWrapper::rb_write_dword(VALUE self, VALUE dword)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->write_dword(FIX2INT(dword)));
		}

		VALUE FileWrapper::rb_read_byte(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->read_byte());
		}

		VALUE FileWrapper::rb_read_word(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->read_word());
		}

		VALUE FileWrapper::rb_read_dword(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->read_dword());
		}

		VALUE FileWrapper::rb_write_float(VALUE self, VALUE flt)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->write_float(NUM2DBL(flt)));
		}

		VALUE FileWrapper::rb_write_double(VALUE self, VALUE dbl)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return INT2FIX(fl->write_double(NUM2DBL(dbl)));
		}

		VALUE FileWrapper::rb_read_float(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return DBL2NUM(fl->read_float());
		}

		VALUE FileWrapper::rb_read_double(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return DBL2NUM(fl->read_double());
		}

		VALUE FileWrapper::rb_is_eof(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return fl->is_eof() ? Qtrue : Qfalse;
		}

		VALUE FileWrapper::rb_get_position(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return LL2NUM(fl->get_position());
		}

		VALUE FileWrapper::rb_set_position(VALUE self, VALUE offset)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			fl->set_position(NUM2LL(offset));

			return Qnil;
		}

		VALUE FileWrapper::rb_dispose(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			fl->dispose();

			return Qnil;
		}

		VALUE FileWrapper::rb_is_disposed(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return fl->disposed ? Qtrue : Qfalse;
		}

		VALUE FileWrapper::rb_seek(VALUE self, VALUE offset, VALUE type)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			fl->seek(NUM2LL(offset), FIX2INT(type));

			return Qnil;
		}

		VALUE FileWrapper::rb_get_size(VALUE self)
		{
			File *fl;
			Data_Get_Struct(self, File, fl);

			return LL2NUM(fl->get_size());
		}

		void FileWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::File")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rageFileClass = rb_define_class_under(rage, "File", rb_cObject);

			VALUE fs = rb_define_module_under(rage, "FS");
			rb_define_const(fs, "SEEK_SET", INT2FIX(ALLEGRO_SEEK_SET));
			rb_define_const(fs, "SEEK_CUR", INT2FIX(ALLEGRO_SEEK_CUR));
			rb_define_const(fs, "SEEK_END", INT2FIX(ALLEGRO_SEEK_END));

			rb_define_alloc_func(rb_rageFileClass, FileWrapper::rb_alloc);

			rb_define_method(rb_rageFileClass, "initialize", RFUNC(FileWrapper::rb_initialize), -1);
			rb_define_method(rb_rageFileClass, "isOpen?", RFUNC(FileWrapper::rb_is_open), 0);
			rb_define_method(rb_rageFileClass, "eof?", RFUNC(FileWrapper::rb_is_eof), 0);
			rb_define_method(rb_rageFileClass, "size", RFUNC(FileWrapper::rb_get_size), 0);
			rb_define_method(rb_rageFileClass, "open", RFUNC(FileWrapper::rb_open), 2);
			rb_define_method(rb_rageFileClass, "read", RFUNC(FileWrapper::rb_read), -1);
			rb_define_method(rb_rageFileClass, "write", RFUNC(FileWrapper::rb_write), 1);
			rb_define_method(rb_rageFileClass, "writeByte", RFUNC(FileWrapper::rb_write_byte), 1);
			rb_define_method(rb_rageFileClass, "writeWord", RFUNC(FileWrapper::rb_write_word), 1);
			rb_define_method(rb_rageFileClass, "writeDWord", RFUNC(FileWrapper::rb_write_dword), 1);
			rb_define_method(rb_rageFileClass, "writeFloat", RFUNC(FileWrapper::rb_write_float), 1);
			rb_define_method(rb_rageFileClass, "writeDouble", RFUNC(FileWrapper::rb_write_double), 1);
			rb_define_method(rb_rageFileClass, "readByte", RFUNC(FileWrapper::rb_read_byte), 0);
			rb_define_method(rb_rageFileClass, "readWord", RFUNC(FileWrapper::rb_read_word), 0);
			rb_define_method(rb_rageFileClass, "readDWord", RFUNC(FileWrapper::rb_read_dword), 0);
			rb_define_method(rb_rageFileClass, "readFloat", RFUNC(FileWrapper::rb_read_float), 0);
			rb_define_method(rb_rageFileClass, "readDouble", RFUNC(FileWrapper::rb_read_double), 0);
			rb_define_method(rb_rageFileClass, "position=", RFUNC(FileWrapper::rb_set_position), 1);
			rb_define_method(rb_rageFileClass, "position", RFUNC(FileWrapper::rb_get_position), 0);
			rb_define_method(rb_rageFileClass, "close", RFUNC(FileWrapper::rb_close), 0);

		}

		VALUE FileWrapper::get_ruby_class(void)
		{
			return rb_rageFileClass;
		}

		VALUE FileWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rageFileClass);
		}
	}
}