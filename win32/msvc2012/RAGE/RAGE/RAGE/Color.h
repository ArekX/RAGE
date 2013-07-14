#pragma once

#include "RubyInterpreter.h"

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

