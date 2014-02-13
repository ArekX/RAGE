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

#include "MemFile_Wrapper.h"
#include "BaseFile_Wrapper.h"
#include "MemFile.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_FILES && RAGE_COMPILE_MEM_FILE

namespace RAGE
{
	namespace Filesystem
	{
		VALUE rb_rageMemFileClass;

		VALUE MemFileWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, MemFileWrapper::rb_destroy, new MemFile());
		}

		void MemFileWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE MemFileWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc == 2)
			{
				if (RAGE_IS_SUPERCLASS_OF(args[0], BaseFileWrapper))
					MemFileWrapper::rb_load_rage_file(self, args[0], args[1]);
				else if (TYPE(args[0]) == T_STRING)
					MemFileWrapper::rb_load_from_string(self, args[0], args[1]);
				else
					MemFileWrapper::rb_open(self, args[0], args[1]);
			}

			return Qnil;
		}

		VALUE MemFileWrapper::rb_load_rage_file(VALUE self, VALUE ragefile, VALUE mode)
		{
			MemFile *fl;
			BaseFile *rfile;
			Data_Get_Struct(self, MemFile, fl);
			Data_Get_Struct(ragefile, BaseFile, rfile);

			fl->load_from_rage_file(rfile, StringValueCStr(mode));

			return Qnil;
		}

		VALUE MemFileWrapper::rb_load_from_string(VALUE self, VALUE string, VALUE mode)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			if (TYPE(string) != T_STRING)
			{
				rb_raise(rb_eArgError, RAGE_ERROR_FS_PASSED_ARGUMENT_NOT_STRING);
				return Qnil;
			}

			fl->load_from_string(RSTRING_PTR(string), RSTRING_LEN(string), StringValueCStr(mode));

			return Qnil;
		}

		VALUE MemFileWrapper::rb_open(VALUE self, VALUE size, VALUE mode)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			fl->open(NUM2LL(size), StringValueCStr(mode));
			
			return Qnil;
		}

		VALUE MemFileWrapper::rb_write(VALUE self, VALUE data)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			if (TYPE(data) != T_STRING)
			{
				rb_raise(rb_eArgError, RAGE_ERROR_FS_PASSED_ARGUMENT_NOT_STRING);
				return Qnil;
			}

			return LL2NUM(fl->write(RSTRING_PTR(data), RSTRING_LEN(data)));
		}

		VALUE MemFileWrapper::rb_close(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			fl->close();

			return Qnil;
		}

		VALUE MemFileWrapper::rb_read(int argc, VALUE *args, VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

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

		VALUE MemFileWrapper::rb_is_open(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return (fl->file != nullptr) ? Qtrue : Qfalse;
		}

		VALUE MemFileWrapper::rb_write_byte(VALUE self, VALUE byte)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->write_byte(FIX2INT(byte)));
		}

		VALUE MemFileWrapper::rb_write_word(VALUE self, VALUE word)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->write_word(FIX2SHORT(word)));
		}

		VALUE MemFileWrapper::rb_write_dword(VALUE self, VALUE dword)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->write_dword(FIX2INT(dword)));
		}

		VALUE MemFileWrapper::rb_read_byte(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->read_byte());
		}

		VALUE MemFileWrapper::rb_read_word(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->read_word());
		}

		VALUE MemFileWrapper::rb_read_dword(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->read_dword());
		}

		VALUE MemFileWrapper::rb_write_float(VALUE self, VALUE flt)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->write_float(NUM2DBL(flt)));
		}

		VALUE MemFileWrapper::rb_write_double(VALUE self, VALUE dbl)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return INT2FIX(fl->write_double(NUM2DBL(dbl)));
		}

		VALUE MemFileWrapper::rb_read_float(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return DBL2NUM(fl->read_float());
		}

		VALUE MemFileWrapper::rb_read_double(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return DBL2NUM(fl->read_double());
		}

		VALUE MemFileWrapper::rb_is_eof(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return fl->is_eof() ? Qtrue : Qfalse;
		}

		VALUE MemFileWrapper::rb_get_position(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return LL2NUM(fl->get_position());
		}

		VALUE MemFileWrapper::rb_set_position(VALUE self, VALUE offset)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			fl->set_position(NUM2LL(offset));

			return Qnil;
		}

		VALUE MemFileWrapper::rb_dispose(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			fl->dispose();

			return Qnil;
		}

		VALUE MemFileWrapper::rb_is_disposed(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return fl->disposed ? Qtrue : Qfalse;
		}

		VALUE MemFileWrapper::rb_seek(VALUE self, VALUE offset, VALUE type)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			fl->seek(NUM2LL(offset), FIX2INT(type));

			return Qnil;
		}

		VALUE MemFileWrapper::rb_get_size(VALUE self)
		{
			MemFile *fl;
			Data_Get_Struct(self, MemFile, fl);

			return LL2NUM(fl->get_size());
		}

		void MemFileWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::MemFile")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rageMemFileClass = rb_define_class_under(rage, "MemFile", BaseFileWrapper::get_ruby_class());

			rb_define_alloc_func(rb_rageMemFileClass, MemFileWrapper::rb_alloc);

			rb_define_method(rb_rageMemFileClass, "initialize", RFUNC(MemFileWrapper::rb_initialize), -1);
			rb_define_method(rb_rageMemFileClass, "isOpen?", RFUNC(MemFileWrapper::rb_is_open), 0);
			rb_define_method(rb_rageMemFileClass, "eof?", RFUNC(MemFileWrapper::rb_is_eof), 0);
			rb_define_method(rb_rageMemFileClass, "size", RFUNC(MemFileWrapper::rb_get_size), 0);
			rb_define_method(rb_rageMemFileClass, "open", RFUNC(MemFileWrapper::rb_open), 2);
			rb_define_method(rb_rageMemFileClass, "openAsMemory", RFUNC(MemFileWrapper::rb_load_rage_file), 2);
			rb_define_method(rb_rageMemFileClass, "openFromString", RFUNC(MemFileWrapper::rb_load_from_string), 2);
			rb_define_method(rb_rageMemFileClass, "read", RFUNC(MemFileWrapper::rb_read), -1);
			rb_define_method(rb_rageMemFileClass, "write", RFUNC(MemFileWrapper::rb_write), 1);
			rb_define_method(rb_rageMemFileClass, "writeByte", RFUNC(MemFileWrapper::rb_write_byte), 1);
			rb_define_method(rb_rageMemFileClass, "writeWord", RFUNC(MemFileWrapper::rb_write_word), 1);
			rb_define_method(rb_rageMemFileClass, "writeDWord", RFUNC(MemFileWrapper::rb_write_dword), 1);
			rb_define_method(rb_rageMemFileClass, "writeFloat", RFUNC(MemFileWrapper::rb_write_float), 1);
			rb_define_method(rb_rageMemFileClass, "writeDouble", RFUNC(MemFileWrapper::rb_write_double), 1);
			rb_define_method(rb_rageMemFileClass, "readByte", RFUNC(MemFileWrapper::rb_read_byte), 0);
			rb_define_method(rb_rageMemFileClass, "readWord", RFUNC(MemFileWrapper::rb_read_word), 0);
			rb_define_method(rb_rageMemFileClass, "readDWord", RFUNC(MemFileWrapper::rb_read_dword), 0);
			rb_define_method(rb_rageMemFileClass, "readFloat", RFUNC(MemFileWrapper::rb_read_float), 0);
			rb_define_method(rb_rageMemFileClass, "readDouble", RFUNC(MemFileWrapper::rb_read_double), 0);
			rb_define_method(rb_rageMemFileClass, "position=", RFUNC(MemFileWrapper::rb_set_position), 1);
			rb_define_method(rb_rageMemFileClass, "position", RFUNC(MemFileWrapper::rb_get_position), 0);
			rb_define_method(rb_rageMemFileClass, "close", RFUNC(MemFileWrapper::rb_close), 0);
			rb_define_method(rb_rageMemFileClass, "dispose", RFUNC(MemFileWrapper::rb_dispose), 0);
			rb_define_method(rb_rageMemFileClass, "disposed?", RFUNC(MemFileWrapper::rb_is_disposed), 0);

		}

		VALUE MemFileWrapper::get_ruby_class(void)
		{
			return rb_rageMemFileClass;
		}

		VALUE MemFileWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, nullptr, rb_rageMemFileClass);
		}
	}
}

#endif