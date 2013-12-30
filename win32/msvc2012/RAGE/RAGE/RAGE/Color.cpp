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

#include "Color.h"

#if RAGE_COMPILE_COLOR

namespace RAGE
{
	namespace Graphics
	{
		Color::Color(void)
		{
			disposed = false;
			color = al_map_rgb(0, 0, 0);
		}

		void Color::from_rgba(float r, float g, float b, float a)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			color = al_map_rgba_f(r, g, b, a);
		}

		void Color::from_cmyk(float c, float m, float y, float k)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			color = al_color_cmyk(c, m, y, k);
		}

		void Color::from_hsl(float h, float s, float l)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			color = al_color_hsl(h, s, l);
		}

		void Color::from_hsv(float h, float s, float v)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			color = al_color_hsv(h, s, v);
		}

		void Color::from_html(char *html)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			color = al_color_html(html);
		}

		void Color::from_name(char *name)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			color = al_color_name(name);
		}

		void Color::from_yuv(float y, float u, float v)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			color = al_color_yuv(y, u, v);
		}

		void Color::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			disposed = true;
		}

		Color::~Color(void)
		{
			if (!disposed)
				dispose();
		}
	}
}

#endif