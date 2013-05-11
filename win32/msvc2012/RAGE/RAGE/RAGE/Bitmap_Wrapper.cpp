#include "Bitmap_Wrapper.h"

namespace RAGE
{
	namespace Graphics
	{
		VALUE BitmapWrapper::rb_initialize(VALUE self, VALUE width, VALUE height)
		{
			// todo checks if really fixnum
			ALLEGRO_BITMAP* bmp = al_create_bitmap(FIX2LONG(width), FIX2LONG(height));
			rb_define_class_variable(self, "width", width);
			rb_define_class_variable(self, "height", height);
			rb_define_class_variable(self, "bitmap", (VALUE)bmp);
			return self;
		}

		VALUE BitmapWrapper::rb_initialize_f(VALUE self, VALUE filename)
		{
			ALLEGRO_BITMAP* bmp = al_load_bitmap(StringValueCStr(filename));
			// TODO checks for stringvalue and existing file
			VALUE width = LONG2FIX(al_get_bitmap_width(bmp));
			VALUE height = LONG2FIX(al_get_bitmap_height(bmp));

			rb_define_class_variable(self, "width", width);
			rb_define_class_variable(self, "height", height);
			rb_define_class_variable(self, "bitmap", (VALUE)bmp);
			// rb_cv_get(self, "bitmap"); za dobijanje maybe?

			return self;
		}
		
		void BitmapWrapper::LoadRubyClass()
		{
			VALUE bitmap = rb_define_class("Bitmap", rb_cObject);
			rb_define_method(bitmap, "initialize", RFUNC(BitmapWrapper::rb_initialize), 2);
			rb_define_method(bitmap, "initialize", RFUNC(BitmapWrapper::rb_initialize_f), 1);
			
		}
	}
}