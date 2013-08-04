#pragma once
#include "RubyInterpreter.h"
#include "Font.h"

namespace RAGE
{
	namespace Graphics
	{
		class FontWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *value);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_load(VALUE self, VALUE font_name, VALUE size);
			static VALUE rb_load_stretch(VALUE self, VALUE font_name, VALUE w, VALUE h);
			static VALUE rb_load_flags(VALUE self, VALUE font_name, VALUE size, VALUE flags);
			static VALUE rb_load_stretch_flags(VALUE self, VALUE font_name, VALUE w, VALUE h, VALUE flags);
			static VALUE rb_text_width(VALUE self, VALUE text);
			static VALUE rb_text_height(VALUE self);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};
	}
}
