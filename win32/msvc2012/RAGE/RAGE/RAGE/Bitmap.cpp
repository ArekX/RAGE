#include "Bitmap.h"


namespace RAGE
{
	namespace Graphics
	{

		Bitmap::Bitmap(void)
		{
			bitmap = NULL;
			al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
			disposed = false;
		}

		Bitmap::~Bitmap(void)
		{
			if (al_get_target_bitmap() == bitmap)
				bitmap = NULL;
			else
				dispose();
		}

		void Bitmap::initialize(int width, int height)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			// FIXME: Set to memory bitmap if too big width.
			bitmap = al_create_bitmap(width, height);
			
		}

		void Bitmap::initialize(char* filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			this->filename = filename;
			
			bitmap = al_load_bitmap(filename);
		}

		int Bitmap::get_width()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (bitmap != NULL)
				return al_get_bitmap_width(bitmap);
			else
				return 0;
		}

		int Bitmap::get_height()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (bitmap != NULL)
				return al_get_bitmap_height(bitmap);
			else
				return 0;
		}

		void Bitmap::draw(float x, float y, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL)
				al_draw_bitmap(bitmap, x, y, flags);
		}

		void Bitmap::draw_region(float sx, float sy, float sw, float sh, float dx, float dy, int flags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL)
				al_draw_bitmap_region(bitmap, sx, sy, sw, sh, dx, dy, flags);
		}


		bool Bitmap::save(char* filename)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			this->filename = filename;
			return al_save_bitmap(filename, bitmap);
		}

		void Bitmap::assign(Bitmap* src)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = al_clone_bitmap(src->bitmap);
		}

		void Bitmap::dispose()
		{
			if (al_get_target_bitmap() == bitmap)
			{
				rb_raise(rb_eException, "Cannot dispose current drawing target bitmap.");
				return;
			}

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = NULL;

			disposed = true;
		}

		void Bitmap::recreate_video_bitmap()
		{
			if (bitmap != NULL)
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
}