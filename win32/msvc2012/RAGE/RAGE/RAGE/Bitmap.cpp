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

#include "Bitmap.h"


namespace RAGE
{
	namespace Graphics
	{

		Bitmap::Bitmap(void)
		{
			rage_file = Qnil;
			bitmap = NULL;
			al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP | GraphicsWrappers::get_bitmap_flags());
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

			rage_file = Qnil;

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);

			bitmap = al_create_bitmap(width, height);

			if (bitmap == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_BITMAP_CREATE_FAIL);
				return;
			}
		}

		void Bitmap::initialize_sub(ALLEGRO_BITMAP* parent, int x, int y, int width, int height)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rage_file = Qnil;

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = al_create_sub_bitmap(parent, x, y, width, height);

			if (bitmap == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_SUBBITMAP_CREATE_FAIL);
				return;
			}
		}

		void Bitmap::initialize(char* filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rage_file = Qnil;

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = al_load_bitmap(filename);

			if (bitmap == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_BITMAP_LOAD_FAIL, filename);
				return;
			}
		}

		void Bitmap::initialize(VALUE r_file, char *ext)
		{
			RAGE_CHECK_DISPOSED(disposed);

			rage_file = Qnil;

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			Filesystem::BaseFile *fl;
			Data_Get_Struct(r_file, Filesystem::BaseFile, fl);

			if (fl->disposed)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_DISPOSED_RAGE_FILE_READ);
				return;
			}

			if (fl->file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_RAGE_FILE_NOT_LOADED);
				return;
			}

			rage_file = r_file;

			bitmap = al_load_bitmap_f(fl->file, ext);

			if (bitmap == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_BITMAP_LOAD_FAIL, RAGE_BASE_FILE);
				return;
			}
		}

		void Bitmap::lock(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, 0);
		}

		void Bitmap::lock_region(int x, int y, int w, int h)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_lock_bitmap_region(bitmap, x, y, w, h, ALLEGRO_PIXEL_FORMAT_ANY, 0);
		}

		void Bitmap::unlock(void)
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

		bool Bitmap::is_sub(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return al_is_sub_bitmap(bitmap);
		}

		ALLEGRO_BITMAP* Bitmap::get_parent(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, NULL);

			return al_get_parent_bitmap(bitmap);
		}

		ALLEGRO_COLOR Bitmap::get_pixel(int x, int y)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, al_map_rgb(0, 0, 0));

			al_get_pixel(bitmap, x, y);
		}

		int Bitmap::get_width(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			if (bitmap != NULL)
				return al_get_bitmap_width(bitmap);
			else
				return 0;
		}

		int Bitmap::get_height(void)
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

		float Bitmap::get_center_x(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return center_x;
		}

		float Bitmap::get_center_y(void)
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

		float Bitmap::get_scale_x(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return scale_x;
		}

		float Bitmap::get_scale_y(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return scale_y;
		}

		void Bitmap::set_angle(float agl)
		{
			RAGE_CHECK_DISPOSED(disposed);

			angle = agl;
		}

		float Bitmap::get_angle(void)
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

		float Bitmap::get_tint_alpha(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.a;
		}


		void Bitmap::set_tint_red(float red)
		{
			RAGE_CHECK_DISPOSED(disposed);

			tint.r = red;
		}

		float Bitmap::get_tint_red(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.r;
		}


		void Bitmap::set_tint_green(float green)
		{
			RAGE_CHECK_DISPOSED(disposed);

			tint.g = green;
		}

		float Bitmap::get_tint_green(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.g;
		}


		void Bitmap::set_tint_blue(float blue)
		{
			RAGE_CHECK_DISPOSED(disposed);

			tint.b = blue;
		}

		float Bitmap::get_tint_blue(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return tint.b;
		}


		int Bitmap::get_flags(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return flags;
		}


		bool Bitmap::save(char* filename)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return al_save_bitmap(filename, bitmap);
		}

		bool Bitmap::save(Filesystem::BaseFile *fl, char *ext)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return al_save_bitmap_f(fl->file, ext, bitmap);
		}

		void Bitmap::assign(Bitmap* src)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = al_clone_bitmap(src->bitmap);
		}

		void Bitmap::assign_parent(Bitmap* src)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = al_clone_bitmap(al_get_parent_bitmap(src->bitmap));
		}

		void Bitmap::gc_mark(void)
		{
			if (!disposed && (rage_file != Qnil))
				rb_gc_mark(rage_file);
		}

		void Bitmap::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (al_get_target_bitmap() == bitmap)
			{
				rb_raise(rb_eException, RAGE_ERROR_CANNOT_DISPOSE_DRAWING_TARGET);
				return;
			}
			else if (al_is_bitmap_locked(bitmap))
			{
				rb_raise(rb_eException, RAGE_ERROR_CANNOT_DISPOSE_LOCKED_BITMAP);
				return;
			}

			if (bitmap != NULL) 
				al_destroy_bitmap(bitmap);

			bitmap = NULL;
			rage_file = Qnil;

			disposed = true;
		}

		void Bitmap::recreate_video_bitmap(void)
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