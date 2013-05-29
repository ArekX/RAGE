#pragma once
#include "RubyInterpreter.h"
#include "Bitmap.h"

#define RB_BITMAP_CLASS "RAGE::Bitmap"

namespace RAGE
{
	namespace Graphics
	{
		class BitmapWrapper
		{
		private:
			static VALUE rb_create(VALUE self, VALUE width, VALUE height);
			static VALUE rb_load_f(VALUE self, VALUE filename);
			static VALUE rb_save_f(VALUE self, VALUE filename);
			static VALUE rb_get_width(VALUE self);
			static VALUE rb_get_height(VALUE self);
			static VALUE rb_clone(VALUE self);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
			static void rb_bitmap_destroy(void *value);
			static VALUE rb_bitmap_alloc(VALUE self);

			static VALUE rb_set_scale_x(VALUE self, VALUE val);
			static VALUE rb_set_scale_y(VALUE self, VALUE val);
			static VALUE rb_set_center_x(VALUE self, VALUE val);
			static VALUE rb_set_center_y(VALUE self, VALUE val);
			static VALUE rb_set_angle(VALUE self, VALUE val);
			static VALUE rb_set_flags(VALUE self, VALUE val);
			static VALUE rb_set_tint(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a);

			static VALUE rb_get_scale_x(VALUE self);
			static VALUE rb_get_scale_y(VALUE self);
			static VALUE rb_get_center_x(VALUE self);
			static VALUE rb_get_center_y(VALUE self);
			static VALUE rb_get_angle(VALUE self);
			static VALUE rb_get_flags(VALUE self);

			/* Screen drawing algos */
			static VALUE rb_bitmap_draw(VALUE self, VALUE x, VALUE y);
			static VALUE rb_bitmap_draw_region(VALUE self, VALUE sx, VALUE sy, VALUE sw, VALUE sh, VALUE dx, VALUE dy);

		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};
	}
}