#include "Bitmap_Wrapper.h"

namespace RAGE
{
	namespace Graphics
	{

		VALUE rb_rageBitmapClass;

		VALUE BitmapWrapper::rb_create(VALUE self, VALUE width, VALUE height)
		{
			if ((TYPE(width) == T_FIXNUM) && (TYPE(height) == T_FIXNUM))
			{
				Bitmap *bmp;
				Data_Get_Struct(self, Bitmap, bmp);
				bmp->initialize(FIX2UINT(width), FIX2UINT(height));
			}
			else
				rb_raise(rb_eTypeError, "Width and Height values need to be Fixnum.");
			
			
			return self;
		}

		VALUE BitmapWrapper::rb_bitmap_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, BitmapWrapper::rb_bitmap_destroy, new Bitmap());
		}

		void BitmapWrapper::rb_bitmap_destroy(void *value)
		{
			free((Bitmap*)value);
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

		VALUE BitmapWrapper::rb_clone(VALUE self)
		{
			VALUE ret_bmp = new_ruby_class_instance();
			Bitmap* current;
			Bitmap* clone;

			Data_Get_Struct(self, Bitmap, current);
			Data_Get_Struct(ret_bmp, Bitmap, clone);

			clone->assign(current);

			return ret_bmp;
		}

		VALUE BitmapWrapper::rb_load_f(VALUE self, VALUE filename)
		{
			VALUE fname = rb_find_file(filename);
			if (TYPE(fname) != T_STRING)
			{
				
				rb_raise(rb_eArgError, "File '%s' not found.", StringValueCStr(filename));
				return Qfalse;
			}
			
			
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->initialize(StringValueCStr(fname));
			return Qtrue;
		}

		VALUE BitmapWrapper::rb_save_f(VALUE self, VALUE filename)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			bool result = bmp->save(StringValueCStr(filename));
			return result ? Qtrue : Qfalse;
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
		
		VALUE BitmapWrapper::rb_dispose(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->dispose();

			return Qtrue;
		}

		VALUE BitmapWrapper::rb_disposed(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			return bmp->is_disposed() ? Qtrue : Qfalse;
		}

		void BitmapWrapper::load_ruby_class()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE g = rb_define_module_under(rage, "Graphics");
			rb_define_const(g, "BITMAP_FLIP_H", INT2FIX(1));
			rb_define_const(g, "BITMAP_FLIP_V", INT2FIX(2));
			rb_define_const(g, "BITMAP_FLIP_VH", INT2FIX(3));
			rb_rageBitmapClass = rb_define_class_under(rage, "Bitmap", rb_cObject);
			rb_define_alloc_func(rb_rageBitmapClass, BitmapWrapper::rb_bitmap_alloc);

			rb_define_method(rb_rageBitmapClass, "load", RFUNC(BitmapWrapper::rb_load_f), 1);
			rb_define_method(rb_rageBitmapClass, "save", RFUNC(BitmapWrapper::rb_save_f), 1);
			rb_define_method(rb_rageBitmapClass, "create", RFUNC(BitmapWrapper::rb_create), 2);
			rb_define_method(rb_rageBitmapClass, "width", RFUNC(BitmapWrapper::rb_get_width), 0);
			rb_define_method(rb_rageBitmapClass, "height", RFUNC(BitmapWrapper::rb_get_height), 0);
			rb_define_method(rb_rageBitmapClass, "clone", RFUNC(BitmapWrapper::rb_clone), 0);
			rb_define_method(rb_rageBitmapClass, "dispose", RFUNC(BitmapWrapper::rb_dispose), 0);
			rb_define_method(rb_rageBitmapClass, "disposed?", RFUNC(BitmapWrapper::rb_disposed), 0);
			rb_define_method(rb_rageBitmapClass, "draw", RFUNC(BitmapWrapper::rb_bitmap_draw1), 2);
			rb_define_method(rb_rageBitmapClass, "drawOpt", RFUNC(BitmapWrapper::rb_bitmap_draw2), 3);
			rb_define_method(rb_rageBitmapClass, "drawRegion", RFUNC(BitmapWrapper::rb_bitmap_draw_region1), 6);
			rb_define_method(rb_rageBitmapClass, "drawRegionOpt", RFUNC(BitmapWrapper::rb_bitmap_draw_region2), 7);
			// TODO: Finish Bitmap class, add tinting, stretch and other stuff.
		}

		VALUE BitmapWrapper::get_ruby_class()
		{
			return rb_rageBitmapClass;
		}

		VALUE BitmapWrapper::new_ruby_class_instance()
		{
			return rb_class_new_instance(0, NULL, rb_rageBitmapClass);
		}

	}
}