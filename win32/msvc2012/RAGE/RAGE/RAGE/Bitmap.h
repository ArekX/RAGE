#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Graphics
	{
		class Bitmap
		{
		private:
			char* filename;
			bool disposed;
			int flags;
			float center_x;
			float center_y;
			float angle;
			float scale_x;
			float scale_y;
			ALLEGRO_COLOR tint;
		public:
			ALLEGRO_BITMAP* bitmap;

			Bitmap(void);
			~Bitmap(void);
			void initialize(int width, int height);
			void initialize_sub(ALLEGRO_BITMAP* parent, int x, int y, int width, int height);
			void initialize(char* filename);

			void lock();
			void lock_region(int x, int y, int w, int h);
			void unlock();

			void set_pixel(int x, int y, ALLEGRO_COLOR color);
			void set_blended_pixel(int x, int y, ALLEGRO_COLOR color);
			ALLEGRO_COLOR get_pixel(int x, int y);
			
			ALLEGRO_BITMAP* get_parent();
			bool is_sub();

			int get_width();
			int get_height();
			void draw(float x, float y);
			void draw_region(float sx, float sy, float sw, float sh, float dx, float dy);
			void set_flags(int sflags);
			int get_flags();

			void set_center_x(float cx);
			void set_center_y(float cy);
			float get_center_x();
			float get_center_y();

			void set_scale_x(float sx);
			void set_scale_y(float sy);
			float get_scale_x();
			float get_scale_y();

			void set_angle(float agl);
			float get_angle();

			void set_tint(ALLEGRO_COLOR cl);

			void set_tint_alpha(float alpha);
			float get_tint_alpha();

			void set_tint_red(float red);
			float get_tint_red();

			void set_tint_green(float green);
			float get_tint_green();

			void set_tint_blue(float blue);
			float get_tint_blue();

			bool save(char* filename);
			void assign(Bitmap* src);
			bool is_disposed();
			void dispose();
			void recreate_video_bitmap();
		};
	}
}

