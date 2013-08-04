#pragma once

#include "File.h"

namespace RAGE
{
	namespace Filesystem
	{
		class FileWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_open(VALUE self, VALUE filename, VALUE mode);
			static VALUE rb_read(int argc, VALUE *args, VALUE self);
			static VALUE rb_write(VALUE self, VALUE data);
			static VALUE rb_close(VALUE self);
			static VALUE rb_is_open(VALUE self);
			static VALUE rb_write_byte(VALUE self, VALUE byte);
			static VALUE rb_write_word(VALUE self, VALUE word);
			static VALUE rb_write_dword(VALUE self, VALUE dword);
			static VALUE rb_write_float(VALUE self, VALUE flt);
			static VALUE rb_write_double(VALUE self, VALUE dbl);
			static VALUE rb_read_byte(VALUE self);
			static VALUE rb_read_word(VALUE self);
			static VALUE rb_read_dword(VALUE self);
			static VALUE rb_read_float(VALUE self);
			static VALUE rb_read_double(VALUE self);
			static VALUE rb_is_eof(VALUE self);
			static VALUE rb_get_size(VALUE self);
			static VALUE rb_get_position(VALUE self);
			static VALUE rb_set_position(VALUE self, VALUE offset);
			static VALUE rb_seek(VALUE self, VALUE offset, VALUE type);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_is_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}