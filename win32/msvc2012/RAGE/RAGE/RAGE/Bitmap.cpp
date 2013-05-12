#include "Bitmap.h"


namespace RAGE
{
	namespace Graphics
	{

		Bitmap::Bitmap(void)
		{
			bitmap = NULL;
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

	}
}