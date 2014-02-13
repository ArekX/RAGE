/*
Copyright (c) 2014 Aleksandar Panic

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
#include "BaseFile.h"

#if RAGE_COMPILE_BITMAP

#define RAGE_BITMAP "RAGE::Bitmap"

namespace RAGE
{
	namespace Graphics
	{
		class Bitmap
		{
		private:
			int flags;
			float center_x;
			float center_y;
			float angle;
			float scale_x;
			float scale_y;
			ALLEGRO_COLOR tint;
			VALUE rage_file;
		public:
			ALLEGRO_BITMAP* bitmap;
			bool disposed;
			Bitmap(void);
			~Bitmap(void);
			void initialize(int width, int height);
			void initialize_sub(ALLEGRO_BITMAP* parent, int x, int y, int width, int height);
			void initialize(char* filename);
			void initialize(VALUE r_file, char *ext);

			void lock(void);
			void lock_region(int x, int y, int w, int h);
			void unlock(void);

			void set_pixel(int x, int y, ALLEGRO_COLOR color);
			void set_blended_pixel(int x, int y, ALLEGRO_COLOR color);
			ALLEGRO_COLOR get_pixel(int x, int y);
			
			ALLEGRO_BITMAP* get_parent(void);
			bool is_sub(void);

			int get_width(void);
			int get_height(void);
			void draw(float x, float y);
			void draw_region(float sx, float sy, float sw, float sh, float dx, float dy);
			void set_flags(int sflags);
			int get_flags(void);

			void set_center_x(float cx);
			void set_center_y(float cy);
			float get_center_x(void);
			float get_center_y(void);

			void set_scale_x(float sx);
			void set_scale_y(float sy);
			float get_scale_x(void);
			float get_scale_y(void);

			void set_angle(float agl);
			float get_angle(void);

			void set_tint(ALLEGRO_COLOR cl);

			void set_tint_alpha(float alpha);
			float get_tint_alpha(void);

			void set_tint_red(float red);
			float get_tint_red(void);

			void set_tint_green(float green);
			float get_tint_green(void);

			void set_tint_blue(float blue);
			float get_tint_blue(void);

			bool save(char* filename);
			bool save(Filesystem::BaseFile *fl, char *ext);
			void assign(Bitmap* src);
			void assign_parent(Bitmap* src);

			void gc_mark(void);

			void dispose(void);
			void recreate_video_bitmap(void);
		};
	}
}

#endif