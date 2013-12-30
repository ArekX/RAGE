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

#include "Font.h"
#include "Bitmap.h"

#if RAGE_COMPILE_FONT

namespace RAGE
{
	namespace Graphics
	{
		Font::Font(void)
		{
			disposed = false;
			is_set = false;
			rage_file = Qnil;
			font = al_create_builtin_font();
		}

		void Font::load_ttf_font(char *filename, int size, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			rage_file = Qnil;

			font = al_load_font(filename, size, flags);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, filename);
				return;
			}
		}

		void Font::load_ttf_font_stretch(char *filename, int w, int h, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			rage_file = Qnil;

			font = al_load_ttf_font_stretch(filename, w, h, flags);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, filename);
				return;
			}
		}

		void Font::load_ttf_font_rage_file(VALUE r_file, char *filename, int size, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			Filesystem::BaseFile *fl;
			Data_Get_Struct(r_file, Filesystem::BaseFile, fl);

			if (fl->disposed)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_DISPOSED_RAGE_FILE_READ);
				return;
			}

			if (fl->file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_RAGE_FILE_NOT_LOADED);
				return;
			}

			rage_file = r_file;

			font = al_load_ttf_font_f(fl->file, filename, size, flags);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, RAGE_BASE_FILE);
				return;
			}
		}

		void Font::gc_mark(void)
		{
			if (!disposed && (rage_file != Qnil))
				rb_gc_mark(rage_file);
		}

		void Font::load_ttf_font_stretch_rage_file(VALUE r_file, char *filename, int w, int h, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			Filesystem::BaseFile *fl;
			Data_Get_Struct(r_file, Filesystem::BaseFile, fl);

			if (fl->disposed)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_DISPOSED_RAGE_FILE_READ);
				return;
			}

			if (fl->file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_RAGE_FILE_NOT_LOADED);
				return;
			}

			rage_file = r_file;

			font = al_load_ttf_font_stretch_f(fl->file, filename, w, h, flags);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, RAGE_BASE_FILE);
				return;
			}
		}

		void Font::get_font_from_bitmap(ALLEGRO_BITMAP *bmp, int num_ranges, int *ranges)
		{
			RAGE_CHECK_DISPOSED(disposed);

			font = al_grab_font_from_bitmap(bmp, num_ranges, ranges);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, RAGE_BITMAP);
				return;
			}
		}

		int Font::get_text_width(ALLEGRO_USTR *text)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (font == NULL)
				return 0;

			return al_get_ustr_width(font, text);
		}

		int Font::get_text_line_length(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (font == NULL)
				return 0;

			return al_get_font_ascent(font);
		}

		void Font::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL)
				al_destroy_font(font);

			rage_file = Qnil;

			disposed = true;
		}

		Font::~Font(void)
		{
			if (!disposed)
				dispose();
		}
	}
}

#endif