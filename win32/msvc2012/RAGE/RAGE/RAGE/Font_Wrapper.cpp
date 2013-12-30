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

#include "Font_Wrapper.h"
#include "RubyInterpreter.h"
#include "BaseFile_Wrapper.h"
#include "Draw_Wrappers.h"
#include "Bitmap_Wrapper.h"
#include "Font.h"

#if RAGE_COMPILE_FONT

#if RAGE_COMPILE_BITMAP
#include "Bitmap.h"
#endif

namespace RAGE
{
	namespace Graphics
	{
		VALUE rb_rageFontClass;

		VALUE FontWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, FontWrapper::rb_mark, FontWrapper::rb_destroy, new Font());
		}

		void FontWrapper::rb_destroy(void *value)
		{
			delete value;
		}

		void FontWrapper::rb_mark(void *ptr)
		{
			((Font*)ptr)->gc_mark();
		}
		
		VALUE FontWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc > 1)
			{
				Font *fnt;
				Data_Get_Struct(self, Font, fnt);

				if (RAGE_IS_SUPERCLASS_OF(args[0], Filesystem::BaseFileWrapper))
				{
					if (argc == 3)
						fnt->load_ttf_font_rage_file(args[0], StringValueCStr(args[1]), FIX2INT(args[2]), 0);
					else if (argc == 4)
						fnt->load_ttf_font_stretch_rage_file(args[0], StringValueCStr(args[1]), FIX2INT(args[2]), FIX2INT(args[3]), 0);
					else
						rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 3, 4);
				}
				else if (RAGE_IS_CLASS_OF(args[0], BitmapWrapper))
				{
					if (argc == 2)
						FontWrapper::rb_get_from_bitmap(self, args[0], args[1]);
					else
						rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 2);
				}
				else
				{
					if (argc == 2)
						fnt->load_ttf_font(StringValueCStr(args[0]), FIX2INT(args[1]), 0);
					else if (argc == 3)
						fnt->load_ttf_font_stretch(StringValueCStr(args[0]), FIX2INT(args[1]), FIX2INT(args[2]), 0);
				}
				
			}

			return Qnil;
		}

		VALUE FontWrapper::rb_load(int argc, VALUE *args, VALUE self)
		{
			if (argc < 2)
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 4);
				return Qnil;
			}

			Font *fnt;
			Data_Get_Struct(self, Font, fnt);

			if (RAGE_IS_SUPERCLASS_OF(args[0], Filesystem::BaseFileWrapper))
			{
				if (argc == 3)
					fnt->load_ttf_font_rage_file(args[0], StringValueCStr(args[1]), FIX2INT(args[2]), 0);
				else if (argc == 4)
					fnt->load_ttf_font_rage_file(args[0], StringValueCStr(args[1]), FIX2INT(args[2]), FIX2INT(args[3]));
				else 
					rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 3, 4);
			}
			else
			{
				char *absolute_file = Interpreter::Ruby::get_file_path(args[0]);
				if (absolute_file == NULL)
				{
				
					rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(args[0]));
					return Qfalse;
				}

				if (argc == 2)
					fnt->load_ttf_font(absolute_file, FIX2INT(args[1]), 0);
				else if (argc == 3)
					fnt->load_ttf_font(absolute_file, FIX2INT(args[1]), FIX2INT(args[2]));
				else
					rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 2, 4);

			}

			return Qnil;
		}

		VALUE FontWrapper::rb_load_stretch(int argc, VALUE *args, VALUE self)
		{
			if (argc < 3)
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 3, 5);
				return Qnil;
			}

			Font *fnt;
			Data_Get_Struct(self, Font, fnt);

			if (RAGE_IS_SUPERCLASS_OF(args[0], Filesystem::BaseFileWrapper))
			{
				if (argc == 4)
					fnt->load_ttf_font_stretch_rage_file(args[0], StringValueCStr(args[1]), FIX2INT(args[2]), FIX2INT(args[3]), 0);
				else if (argc == 5)
					fnt->load_ttf_font_stretch_rage_file(args[0], StringValueCStr(args[1]), FIX2INT(args[2]), FIX2INT(args[3]), FIX2INT(args[4]));
				else 
					rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 4, 5);
			}
			else
			{
				char *absolute_file = Interpreter::Ruby::get_file_path(args[0]);
				if (absolute_file == NULL)
				{
				
					rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(args[0]));
					return Qfalse;
				}

				if (argc == 3)
					fnt->load_ttf_font_stretch(absolute_file, FIX2INT(args[1]), FIX2INT(args[2]), 0);
				else if (argc == 4)
					fnt->load_ttf_font_stretch(absolute_file, FIX2INT(args[1]), FIX2INT(args[2]), FIX2INT(args[3]));
				else
					rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 3, 4);

			}

			return Qnil;
		}

		VALUE FontWrapper::rb_text_width(VALUE self, VALUE text)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			
			ALLEGRO_USTR *ustring = al_ustr_new(StringValueCStr(text));

			int width = fnt->get_text_width(ustring);

			al_ustr_free(ustring);

			return INT2FIX(width);
		}

		VALUE FontWrapper::rb_text_height(VALUE self)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			
			return INT2FIX(fnt->get_text_line_length());
		}

		VALUE FontWrapper::rb_dispose(VALUE self)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);

			if (fnt->is_set)
				DrawWrappers::reset_font();

			fnt->dispose();

			return Qnil;
		}

		VALUE FontWrapper::rb_disposed(VALUE self)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);

			return fnt->disposed ? Qtrue : Qfalse;
		}

		#if RAGE_COMPILE_BITMAP
		VALUE FontWrapper::rb_get_from_bitmap(VALUE self, VALUE bitmap, VALUE ranges)
		{
			Bitmap *bmp;
			Font *fn;
			Data_Get_Struct(self, Font, fn);
			Data_Get_Struct(bitmap, Bitmap, bmp);

			if (TYPE(ranges) != T_ARRAY)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_ARG_NOT_ARY);
				return Qnil;
			}

			if ((RARRAY_LEN(ranges) & 1) != 0)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_GLYPH_RANGE_ERROR);
				return Qnil;
			}

			int max = RARRAY_LEN(ranges); 
			int *rngs = new int[max];

			for (int i = 0; i < max; i++)
				rngs[i] = FIX2INT(rb_ary_entry(ranges, i));

			fn->get_font_from_bitmap(bmp->bitmap, max / 2, rngs);

			delete[] rngs;
			
			return Qnil;
		}
		#endif

		void FontWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Font")) return;

			VALUE rage = rb_define_module("RAGE");

			rb_define_const(rage, "TTF_NO_KERNING", INT2FIX(ALLEGRO_TTF_NO_KERNING));
			rb_define_const(rage, "TTF_MONOCHROME", INT2FIX(ALLEGRO_TTF_MONOCHROME));
			rb_define_const(rage, "TTF_NO_AUTOHINT", INT2FIX(ALLEGRO_TTF_NO_AUTOHINT));

			rb_rageFontClass = rb_define_class_under(rage, "Font", rb_cObject);

			rb_define_alloc_func(rb_rageFontClass, FontWrapper::rb_alloc);

			rb_define_method(rb_rageFontClass, "initialize", RFUNC(FontWrapper::rb_initialize), -1);
			rb_define_method(rb_rageFontClass, "load", RFUNC(FontWrapper::rb_load), -1);
			rb_define_method(rb_rageFontClass, "loadStretch", RFUNC(FontWrapper::rb_load_stretch), -1);

			#if RAGE_COMPILE_BITMAP
			rb_define_method(rb_rageFontClass, "getFromBitmap", RFUNC(FontWrapper::rb_get_from_bitmap), 2);
			#endif

			// TODO: Add get ascent,descent,etc.

			rb_define_method(rb_rageFontClass, "textWidth", RFUNC(FontWrapper::rb_text_width), 1);
			rb_define_method(rb_rageFontClass, "textHeight", RFUNC(FontWrapper::rb_text_height), 0);
			rb_define_method(rb_rageFontClass, "dispose", RFUNC(FontWrapper::rb_dispose), 0);
			rb_define_method(rb_rageFontClass, "disposed?", RFUNC(FontWrapper::rb_disposed), 0);
		}

		VALUE FontWrapper::get_ruby_class(void)
		{
			return rb_rageFontClass;
		}

		VALUE FontWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rageFontClass);
		}
	}
}

#endif