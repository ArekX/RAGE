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

#if RAGE_COMPILE_COLOR

namespace RAGE
{
	namespace Graphics
	{
		class Color
		{
		public:
			bool disposed;
			ALLEGRO_COLOR color;
			Color(void);
			void from_rgba(float r, float g, float b, float a);
			void from_cmyk(float c, float m, float y, float k);
			void from_hsl(float h, float s, float l);
			void from_hsv(float h, float s, float v);
			void from_yuv(float y, float u, float v);
			void from_html(char *html);
			void from_name(char *name);
			void dispose(void);
			~Color(void);
		};
	}
}

#endif
