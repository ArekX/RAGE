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

			scale_x = 1;
			scale_y = 1;
			center_x = 0;
			center_y = 0;
			angle = 0;
			flags = 0;
			tint = al_map_rgb(255, 255, 255);
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

			bitmap = al_create_bitmap(width, height);
		}

		void Bitmap::initialize_sub(ALLEGRO_BITMAP* parent, int x, int y, int width, int height)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = al_create_sub_bitmap(parent, x, y, width, height);
		}

		void Bitmap::initialize(char* filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			this->filename = filename;
			
			bitmap = al_load_bitmap(filename);
		}

		void Bitmap::lock()
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_lock_bitmap(bitmap, al_get_bitmap_format(bitmap), ALLEGRO_LOCK_READWRITE);
		}

		void Bitmap::lock_region(int x, int y, int w, int h)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_lock_bitmap_region(bitmap, x, y, w, h, al_get_bitmap_format(bitmap), ALLEGRO_LOCK_READWRITE);
		}

		void Bitmap::unlock()
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_unlock_bitmap(bitmap);
		}

		void Bitmap::set_pixel(int x, int y, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_put_pixel(x, y, color);
		}

		void Bitmap::set_blended_pixel(int x, int y, ALLEGRO_COLOR color)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_put_blended_pixel(x, y, color);
		}

		ALLEGRO_COLOR Bitmap::get_pixel(int x, int y)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, al_map_rgb(0, 0, 0));

			al_get_pixel(bitmap, x, y);
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

		void Bitmap::draw(float x, float y)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL)
				al_draw_tinted_scaled_rotated_bitmap(bitmap, tint, center_x, center_y, 
				                                     x, y, scale_x, scale_y, angle, flags);
		}

		void Bitmap::draw_region(float sx, float sy, float sw, float sh, float dx, float dy)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL)
				al_draw_tinted_scaled_rotated_bitmap_region(bitmap, sx, sy, sw, sh, tint, center_x, 
				                                            center_y, dx, dy, scale_x, scale_y, angle, flags);
		}

		void Bitmap::set_center_x(float cx)
		{
			RAGE_CHECK_DISPOSED(disposed);
			center_x = cx;
		}

		void Bitmap::set_center_y(float cy)
		{
			RAGE_CHECK_DISPOSED(disposed);
			center_y = cy;
		}

		float Bitmap::get_center_x()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return center_x;
		}

		float Bitmap::get_center_y()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return center_y;
		}

		void Bitmap::set_scale_x(float sx)
		{
			RAGE_CHECK_DISPOSED(disposed);

			scale_x = sx;
		}

		void Bitmap::set_scale_y(float sy)
		{
			RAGE_CHECK_DISPOSED(disposed);

			scale_y = sy;
		}

		float Bitmap::get_scale_x()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return scale_x;
		}

		float Bitmap::get_scale_y()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return scale_y;
		}

		void Bitmap::set_angle(float agl)
		{
			RAGE_CHECK_DISPOSED(disposed);

			angle = agl;
		}

		float Bitmap::get_angle()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return angle;
		}

		void Bitmap::set_flags(int sflags)
		{
			RAGE_CHECK_DISPOSED(disposed);

			flags = sflags;
		}

		void Bitmap::set_tint(ALLEGRO_COLOR cl)
		{
			RAGE_CHECK_DISPOSED(disposed);
			tint = cl;
		}

		void Bitmap::set_tint_alpha(float alpha)
		{
			RAGE_CHECK_DISPOSED(disposed);

			tint.a = alpha;
		}

		float Bitmap::get_tint_alpha()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.a;
		}


		void Bitmap::set_tint_red(float red)
		{
			RAGE_CHECK_DISPOSED(disposed);

			tint.r = red;
		}

		float Bitmap::get_tint_red()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.r;
		}


		void Bitmap::set_tint_green(float green)
		{
			RAGE_CHECK_DISPOSED(disposed);

			tint.g = green;
		}

		float Bitmap::get_tint_green()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.g;
		}


		void Bitmap::set_tint_blue(float blue)
		{
			RAGE_CHECK_DISPOSED(disposed);

			tint.b = blue;
		}

		float Bitmap::get_tint_blue()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.b;
		}


		int Bitmap::get_flags()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return flags;
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

		bool Bitmap::is_disposed()
		{
			return disposed;
		}

		void Bitmap::dispose()
		{
			RAGE_CHECK_DISPOSED(disposed);



			if (al_get_target_bitmap() == bitmap)
			{
				rb_raise(rb_eException, "Cannot dispose current drawing target bitmap.");
				return;
			}
			else if (al_is_bitmap_locked(bitmap))
			{
				rb_raise(rb_eException, "Cannot dispose locked bitmap. Unlock this bitmap first.");
				return;
			}

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = NULL;

			disposed = true;
		}

		void Bitmap::recreate_video_bitmap()
		{
			if (bitmap != NULL && !(al_get_target_bitmap() == bitmap))
			{
				
				al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
				al_set_new_bitmap_format(al_get_bitmap_format(bitmap));

				ALLEGRO_BITMAP *new_bitmap = al_clone_bitmap(bitmap);

				al_destroy_bitmap(bitmap);
				bitmap = new_bitmap;
			}
		}
	}
}