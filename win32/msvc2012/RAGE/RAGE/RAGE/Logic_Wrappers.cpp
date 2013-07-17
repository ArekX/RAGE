#include "Logic_Wrappers.h"

namespace RAGE
{
	namespace Logic
	{

		bool LogicWrappers::collision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
		{
			return ((abs(2*(x1 - x2) + (w1-w2) ) < (w1+w2)) && (abs(2*(y1 - y2) + (h1-h2) ) < (h1+h2)));
		}

		VALUE LogicWrappers::rb_bitmap_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp1, VALUE x2, VALUE y2, VALUE bmp2)
		{
			Graphics::Bitmap *b1;
			Graphics::Bitmap *b2;

			Data_Get_Struct(bmp1, Graphics::Bitmap, b1);
			Data_Get_Struct(bmp2, Graphics::Bitmap, b2);

			return LogicWrappers::collision(NUM2DBL(x1), NUM2DBL(y1), b1->get_width(), b1->get_height(), NUM2DBL(x2), NUM2DBL(y2), b2->get_width(), b2->get_height()) ? Qtrue : Qfalse;
		}

		VALUE LogicWrappers::rb_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE w1, VALUE h1, VALUE x2, VALUE y2, VALUE w2, VALUE h2)
		{
			return LogicWrappers::collision(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(w1), NUM2DBL(h1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(w2), NUM2DBL(h2)) ? Qtrue : Qfalse;  
		}

		VALUE LogicWrappers::rb_bitmap_vs_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp, VALUE x2, VALUE y2, VALUE w2, VALUE h2)
		{
			Graphics::Bitmap *b1;

			Data_Get_Struct(bmp, Graphics::Bitmap, b1);

			return LogicWrappers::collision(NUM2DBL(x1), NUM2DBL(y1), b1->get_width(), b1->get_height(), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(w2), NUM2DBL(h2)) ? Qtrue : Qfalse;
		}

		void LogicWrappers::load_wrappers(void)
		{
			VALUE rage = rb_define_module("RAGE");

			VALUE lg = rb_define_module_under(rage, "Logic");

			rb_define_module_function(lg, "bitmapVsBitmapCollision?", RFUNC(LogicWrappers::rb_bitmap_collision), 6);
			rb_define_module_function(lg, "bitmapVsBoxCollision?", RFUNC(LogicWrappers::rb_bitmap_vs_box_collision), 7);
			rb_define_module_function(lg, "boxVsBoxCollision?", RFUNC(LogicWrappers::rb_box_collision), 8);
		}
	}
}
