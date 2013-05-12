#include "Bitmap_Wrapper.h"

namespace RAGE
{
	namespace Graphics
	{
		VALUE BitmapWrapper::rb_create(VALUE self, VALUE width, VALUE height)
		{
			if ((TYPE(width) == T_FIXNUM) && (TYPE(height) == T_FIXNUM))
			{
				Bitmap *bmp;
				Data_Get_Struct(self, Bitmap, bmp);
				bmp->initialize(FIX2UINT(width), FIX2UINT(height));
			}
			else
				rb_throw("Width and Height values need to be Fixnum.", self);
			
			
			return self;
		}

		VALUE BitmapWrapper::rb_bitmap_alloc(VALUE self)
		{
			Bitmap *bit = new Bitmap();
			return Data_Wrap_Struct(self, 0, BitmapWrapper::rb_bitmap_destroy, bit);
		}

		void BitmapWrapper::rb_bitmap_destroy(void *value)
		{
			Bitmap *bit = (Bitmap*)value;
			free(bit);
		}

		VALUE BitmapWrapper::rb_get_width(VALUE self)
		{
			Bitmap* bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return INT2FIX(bmp->get_width());
		}

		VALUE BitmapWrapper::rb_get_height(VALUE self)
		{
			Bitmap* bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return INT2FIX(bmp->get_height());
		}


		VALUE BitmapWrapper::rb_load_f(VALUE self, VALUE filename)
		{
			if (TYPE(filename) != T_STRING)
			{
				rb_throw("Filename must be a string value.", self);
				return Qfalse;
			}

			VALUE fname = rb_find_file(filename);
			if (TYPE(fname) != T_STRING)
			{
				rb_throw_obj(rb_sprintf("File '%s' not found.", StringValueCStr(filename)), self);
				return Qfalse;
			}
			
			
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->initialize(StringValueCStr(fname));
			return Qtrue;
		}

		VALUE BitmapWrapper::rb_bitmap_draw1(VALUE self, VALUE x, VALUE y)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);
			bmp->draw(NUM2DBL(x), NUM2DBL(y), 0);
			 
			return Qtrue;
		}

		VALUE BitmapWrapper::rb_bitmap_draw2(VALUE self, VALUE x, VALUE y, VALUE flags)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);
			bmp->draw(NUM2DBL(x), NUM2DBL(y), FIX2INT(flags));
			 
			return Qtrue;
		}

		VALUE BitmapWrapper::rb_bitmap_draw_region1(VALUE self, VALUE sx, VALUE sy, VALUE sw, VALUE sh, VALUE dx, VALUE dy)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);
			bmp->draw_region(NUM2DBL(sx), NUM2DBL(sy), NUM2DBL(sw), NUM2DBL(sh), NUM2DBL(dx), NUM2DBL(dy), 0);
			 
			return Qtrue;
		}

		VALUE BitmapWrapper::rb_bitmap_draw_region2(VALUE self, VALUE sx, VALUE sy, VALUE sw, VALUE sh, VALUE dx, VALUE dy, 
				                            VALUE flags)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);
			bmp->draw_region(NUM2DBL(sx), NUM2DBL(sy), NUM2DBL(sw), NUM2DBL(sh), NUM2DBL(dx), NUM2DBL(dy), FIX2INT(flags));
			 
			return Qtrue;
		}

		
		void BitmapWrapper::LoadRubyClass()
		{
			VALUE rage = rb_define_module("RAGE");
			rb_define_const(rage, "BITMAP_FLIP_H", INT2FIX(1));
			rb_define_const(rage, "BITMAP_FLIP_V", INT2FIX(2));
			rb_define_const(rage, "BITMAP_FLIP_VH", INT2FIX(3));
			VALUE bitmap = rb_define_class_under(rage, "Bitmap", rb_cObject);
			
			rb_define_alloc_func(bitmap, BitmapWrapper::rb_bitmap_alloc);
			rb_define_method(bitmap, "load", RFUNC(BitmapWrapper::rb_load_f), 1);
			rb_define_method(bitmap, "create", RFUNC(BitmapWrapper::rb_create), 2);
			rb_define_method(bitmap, "width", RFUNC(BitmapWrapper::rb_get_width), 0);
			rb_define_method(bitmap, "height", RFUNC(BitmapWrapper::rb_get_height), 0);
			rb_define_method(bitmap, "draw", RFUNC(BitmapWrapper::rb_bitmap_draw1), 2);
			rb_define_method(bitmap, "drawOpt", RFUNC(BitmapWrapper::rb_bitmap_draw2), 3);
			rb_define_method(bitmap, "drawRegion", RFUNC(BitmapWrapper::rb_bitmap_draw_region1), 6);
			rb_define_method(bitmap, "drawRegionOpt", RFUNC(BitmapWrapper::rb_bitmap_draw_region2), 7);
		}
	}
}