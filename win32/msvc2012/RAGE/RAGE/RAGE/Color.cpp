#include "Color.h"

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
