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

#if RAGE_COMPILE_FILES && RAGE_COMPILE_FILE

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

#endif