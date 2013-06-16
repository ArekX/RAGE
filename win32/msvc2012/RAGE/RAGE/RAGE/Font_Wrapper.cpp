#include "Font_Wrapper.h"

namespace RAGE
{
	namespace Graphics
	{
		VALUE rb_rageFontClass;

		VALUE FontWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, FontWrapper::rb_destroy, new Font());
		}

		void FontWrapper::rb_destroy(void *value)
		{
			free((Font*)value);
		}
		
		VALUE FontWrapper::rb_load(VALUE self, VALUE font_name, VALUE size)
		{
			VALUE fname = rb_find_file(font_name);
			if (TYPE(fname) != T_STRING)
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(font_name));
				return Qfalse;
			}

			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			fnt->load_ttf_font(StringValueCStr(font_name), FIX2INT(size));

			return Qnil;
		}

		VALUE FontWrapper::rb_text_width(VALUE self, VALUE text)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			
			ALLEGRO_USTR *ustring = al_ustr_new(StringValueCStr(text));

			int width = fnt->get_text_width(ustring);

			al_ustr_free(ustring);

			return INT2FIX(width);
		}

		VALUE FontWrapper::rb_text_height(VALUE self)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			
			return INT2FIX(fnt->get_text_line_length());
		}

		VALUE FontWrapper::rb_dispose(VALUE self)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);

			if (fnt->is_set)
				DrawWrappers::reset_font();

			fnt->dispose();

			return Qnil;
		}

		VALUE FontWrapper::rb_disposed(VALUE self)
		{
			Font *fnt;
			Data_Get_Struct(self, Font, fnt);

			return fnt->disposed ? Qtrue : Qfalse;
		}

		VALUE FontWrapper::rb_load_stretch(VALUE self, VALUE font_name, VALUE w, VALUE h)
		{
			VALUE fname = rb_find_file(font_name);
			if (TYPE(fname) != T_STRING)
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(font_name));
				return Qfalse;
			}

			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			fnt->load_ttf_font_stretch(StringValueCStr(font_name), FIX2INT(w), FIX2INT(h));

			return Qnil;
		}

		VALUE FontWrapper::rb_load_flags(VALUE self, VALUE font_name, VALUE size, VALUE flags)
		{
			VALUE fname = rb_find_file(font_name);
			if (TYPE(fname) != T_STRING)
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(font_name));
				return Qfalse;
			}

			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			fnt->load_ttf_font_f(StringValueCStr(font_name), FIX2INT(size), FIX2INT(flags));

			return Qnil;
		}

		VALUE FontWrapper::rb_load_stretch_flags(VALUE self, VALUE font_name, VALUE w, VALUE h, VALUE flags)
		{
			VALUE fname = rb_find_file(font_name);
			if (TYPE(fname) != T_STRING)
			{
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(font_name));
				return Qfalse;
			}

			Font *fnt;
			Data_Get_Struct(self, Font, fnt);
			fnt->load_ttf_font_stretch_f(StringValueCStr(font_name), FIX2INT(w), FIX2INT(h), FIX2INT(flags));

			return Qnil;
		}

		void FontWrapper::load_ruby_class()
		{
			VALUE rage = rb_define_module("RAGE");

			rb_define_const(rage, "TTF_NO_KERNING", FIX2INT(ALLEGRO_TTF_NO_KERNING));
			rb_define_const(rage, "TTF_MONOCHROME", FIX2INT(ALLEGRO_TTF_MONOCHROME));
			rb_define_const(rage, "TTF_NO_AUTOHINT", FIX2INT(ALLEGRO_TTF_NO_AUTOHINT));

			rb_rageFontClass = rb_define_class_under(rage, "Font", rb_cObject);

			rb_define_alloc_func(rb_rageFontClass, FontWrapper::rb_alloc);

			rb_define_method(rb_rageFontClass, "load", RFUNC(FontWrapper::rb_load), 2);
			rb_define_method(rb_rageFontClass, "loadStretch", RFUNC(FontWrapper::rb_load_stretch), 3);
			rb_define_method(rb_rageFontClass, "loadFlags", RFUNC(FontWrapper::rb_load_flags), 3);
			rb_define_method(rb_rageFontClass, "loadStretchFlags", RFUNC(FontWrapper::rb_load_stretch_flags), 4);
			rb_define_method(rb_rageFontClass, "textWidth", RFUNC(FontWrapper::rb_text_width), 1);
			rb_define_method(rb_rageFontClass, "textHeight", RFUNC(FontWrapper::rb_text_height), 0);
			rb_define_method(rb_rageFontClass, "dispose", RFUNC(FontWrapper::rb_dispose), 0);
			rb_define_method(rb_rageFontClass, "disposed?", RFUNC(FontWrapper::rb_disposed), 0);
		}

		VALUE FontWrapper::get_ruby_class()
		{
			return rb_rageFontClass;
		}

		VALUE FontWrapper::new_ruby_class_instance()
		{
			return rb_class_new_instance(0, NULL, rb_rageFontClass);
		}
	}
}