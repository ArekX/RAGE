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

#include "Logic_Wrappers.h"
#include "Graphics_Wrappers.h"
#include "Bitmap.h"
#include "RubyInterpreter.h"

#include <random>

#if RAGE_COMPILE_LOGIC

namespace RAGE
{
	namespace Logic
	{
		std::random_device random_device;
		std::mt19937 mt_random_engine(random_device());
		std::uniform_real_distribution<double> mt_distributor_double(0.0, 1.0);

		bool LogicWrappers::collision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
		{
			return ((abs(2*(x1 - x2) + (w1-w2) ) < (w1+w2)) && (abs(2*(y1 - y2) + (h1-h2) ) < (h1+h2)));
		}

		#if RAGE_COMPILE_BITMAP
		VALUE LogicWrappers::rb_bitmap_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp1, VALUE x2, VALUE y2, VALUE bmp2)
		{
			Graphics::Bitmap *b1;
			Graphics::Bitmap *b2;

			Data_Get_Struct(bmp1, Graphics::Bitmap, b1);
			Data_Get_Struct(bmp2, Graphics::Bitmap, b2);

			return LogicWrappers::collision(NUM2DBL(x1), NUM2DBL(y1), b1->get_width(), b1->get_height(), NUM2DBL(x2), NUM2DBL(y2), b2->get_width(), b2->get_height()) ? Qtrue : Qfalse;
		}

		VALUE LogicWrappers::rb_bitmap_vs_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp, VALUE x2, VALUE y2, VALUE w2, VALUE h2)
		{
			Graphics::Bitmap *b1;

			Data_Get_Struct(bmp, Graphics::Bitmap, b1);

			return LogicWrappers::collision(NUM2DBL(x1), NUM2DBL(y1), b1->get_width(), b1->get_height(), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(w2), NUM2DBL(h2)) ? Qtrue : Qfalse;
		}
		#endif

		VALUE LogicWrappers::rb_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE w1, VALUE h1, VALUE x2, VALUE y2, VALUE w2, VALUE h2)
		{
			return LogicWrappers::collision(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(w1), NUM2DBL(h1), NUM2DBL(x2), NUM2DBL(y2), NUM2DBL(w2), NUM2DBL(h2)) ? Qtrue : Qfalse;  
		}

		VALUE LogicWrappers::rb_mt_rand(int argc, VALUE *args, VALUE self)
		{
			if (argc == 0) {
				return DBL2NUM(mt_distributor_double(mt_random_engine));
			}

			if (argc > 3) {
				rb_raise(rb_eArgError, "Invalid number of arguments.");
				return Qnil;
			}

			if (argc == 1) {
				mt_random_engine.seed(FIX2INT(args[0]));
				return DBL2NUM(mt_distributor_double(mt_random_engine));
			}

			int min = 0;
			int max = 0;

			if (argc == 2) {
				min = FIX2INT(args[0]);
				max = FIX2INT(args[1]);
			}


			if (argc == 3) {
				min = FIX2INT(args[0]);
				max = FIX2INT(args[1]);
				mt_random_engine.seed(FIX2INT(args[2]));
			}

			std::uniform_int_distribution<int> mt_distributor_int(min, max);
			return INT2FIX(mt_distributor_int(mt_random_engine));
		}

		void LogicWrappers::load_wrappers(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Logic")) return;

			VALUE rage = rb_define_module("RAGE");

			VALUE lg = rb_define_module_under(rage, "Logic");

			#if RAGE_COMPILE_BITMAP
			rb_define_module_function(lg, "bitmapVsBitmapCollision?", RFUNC(LogicWrappers::rb_bitmap_collision), 6);
			rb_define_module_function(lg, "bitmapVsBoxCollision?", RFUNC(LogicWrappers::rb_bitmap_vs_box_collision), 7);
			#endif

			rb_define_module_function(lg, "boxVsBoxCollision?", RFUNC(LogicWrappers::rb_box_collision), 8);
			rb_define_module_function(lg, "uniformRand", RFUNC(LogicWrappers::rb_mt_rand), -1);
		}
	}
}

#endif