#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Filesystem
	{

		class FSWrappers
		{
		private:
			static VALUE rb_physfs_start(VALUE self);
			static VALUE rb_physfs_stop(VALUE self);
			static VALUE rb_physfs_add_file(VALUE self, VALUE filename, VALUE mount, VALUE prepend);
			static VALUE rb_physfs_add_path(VALUE self, VALUE path, VALUE mount, VALUE prepend);
			static VALUE rb_physfs_remove(VALUE self, VALUE mount);
			static VALUE rb_physfs_started(VALUE self);
			static VALUE rb_physfs_get_mounts(VALUE self);
			static VALUE rb_physfs_enum_files(VALUE self, VALUE dir);
			static VALUE rb_physfs_set_write_dir(VALUE self, VALUE dir);
			static VALUE rb_physfs_get_write_dir(VALUE self, VALUE dir);
		public:
			static bool is_physfs_on();
			static void force_physfs_on();
			static void init_wrappers();
		};

	}
}