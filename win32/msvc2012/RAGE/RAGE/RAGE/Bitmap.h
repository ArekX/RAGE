#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Graphics
	{
		class Bitmap
		{
		public:
			ALLEGRO_BITMAP* bitmap;
			char* filename;

			Bitmap(void);
			~Bitmap(void);
			void initialize(int width, int height);
			void initialize(char* filename);
			int get_width();
			int get_height();
			void draw(float x, float y, int flags);
			void draw_region(float sx, float sy, float sw, float sh, float dx, float dy, int flags);
		};
	}
}

