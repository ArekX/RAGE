#include "FS_Wrappers.h"

namespace RAGE
{
	namespace Filesystem
	{
		bool physfs_on = false;

		VALUE FSWrappers::rb_physfs_start(VALUE self)
		{
			if (physfs_on)
				return Qnil;

			al_set_physfs_file_interface();
			physfs_on = true;

			return Qnil;
		}

		VALUE FSWrappers::rb_physfs_stop(VALUE self)
		{
			if (!physfs_on)
				return Qnil;

			al_set_standard_file_interface();
			physfs_on = false;

			return Qnil;
		}

		VALUE FSWrappers::rb_physfs_add_file(VALUE self, VALUE filename, VALUE mount, VALUE prepend)
		{
			VALUE fname = rb_find_file(filename);
			if (TYPE(fname) != T_STRING)
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}

			int prep_append = (TYPE(prepend) == T_TRUE) ? 0 : 1;
			
			if (!PHYSFS_mount(StringValueCStr(filename), StringValueCStr(mount), prep_append))
				return Qfalse;

			return Qtrue;
		}

		VALUE FSWrappers::rb_physfs_add_path(VALUE self, VALUE path, VALUE mount, VALUE prepend)
		{
			int prep_append = (TYPE(prepend) == T_TRUE) ? 0 : 1;

			if (!PHYSFS_mount(StringValueCStr(path), StringValueCStr(mount), prep_append))
				return Qfalse;

			return Qtrue;
			
		}

		VALUE FSWrappers::rb_physfs_started(VALUE self)
		{
			if (physfs_on)
				return Qtrue;
			else
				return Qfalse;
		}

		void FSWrappers::force_physfs_on()
		{
			physfs_on = true;
			al_set_physfs_file_interface();
		}

		bool FSWrappers::is_physfs_on()
		{
			return physfs_on;
		}

		VALUE FSWrappers::rb_physfs_get_mounts(VALUE self)
		{
			VALUE list = rb_ary_new();
			rb_gc_register_address(&list);

			char **lst = PHYSFS_getSearchPath();
			int i = 0;

			while (lst[i] != NULL)
			{
				rb_ary_push(list, rb_str_new_cstr(lst[i++]));
			}

			PHYSFS_freeList(lst);

			return list;
		}

		VALUE FSWrappers::rb_physfs_remove(VALUE self, VALUE mount)
		{
			if (!PHYSFS_removeFromSearchPath(StringValueCStr(mount)))
				return Qfalse;

			return Qtrue;
		}

		VALUE FSWrappers::rb_physfs_enum_files(VALUE self, VALUE dir)
		{
			VALUE list = rb_ary_new();
			rb_gc_register_address(&list);

			char **lst = PHYSFS_enumerateFiles(StringValueCStr(dir));
			int i = 0;

			while (lst[i] != NULL)
			{
				rb_ary_push(list, rb_str_new_cstr(lst[i++]));
			}

			PHYSFS_freeList(lst);

			return list;
		}

		VALUE FSWrappers::rb_physfs_set_write_dir(VALUE self, VALUE dir)
		{
			if (!PHYSFS_setWriteDir(StringValueCStr(dir)))
				return Qfalse;
			return Qtrue;
		}

		VALUE FSWrappers::rb_physfs_get_write_dir(VALUE self)
		{
			return rb_str_new_cstr(PHYSFS_getWriteDir());
		}

		VALUE FSWrappers::rb_get_mount_path(VALUE self, VALUE mount_dir)
		{
			return rb_str_new_cstr(PHYSFS_getMountPoint(StringValueCStr(mount_dir)));
		}

		VALUE FSWrappers::rb_physfs_get_modified_time(VALUE self, VALUE filename)
		{
			return LL2NUM(PHYSFS_getLastModTime(StringValueCStr(filename)));
		}

		VALUE FSWrappers::rb_physfs_file_exists(VALUE self, VALUE filename)
		{
			if (PHYSFS_exists(StringValueCStr(filename)))
				return Qtrue;
			
			return Qfalse;
		}

		VALUE FSWrappers::rb_physfs_dir_exists(VALUE self, VALUE dirname)
		{
			if (PHYSFS_isDirectory(StringValueCStr(dirname)))
				return Qtrue;
			
			return Qfalse;
		}

		VALUE FSWrappers::rb_physfs_make_dir(VALUE self, VALUE dirname)
		{
			if (PHYSFS_mkdir(StringValueCStr(dirname)))
				return Qtrue;
			
			return Qfalse;
		}

		VALUE FSWrappers::rb_physfs_get_dir_separator(VALUE self)
		{
			return rb_str_new_cstr(PHYSFS_getDirSeparator());
		}

		VALUE FSWrappers::rb_physfs_delete(VALUE self, VALUE path)
		{
			if (PHYSFS_delete(StringValueCStr(path)))
				return Qtrue;
			
			return Qfalse;
		}

		VALUE FSWrappers::rb_physfs_get_last_error(VALUE self)
		{
			return rb_str_new_cstr(PHYSFS_getLastError());
		}

		void FSWrappers::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE fs = rb_define_module_under(rage, "FS");

			rb_define_module_function(fs, "startFS", RFUNC(FSWrappers::rb_physfs_start), 0);
			rb_define_module_function(fs, "stopFS", RFUNC(FSWrappers::rb_physfs_stop), 0);
			rb_define_module_function(fs, "started?", RFUNC(FSWrappers::rb_physfs_started), 0);
			rb_define_module_function(fs, "mountArchive", RFUNC(FSWrappers::rb_physfs_add_file), 3);
			rb_define_module_function(fs, "mountPath", RFUNC(FSWrappers::rb_physfs_add_path), 3);
			rb_define_module_function(fs, "removeMount", RFUNC(FSWrappers::rb_physfs_remove), 1);
			rb_define_module_function(fs, "getMounts", RFUNC(FSWrappers::rb_physfs_get_mounts), 0);
			rb_define_module_function(fs, "enumFS", RFUNC(FSWrappers::rb_physfs_enum_files), 1);
			rb_define_module_function(fs, "writeDir=", RFUNC(FSWrappers::rb_physfs_set_write_dir), 1);
			rb_define_module_function(fs, "writeDir", RFUNC(FSWrappers::rb_physfs_get_write_dir), 0);
			rb_define_module_function(fs, "getMountPath", RFUNC(FSWrappers::rb_get_mount_path), 1);
			rb_define_module_function(fs, "getModTime", RFUNC(FSWrappers::rb_physfs_get_modified_time), 1);
			rb_define_module_function(fs, "fileExists?", RFUNC(FSWrappers::rb_physfs_file_exists), 1);
			rb_define_module_function(fs, "dirExists?", RFUNC(FSWrappers::rb_physfs_dir_exists), 1);
			rb_define_module_function(fs, "mkDir", RFUNC(FSWrappers::rb_physfs_make_dir), 1);
			rb_define_module_function(fs, "getDirSep", RFUNC(FSWrappers::rb_physfs_get_dir_separator), 0);
			rb_define_module_function(fs, "delete", RFUNC(FSWrappers::rb_physfs_delete), 1);
			rb_define_module_function(fs, "lastError", RFUNC(FSWrappers::rb_physfs_get_last_error), 0);
		}
	}
}
