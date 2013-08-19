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

