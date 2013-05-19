#include "Bitmap.h"


namespace RAGE
{
	namespace Graphics
	{

		Bitmap::Bitmap(void)
		{
			bitmap = NULL;
			al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
		}

		Bitmap::~Bitmap(void)
		{
			if (bitmap != NULL)
				al_destroy_bitmap(bitmap);
		}

		void Bitmap::initialize(int width, int height)
		{
			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			// FIXME: Set to memory bitmap if too big width.
			bitmap = al_create_bitmap(width, height);
			
		}

		void Bitmap::initialize(char* filename)
		{
			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);
			this->filename = filename;
			
			bitmap = al_load_bitmap(filename);
		}

		int Bitmap::get_width()
		{
			if (bitmap != NULL)
				return al_get_bitmap_width(bitmap);
			else
				return 0;
		}

		int Bitmap::get_height()
		{
			if (bitmap != NULL)
				return al_get_bitmap_height(bitmap);
			else
				return 0;
		}

		void Bitmap::draw(float x, float y, int flags)
		{
			al_draw_bitmap(bitmap, x, y, flags);
		}

		void Bitmap::draw_region(float sx, float sy, float sw, float sh, float dx, float dy, int flags)
		{
			al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, flags);
		}


		bool Bitmap::save(char* filename)
		{
			this->filename = filename;
			return al_save_bitmap(filename, bitmap);
		}

		void Bitmap::assign(Bitmap* src)
		{
			
			int oldflags = al_get_new_bitmap_flags();
			int oldformat = al_get_new_bitmap_format();
			ALLEGRO_BITMAP* oldtarget = al_get_target_bitmap();
			al_set_new_bitmap_flags(al_get_bitmap_flags(src->bitmap));
			al_set_new_bitmap_format(al_get_bitmap_format(src->bitmap));
			
			bitmap = al_create_bitmap(al_get_bitmap_width(src->bitmap), al_get_bitmap_height(src->bitmap));
			al_set_target_bitmap(bitmap);
			al_draw_bitmap(src->bitmap, 0, 0, 0);
			
			al_set_new_bitmap_flags(oldflags);
			al_set_new_bitmap_format(oldformat);
			al_set_target_bitmap(oldtarget);
		}

		void Bitmap::recreate_video_bitmap()
		{
			int oldflags = al_get_new_bitmap_flags();
			int oldformat = al_get_new_bitmap_format();
			
			al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
			al_set_new_bitmap_format(al_get_bitmap_format(bitmap));
			
			ALLEGRO_BITMAP *new_video = al_create_bitmap(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap));
			ALLEGRO_BITMAP* oldtarget = al_get_target_bitmap();
			al_set_target_bitmap(new_video);
			al_draw_bitmap(bitmap, 0, 0, 0);
			al_destroy_bitmap(bitmap);

			al_set_target_bitmap(oldtarget);
			al_set_new_bitmap_flags(oldflags);
			al_set_new_bitmap_format(oldformat);
			
			bitmap = new_video;
		}
	}
}