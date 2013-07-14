#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Graphics
	{
		class Font
		{
		public:
			bool disposed;
			bool is_set;
			ALLEGRO_FONT *font;
			Font(void);
			void load_ttf_font(char *filename, int size);
			void load_ttf_font_stretch(char *filename, int w, int h);
			void load_ttf_font_f(char *filename, int size, int flags);
			void load_ttf_font_stretch_f(char *filename, int w, int h, int flags);
			int get_text_width(ALLEGRO_USTR *text);
			int get_text_line_length(void);
			void dispose(void);
			~Font(void);
		};
	}
}

