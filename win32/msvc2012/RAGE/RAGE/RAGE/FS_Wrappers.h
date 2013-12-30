/*
Copyright (c) 2013 Aleksandar Panic

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

#if RAGE_COMPILE_FS

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
			static VALUE rb_get_absolute_path(VALUE self, VALUE filename);
		public:
			static bool is_physfs_on(void);
			static void force_physfs_on(void);
			static void load_wrappers(void);
		};

	}
}

#endif