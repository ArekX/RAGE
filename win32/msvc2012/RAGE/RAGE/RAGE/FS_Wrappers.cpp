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
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}
		}

		VALUE FSWrappers::rb_physfs_add_path(VALUE self, VALUE path, VALUE mount, VALUE prepend)
		{
			int prep_append = (TYPE(prepend) == T_TRUE) ? 0 : 1;

			if (!PHYSFS_mount(StringValueCStr(path), StringValueCStr(mount), prep_append))
			{
				rb_raise(rb_eArgError, RAGE_RB_PATH_MISSING_ERROR, StringValueCStr(path));
				return Qfalse;
			}
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

		VALUE FSWrappers::rb_physfs_get_write_dir(VALUE self, VALUE dir)
		{
			return rb_str_new_cstr(PHYSFS_getWriteDir());
		}

		void FSWrappers::init_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE fs = rb_define_module_under(rage, "FS");

			rb_define_module_function(fs, "startFS", RFUNC(FSWrappers::rb_physfs_start), 0);
			rb_define_module_function(fs, "stopFS", RFUNC(FSWrappers::rb_physfs_stop), 0);
			rb_define_module_function(fs, "startedFS?", RFUNC(FSWrappers::rb_physfs_started), 0);
			rb_define_module_function(fs, "mountArchive", RFUNC(FSWrappers::rb_physfs_add_file), 3);
			rb_define_module_function(fs, "mountPath", RFUNC(FSWrappers::rb_physfs_add_path), 3);
			rb_define_module_function(fs, "removeMount", RFUNC(FSWrappers::rb_physfs_remove), 1);
			rb_define_module_function(fs, "getMounts", RFUNC(FSWrappers::rb_physfs_get_mounts), 0);
			rb_define_module_function(fs, "enumFS", RFUNC(FSWrappers::rb_physfs_enum_files), 1);
			rb_define_module_function(fs, "writeDir=", RFUNC(FSWrappers::rb_physfs_set_write_dir), 1);
			rb_define_module_function(fs, "writeDir", RFUNC(FSWrappers::rb_physfs_get_write_dir), 1);
		}
	}
}
