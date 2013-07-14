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
			static VALUE rb_physfs_get_write_dir(VALUE self);
			static VALUE rb_physfs_get_modified_time(VALUE self, VALUE filename);
			static VALUE rb_physfs_file_exists(VALUE self, VALUE filename);
			static VALUE rb_physfs_dir_exists(VALUE self, VALUE dirname);
			static VALUE rb_get_mount_path(VALUE self, VALUE mount_dir);
			static VALUE rb_physfs_make_dir(VALUE self, VALUE dirname);
			static VALUE rb_physfs_get_dir_separator(VALUE self);
			static VALUE rb_physfs_delete(VALUE self, VALUE path);
			static VALUE rb_physfs_get_last_error(VALUE self);
		public:
			static bool is_physfs_on(void);
			static void force_physfs_on(void);
			static void load_wrappers(void);
		};

	}
}