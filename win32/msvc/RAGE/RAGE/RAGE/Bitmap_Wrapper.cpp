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

#include "Bitmap_Wrapper.h"
#include "BaseFile_Wrapper.h"
#include "Bitmap.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_BITMAP

#if RAGE_COMPILE_COLOR
#include "Color.h"
#endif

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
				rb_raise(rb_eTypeError, RAGE_BITMAP_ERROR);
			
			
			return Qnil;
		}

		VALUE BitmapWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc >= 1)
			{
				Bitmap *bmp;
				Data_Get_Struct(self, Bitmap, bmp);

				if ((argc == 1) || RAGE_IS_SUPERCLASS_OF(args[0], Filesystem::BaseFileWrapper))
					BitmapWrapper::rb_load_f(argc, args, self);

				else if (argc == 2)
					bmp->initialize(FIX2UINT(args[0]), FIX2UINT(args[1]));
			}

			return Qnil;
		}

		VALUE BitmapWrapper::rb_bitmap_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, BitmapWrapper::rb_mark, BitmapWrapper::rb_bitmap_destroy, new Bitmap());
		}

		void BitmapWrapper::rb_bitmap_destroy(void *value)
		{
			delete value;
		}

		void BitmapWrapper::rb_mark(void *ptr)
		{
			((Bitmap*)ptr)->gc_mark();
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

		VALUE BitmapWrapper::rb_load_f(int argc, VALUE *args, VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			if (argc == 0)
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 2);
				return Qnil;
			}

			if (RAGE_IS_SUPERCLASS_OF(args[0], Filesystem::BaseFileWrapper))
			{
				if (argc != 2)
				{
					rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 2);
					return Qnil;
				}

				bmp->initialize(args[0], StringValueCStr(args[1]));
			}
			else
			{
				char *absolute_file = Interpreter::Ruby::get_file_path(args[0]);

				if (absolute_file == nullptr)
				{
				
					rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(args[0]));
					return Qfalse;
				}
			
				bmp->initialize(absolute_file);
			}
			return Qtrue;
		}

		VALUE BitmapWrapper::rb_save_f(int argc, VALUE *args, VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			bool result = false;

			if (argc == 0)
			{
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 2);
				return Qnil;
			}

			if (RAGE_IS_SUPERCLASS_OF(args[0], Filesystem::BaseFileWrapper))
			{
				if (argc != 2)
				{
					rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_INCOMP_ARGS, 1, 2);
					return Qnil;
				}

				Filesystem::BaseFile *fl;
				Data_Get_Struct(args[0], Filesystem::BaseFile, fl);

				result = bmp->save(fl, StringValueCStr(args[1]));
			}
			else
				result = bmp->save(StringValueCStr(args[0]));

			return result ? Qtrue : Qfalse;
		}

		VALUE BitmapWrapper::rb_bitmap_draw(VALUE self, VALUE x, VALUE y)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);
			bmp->draw(NUM2DBL(x), NUM2DBL(y));
			 
			return Qtrue;
		}


		VALUE BitmapWrapper::rb_bitmap_draw_region(VALUE self, VALUE sx, VALUE sy, VALUE sw, VALUE sh, VALUE dx, VALUE dy)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);
			bmp->draw_region(NUM2DBL(sx), NUM2DBL(sy), NUM2DBL(sw), NUM2DBL(sh), NUM2DBL(dx), NUM2DBL(dy));
			 
			return Qtrue;
		}

		VALUE BitmapWrapper::rb_bitmap_is_sub(VALUE self)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			if (bmp->is_sub())
				return Qtrue;
			else
				return Qfalse;
		}

		VALUE BitmapWrapper::rb_bitmap_get_parent(VALUE self)
		{
			Bitmap *bmp, *ret;
			
			Data_Get_Struct(self, Bitmap, bmp);

			VALUE ret_bmp = new_ruby_class_instance();
			
			Data_Get_Struct(ret_bmp, Bitmap, ret);
			
			ret->assign_parent(bmp);

			if (ret->bitmap == nullptr)
			{
				ret->dispose();
				
				rb_gc_register_address(&ret_bmp);

				return Qnil;
			}

			return ret_bmp;
		}

		VALUE BitmapWrapper::rb_set_scale_x(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_scale_x(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_scale_y(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_scale_y(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_center_x(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_center_x(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_center_y(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_center_y(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_angle(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_angle(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_flags(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_flags(FIX2INT(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_tint(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			Bitmap *bmp;
			
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_tint(al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_get_scale_x(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return DBL2NUM(bmp->get_scale_x());
		}

		VALUE BitmapWrapper::rb_get_scale_y(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return DBL2NUM(bmp->get_scale_y());
		}

		VALUE BitmapWrapper::rb_get_center_x(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return DBL2NUM(bmp->get_center_x());
		}

		VALUE BitmapWrapper::rb_get_center_y(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return DBL2NUM(bmp->get_center_y());
		}

		VALUE BitmapWrapper::rb_get_angle(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return DBL2NUM(bmp->get_angle());
		}

		VALUE BitmapWrapper::rb_get_flags(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);
			return INT2FIX(bmp->get_flags());
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

			return bmp->disposed ? Qtrue : Qfalse;
		}

		VALUE BitmapWrapper::rb_get_alpha(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			return DBL2NUM(bmp->get_tint_alpha());
		}

		VALUE BitmapWrapper::rb_get_red(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			return DBL2NUM(bmp->get_tint_red());
		}

		VALUE BitmapWrapper::rb_get_green(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			return DBL2NUM(bmp->get_tint_green());
		}

		VALUE BitmapWrapper::rb_get_blue(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			return DBL2NUM(bmp->get_tint_blue());
		}

		VALUE BitmapWrapper::rb_set_alpha(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_tint_alpha(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_red(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_tint_red(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_green(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_tint_green(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_blue(VALUE self, VALUE val)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_tint_blue(NUM2DBL(val));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_recreate(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->recreate_video_bitmap();

			return Qnil;
		}

		VALUE BitmapWrapper::rb_create_sub(VALUE self, VALUE parent, VALUE x, VALUE y, VALUE width, VALUE height)
		{
			Bitmap *bmp, *parent_bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			if (rb_class_of(parent) != rb_rageBitmapClass)
			{
				rb_raise(rb_eArgError, RAGE_BITMAP_PARENT_ERROR);
				return Qnil;
			}

			Data_Get_Struct(parent, Bitmap, parent_bmp);

			bmp->initialize_sub(parent_bmp->bitmap, FIX2INT(x), FIX2INT(y), FIX2INT(width), FIX2INT(height));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_bitmap_lock(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->lock();

			return Qnil;
		}

		VALUE BitmapWrapper::rb_bitmap_lock_region(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->lock_region(FIX2INT(x), FIX2INT(y), FIX2INT(w), FIX2INT(h));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_bitmap_unlock(VALUE self)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->unlock();

			return Qnil;
		}

		VALUE BitmapWrapper::rb_bitmap_get_pixel(VALUE self, VALUE color, VALUE x, VALUE y)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			Color *cl;
			Data_Get_Struct(color, Color, cl);

			cl->color = bmp->get_pixel(FIX2INT(x), FIX2INT(y));
			
			return Qnil;
		}

		#if RAGE_COMPILE_COLOR
		VALUE BitmapWrapper::rb_bitmap_set_pixel(VALUE self, VALUE x, VALUE y, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_pixel(FIX2INT(x), FIX2INT(y), al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));

			return Qnil;
		}
		#endif

		VALUE BitmapWrapper::rb_bitmap_set_blended_pixel(VALUE self, VALUE x, VALUE y, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			Bitmap *bmp;
			Data_Get_Struct(self, Bitmap, bmp);

			bmp->set_blended_pixel(FIX2INT(x), FIX2INT(y), al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));

			return Qnil;
		}

		VALUE BitmapWrapper::rb_set_tint_o(VALUE self, VALUE color)
		{
			Color *cl;
			Bitmap *bmp;

			Data_Get_Struct(self, Bitmap, bmp);
			Data_Get_Struct(color, Color, cl);

			bmp->set_tint(cl->color);

			return Qnil;
		}

		void BitmapWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Bitmap")) return;

			VALUE rage = rb_define_module("RAGE");
			VALUE g = rb_define_module_under(rage, "Graphics");

			rb_define_const(g, "FLIP_H", INT2FIX(ALLEGRO_FLIP_HORIZONTAL));
			rb_define_const(g, "FLIP_V", INT2FIX(ALLEGRO_FLIP_VERTICAL));

			rb_rageBitmapClass = rb_define_class_under(rage, "Bitmap", rb_cObject);
			rb_define_alloc_func(rb_rageBitmapClass, BitmapWrapper::rb_bitmap_alloc);

			rb_define_method(rb_rageBitmapClass, "initialize", RFUNC(BitmapWrapper::rb_initialize), -1);
			rb_define_method(rb_rageBitmapClass, "load", RFUNC(BitmapWrapper::rb_load_f), -1);
			rb_define_method(rb_rageBitmapClass, "save", RFUNC(BitmapWrapper::rb_save_f), -1);
			rb_define_method(rb_rageBitmapClass, "create", RFUNC(BitmapWrapper::rb_create), 2);
			rb_define_method(rb_rageBitmapClass, "createSub", RFUNC(BitmapWrapper::rb_create_sub), 5);
			rb_define_method(rb_rageBitmapClass, "recreate", RFUNC(BitmapWrapper::rb_recreate), 0);
			rb_define_method(rb_rageBitmapClass, "getParent", RFUNC(BitmapWrapper::rb_bitmap_get_parent), 0);
			rb_define_method(rb_rageBitmapClass, "isSub?", RFUNC(BitmapWrapper::rb_bitmap_is_sub), 0);
			rb_define_method(rb_rageBitmapClass, "width", RFUNC(BitmapWrapper::rb_get_width), 0);
			rb_define_method(rb_rageBitmapClass, "height", RFUNC(BitmapWrapper::rb_get_height), 0);
			rb_define_method(rb_rageBitmapClass, "centerX=", RFUNC(BitmapWrapper::rb_set_center_x), 1);
			rb_define_method(rb_rageBitmapClass, "centerY=", RFUNC(BitmapWrapper::rb_set_center_y), 1);
			rb_define_method(rb_rageBitmapClass, "scaleX=", RFUNC(BitmapWrapper::rb_set_scale_x), 1);
			rb_define_method(rb_rageBitmapClass, "scaleY=", RFUNC(BitmapWrapper::rb_set_scale_y), 1);
			rb_define_method(rb_rageBitmapClass, "angle=", RFUNC(BitmapWrapper::rb_set_angle), 1);
			rb_define_method(rb_rageBitmapClass, "flip=", RFUNC(BitmapWrapper::rb_set_flags), 1);
			rb_define_method(rb_rageBitmapClass, "centerX", RFUNC(BitmapWrapper::rb_get_center_x), 0);
			rb_define_method(rb_rageBitmapClass, "centerY", RFUNC(BitmapWrapper::rb_get_center_y), 0);
			rb_define_method(rb_rageBitmapClass, "scaleX", RFUNC(BitmapWrapper::rb_get_scale_x), 0);
			rb_define_method(rb_rageBitmapClass, "scaleY", RFUNC(BitmapWrapper::rb_get_scale_y), 0);
			rb_define_method(rb_rageBitmapClass, "angle", RFUNC(BitmapWrapper::rb_get_angle), 0);
			rb_define_method(rb_rageBitmapClass, "flip", RFUNC(BitmapWrapper::rb_get_flags), 0);
			rb_define_method(rb_rageBitmapClass, "setTint", RFUNC(BitmapWrapper::rb_set_tint), 4);
			rb_define_method(rb_rageBitmapClass, "setTintO", RFUNC(BitmapWrapper::rb_set_tint_o), 1);
			rb_define_method(rb_rageBitmapClass, "alpha=", RFUNC(BitmapWrapper::rb_set_alpha), 1);
			rb_define_method(rb_rageBitmapClass, "red=", RFUNC(BitmapWrapper::rb_set_red), 1);
			rb_define_method(rb_rageBitmapClass, "green=", RFUNC(BitmapWrapper::rb_set_green), 1);
			rb_define_method(rb_rageBitmapClass, "blue=", RFUNC(BitmapWrapper::rb_set_blue), 1);
			rb_define_method(rb_rageBitmapClass, "alpha", RFUNC(BitmapWrapper::rb_get_alpha), 0);
			rb_define_method(rb_rageBitmapClass, "red", RFUNC(BitmapWrapper::rb_get_red), 0);
			rb_define_method(rb_rageBitmapClass, "green", RFUNC(BitmapWrapper::rb_get_green), 0);
			rb_define_method(rb_rageBitmapClass, "blue", RFUNC(BitmapWrapper::rb_get_blue), 0);

			rb_define_method(rb_rageBitmapClass, "lock", RFUNC(BitmapWrapper::rb_bitmap_lock), 0);
			rb_define_method(rb_rageBitmapClass, "lockRegion", RFUNC(BitmapWrapper::rb_bitmap_lock_region), 4);
			rb_define_method(rb_rageBitmapClass, "unlock", RFUNC(BitmapWrapper::rb_bitmap_unlock), 0);
			rb_define_method(rb_rageBitmapClass, "setPixel", RFUNC(BitmapWrapper::rb_bitmap_set_pixel), 6);
			rb_define_method(rb_rageBitmapClass, "blendPixel", RFUNC(BitmapWrapper::rb_bitmap_set_blended_pixel), 6);
			#if RAGE_COMPILE_COLOR
			rb_define_method(rb_rageBitmapClass, "getPixel", RFUNC(BitmapWrapper::rb_bitmap_get_pixel), 3);
			#endif

			rb_define_method(rb_rageBitmapClass, "clone", RFUNC(BitmapWrapper::rb_clone), 0);
			rb_define_method(rb_rageBitmapClass, "dispose", RFUNC(BitmapWrapper::rb_dispose), 0);
			rb_define_method(rb_rageBitmapClass, "disposed?", RFUNC(BitmapWrapper::rb_disposed), 0);
			rb_define_method(rb_rageBitmapClass, "draw", RFUNC(BitmapWrapper::rb_bitmap_draw), 2);
			rb_define_method(rb_rageBitmapClass, "drawRegion", RFUNC(BitmapWrapper::rb_bitmap_draw_region), 6);
		}

		VALUE BitmapWrapper::get_ruby_class(void)
		{
			return rb_rageBitmapClass;
		}

		VALUE BitmapWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, nullptr, rb_rageBitmapClass);
		}

	}
}

#endif