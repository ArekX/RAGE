#include "Font.h"

namespace RAGE
{
	namespace Graphics
	{
		Font::Font(void)
		{
			disposed = false;
			is_set = false;
			font = al_create_builtin_font();
		}

		void Font::load_ttf_font(char *filename, int size)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			font = al_load_font(filename, size, 0);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, filename);
				return;
			}
		}

		void Font::load_ttf_font_stretch(char *filename, int w, int h)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			font = al_load_ttf_font_stretch(filename, w, h, 0);
		}

		void Font::load_ttf_font_f(char *filename, int size, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			font = al_load_font(filename, size, flags);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, filename);
				return;
			}
		}

		void Font::load_ttf_font_stretch_f(char *filename, int w, int h, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (font != NULL) 
				al_destroy_font(font);

			font = al_load_ttf_font_stretch(filename, w, h, flags);

			if (font == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FONT_LOAD_FAIL, filename);
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

			disposed = true;
		}

		Font::~Font(void)
		{
		}
	}
}