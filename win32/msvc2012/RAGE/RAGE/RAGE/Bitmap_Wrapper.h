#pragma once
#include "RubyInterpreter.h"
#include "Bitmap.h"

namespace RAGE
{
	namespace Graphics
	{

		class BitmapWrapper
		{
		private:
			static VALUE rb_create(VALUE self, VALUE width, VALUE height);
			static VALUE rb_load_f(VALUE self, VALUE filename);
			static VALUE rb_get_width(VALUE self);
			static VALUE rb_get_height(VALUE self);
			static void rb_bitmap_destroy(void *value);
			static VALUE rb_bitmap_alloc(VALUE self);

			/* Screen drawing algos */
			static VALUE rb_bitmap_draw1(VALUE self, VALUE x, VALUE y);
			static VALUE rb_bitmap_draw2(VALUE self, VALUE x, VALUE y, VALUE flags);
			static VALUE rb_bitmap_draw_region1(VALUE self, VALUE sx, VALUE sy, VALUE sw, VALUE sh, VALUE dx, VALUE dy);
			static VALUE rb_bitmap_draw_region2(VALUE self, VALUE sx, VALUE sy, VALUE sw, VALUE sh, VALUE dx, VALUE dy, 
				                                VALUE flags);

		public:
			static void load_ruby_class();
		};
	}
}