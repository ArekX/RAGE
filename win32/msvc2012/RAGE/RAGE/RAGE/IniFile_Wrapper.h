#pragma once

#include "IniFile.h"

namespace RAGE
{
	namespace Filesystem
	{

		class IniFileWrapper
		{
		private:
			static void rb_destroy(void *value);
			static VALUE rb_alloc(VALUE self);
			static VALUE rb_create(VALUE self);
			static VALUE rb_load(VALUE self, VALUE filename);
			static VALUE rb_save(VALUE self, VALUE filename);
			static VALUE rb_get(VALUE self, VALUE section, VALUE key);
			static VALUE rb_set(VALUE self, VALUE section, VALUE key, VALUE val);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}

