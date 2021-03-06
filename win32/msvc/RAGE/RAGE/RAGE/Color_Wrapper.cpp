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

#include "Color_Wrapper.h"
#include "RubyInterpreter.h"
#include "Color.h"

#if RAGE_COMPILE_COLOR

namespace RAGE
{
	namespace Graphics
	{
		VALUE rb_rageColorClass;

		VALUE ColorWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, ColorWrapper::rb_destroy, new Color());
		}

		void ColorWrapper::rb_destroy(void *value)
		{
			delete value;
		}

		VALUE ColorWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			if (argc >= 1)
			{
				Color *clr;

				Data_Get_Struct(self, Color, clr);

				switch(argc)
				{
					case 1:
						clr->from_name(StringValueCStr(args[0]));
						break;
					case 3:
						clr->from_rgba(NUM2DBL(args[0]), NUM2DBL(args[1]), NUM2DBL(args[2]), 1);
						break;
					case 4:
						clr->from_rgba(NUM2DBL(args[0]), NUM2DBL(args[1]), NUM2DBL(args[2]), NUM2DBL(args[3]));
						break;
				}
			}

			return Qnil;
		}

		VALUE ColorWrapper::rb_from_rgba(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->from_rgba(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a));

			return Qnil;
		}

		VALUE ColorWrapper::rb_from_cmyk(VALUE self, VALUE c, VALUE m, VALUE y, VALUE k)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->from_cmyk(NUM2DBL(c), NUM2DBL(m), NUM2DBL(y), NUM2DBL(k));

			return Qnil;
		}

		VALUE ColorWrapper::rb_from_hsl(VALUE self, VALUE h, VALUE s, VALUE l)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->from_hsl(NUM2DBL(h), NUM2DBL(s), NUM2DBL(l));

			return Qnil;
		}

		VALUE ColorWrapper::rb_from_hsv(VALUE self, VALUE h, VALUE s, VALUE v)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->from_hsv(NUM2DBL(h), NUM2DBL(s), NUM2DBL(v));

			return Qnil;
		}

		VALUE ColorWrapper::rb_from_yuv(VALUE self, VALUE y, VALUE u, VALUE v)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->from_yuv(NUM2DBL(y), NUM2DBL(u), NUM2DBL(v));

			return Qnil;
		}

		VALUE ColorWrapper::rb_from_html(VALUE self, VALUE html)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->from_html(StringValueCStr(html));

			return Qnil;
		}

		VALUE ColorWrapper::rb_from_name(VALUE self, VALUE name)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->from_name(StringValueCStr(name));

			return Qnil;
		}

		VALUE ColorWrapper::rb_get_r(VALUE self)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			return DBL2NUM(clr->color.r);
		}

		VALUE ColorWrapper::rb_set_r(VALUE self, VALUE val)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->color.r = NUM2DBL(val);

			return Qnil;
		}

		VALUE ColorWrapper::rb_get_g(VALUE self)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			return DBL2NUM(clr->color.g);
		}

		VALUE ColorWrapper::rb_set_g(VALUE self, VALUE val)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->color.g = NUM2DBL(val);

			return Qnil;
		}

		VALUE ColorWrapper::rb_get_b(VALUE self)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			return DBL2NUM(clr->color.b);
		}

		VALUE ColorWrapper::rb_set_b(VALUE self, VALUE val)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->color.b = NUM2DBL(val);

			return Qnil;
		}

		VALUE ColorWrapper::rb_get_a(VALUE self)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			return DBL2NUM(clr->color.a);
		}

		VALUE ColorWrapper::rb_set_a(VALUE self, VALUE val)
		{
			Color *clr;

			Data_Get_Struct(self, Color, clr);

			clr->color.a = NUM2DBL(val);

			return Qnil;
		}

		VALUE ColorWrapper::rb_dispose(VALUE self)
		{
			Color *clr;
			Data_Get_Struct(self, Color, clr);

			clr->dispose();

			return Qnil;
		}

		VALUE ColorWrapper::rb_disposed(VALUE self)
		{
			Color *clr;
			Data_Get_Struct(self, Color, clr);

			return clr->disposed ? Qtrue : Qfalse;
		}

		void ColorWrapper::load_ruby_class(void)
		{
			if (!Interpreter::Ruby::get_config()->is_on("RAGE::Color")) return;

			VALUE rage = rb_define_module("RAGE");
			rb_rageColorClass = rb_define_class_under(rage, "Color", rb_cObject);

			rb_define_alloc_func(rb_rageColorClass, ColorWrapper::rb_alloc);

			rb_define_method(rb_rageColorClass, "initialize", RFUNC(ColorWrapper::rb_initialize), -1);
			rb_define_method(rb_rageColorClass, "setRGBA", RFUNC(ColorWrapper::rb_from_rgba), 4);
			rb_define_method(rb_rageColorClass, "setCMYK", RFUNC(ColorWrapper::rb_from_cmyk), 4);
			rb_define_method(rb_rageColorClass, "setHSL", RFUNC(ColorWrapper::rb_from_hsl), 3);
			rb_define_method(rb_rageColorClass, "setHSV", RFUNC(ColorWrapper::rb_from_hsv), 3);
			rb_define_method(rb_rageColorClass, "setYUV", RFUNC(ColorWrapper::rb_from_yuv), 3);
			rb_define_method(rb_rageColorClass, "setHTML", RFUNC(ColorWrapper::rb_from_html), 1);
			rb_define_method(rb_rageColorClass, "setName", RFUNC(ColorWrapper::rb_from_name), 1);
			rb_define_method(rb_rageColorClass, "r=", RFUNC(ColorWrapper::rb_set_r), 1);
			rb_define_method(rb_rageColorClass, "r", RFUNC(ColorWrapper::rb_get_r), 0);
			rb_define_method(rb_rageColorClass, "g=", RFUNC(ColorWrapper::rb_set_g), 1);
			rb_define_method(rb_rageColorClass, "g", RFUNC(ColorWrapper::rb_get_g), 0);
			rb_define_method(rb_rageColorClass, "b=", RFUNC(ColorWrapper::rb_set_b), 1);
			rb_define_method(rb_rageColorClass, "b", RFUNC(ColorWrapper::rb_get_b), 0);
			rb_define_method(rb_rageColorClass, "a=", RFUNC(ColorWrapper::rb_set_a), 1);
			rb_define_method(rb_rageColorClass, "a", RFUNC(ColorWrapper::rb_get_a), 0);
			rb_define_method(rb_rageColorClass, "dispose", RFUNC(ColorWrapper::rb_dispose), 0);
			rb_define_method(rb_rageColorClass, "disposed?", RFUNC(ColorWrapper::rb_disposed), 0);
		}

		VALUE ColorWrapper::get_ruby_class(void)
		{
			return rb_rageColorClass;
		}

		VALUE ColorWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, nullptr, rb_rageColorClass);
		}
	}
}

#endif