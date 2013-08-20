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

#include "BaseFile_Wrapper.h"

namespace RAGE
{
	namespace Filesystem
	{
		VALUE rb_rageBaseFileClass;

		VALUE BaseFileWrapper::rb_error_abstract(VALUE self)
		{
			rb_raise(rb_eException, RAGE_ERROR_FS_BASE_FILE_ERROR);
			return Qnil;
		}

		bool BaseFileWrapper::rb_is_enabled(void)
		{
			return (
					Interpreter::Ruby::get_config()->is_on("RAGE::File") ||
					Interpreter::Ruby::get_config()->is_on("RAGE::MemFile") ||
					Interpreter::Ruby::get_config()->is_on("RAGE::IniFile") ||
					Interpreter::Ruby::get_config()->is_on("RAGE::Music")
				   );
		}

		void BaseFileWrapper::load_ruby_class(void)
		{
			if (!BaseFileWrapper::rb_is_enabled) return;

			VALUE rage = rb_define_module("RAGE");

			rb_rageBaseFileClass = rb_define_class_under(rage, "BaseFile", rb_cObject);

			rb_define_method(rb_rageBaseFileClass, "isOpen?", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "eof?", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "size", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "open", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "read", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "write", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "writeByte", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "writeWord", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "writeDWord", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "writeFloat", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "writeDouble", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "readByte", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "readWord", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "readDWord", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "readFloat", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "readDouble", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "position=", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "position", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
			rb_define_method(rb_rageBaseFileClass, "close", RFUNC(BaseFileWrapper::rb_error_abstract), 0);
		}

		VALUE BaseFileWrapper::get_ruby_class(void)
		{
			return rb_rageBaseFileClass;
		}

		VALUE BaseFileWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rageBaseFileClass);
		}
	}
}