#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Logic
	{
		class LogicWrappers
		{
		private:
			static VALUE rb_bitmap_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp1, VALUE x2, VALUE y2, VALUE bmp2);
			static VALUE rb_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE w1, VALUE h1, VALUE x2, VALUE y2, VALUE w2, VALUE h2);
			static VALUE rb_bitmap_vs_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp, VALUE x2, VALUE y2, VALUE w2, VALUE h2);
		public:
			static bool collision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
			static void load_wrappers(void);
		};
	}
}

