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
			bool disposed;

			Bitmap(void);
			~Bitmap(void);
			void initialize(int width, int height);
			void initialize(char* filename);
			int get_width();
			int get_height();
			void draw(float x, float y, int flags);
			void draw_region(float sx, float sy, float sw, float sh, float dx, float dy, int flags);
			bool save(char* filename);
			void assign(Bitmap* src);
			bool is_disposed();
			void dispose();
			void recreate_video_bitmap();
		};
	}
}

