#include "VertexArray_Wrapper.h"

namespace RAGE
{
	namespace Graphics
	{
		VALUE rb_rageVertexArrayClass;

		VALUE VertexArrayWrapper::rb_allocate(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, VertexArrayWrapper::rb_destroy, new VertexArray());
		}

		void VertexArrayWrapper::rb_destroy(void* ptr)
		{
			free((VertexArray*)ptr);
		}

		VALUE VertexArrayWrapper::rb_initialize(int argc, VALUE *args, VALUE self)
		{
			VertexArray *va;

			Data_Get_Struct(self, VertexArray, va);

			if (argc == 0)
				va->initialize(0);
			else if (argc == 1)
				va->initialize(FIX2INT(args[0]));
			else
				rb_raise(rb_eArgError, RAGE_VAR_FUNCTION_TOO_MANY_ARGS);
		}

		VALUE VertexArrayWrapper::rb_change(VALUE self, VALUE index, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE color)
		{
			VertexArray *va;
			Color *cl;
			Data_Get_Struct(self, VertexArray, va);
			Data_Get_Struct(color, Color, cl);

			va->change_vertex(NUM2LL(index), NUM2DBL(x), NUM2DBL(y), NUM2DBL(z), NUM2DBL(u), NUM2DBL(v), cl->color);

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_change_c(VALUE self, VALUE index, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->change_vertex(NUM2LL(index), NUM2DBL(x), NUM2DBL(y), NUM2DBL(z), NUM2DBL(u), NUM2DBL(v), al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_push_c(VALUE self, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->add_vertex(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z), NUM2DBL(u), NUM2DBL(v), al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_push(VALUE self, VALUE x, VALUE y, VALUE z, VALUE u, VALUE v, VALUE color)
		{
			VertexArray *va;
			Color *cl;
			Data_Get_Struct(self, VertexArray, va);
			Data_Get_Struct(color, Color, cl);

			va->add_vertex(NUM2DBL(x), NUM2DBL(y), NUM2DBL(z), NUM2DBL(u), NUM2DBL(v), cl->color);

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_pop(VALUE self)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->remove_vertex(va->ary_len - 1);

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_remove(VALUE self, VALUE index)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->remove_vertex(NUM2LL(index));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_clear(VALUE self)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->clear_array();

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_size(VALUE self)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			return LL2NUM(va->ary_len);
		}

		VALUE VertexArrayWrapper::rb_get_x(VALUE self, VALUE index)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			return DBL2NUM(va->get_vertex_x(NUM2LL(index)));
		}

		VALUE VertexArrayWrapper::rb_get_y(VALUE self, VALUE index)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			return DBL2NUM(va->get_vertex_y(NUM2LL(index)));
		}

		VALUE VertexArrayWrapper::rb_get_z(VALUE self, VALUE index)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			return DBL2NUM(va->get_vertex_z(NUM2LL(index)));
		}

		VALUE VertexArrayWrapper::rb_get_u(VALUE self, VALUE index)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			return DBL2NUM(va->get_vertex_u(NUM2LL(index)));
		}

		VALUE VertexArrayWrapper::rb_get_v(VALUE self, VALUE index)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			return DBL2NUM(va->get_vertex_v(NUM2LL(index)));
		}

		VALUE VertexArrayWrapper::rb_get_color(VALUE self, VALUE index)
		{
			VertexArray *va;
			Color *cl;
			Data_Get_Struct(self, VertexArray, va);

			VALUE return_color = RAGE::Graphics::ColorWrapper::new_ruby_class_instance();

			Data_Get_Struct(return_color, Color, cl);

			cl->color = va->get_vertex_color(NUM2LL(index));

			return return_color;
		}

		VALUE VertexArrayWrapper::rb_get_color_to(VALUE self, VALUE index, VALUE color)
		{
			VertexArray *va;
			Color *cl;
			Data_Get_Struct(self, VertexArray, va);
			Data_Get_Struct(color, Color, cl);

			cl->color = va->get_vertex_color(NUM2LL(index));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_set_x(VALUE self, VALUE index, VALUE x)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->set_vertex_x(NUM2LL(index), NUM2DBL(x));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_set_y(VALUE self, VALUE index, VALUE y)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->set_vertex_y(NUM2LL(index), NUM2DBL(y));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_set_z(VALUE self, VALUE index, VALUE z)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->set_vertex_z(NUM2LL(index), NUM2DBL(z));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_set_u(VALUE self, VALUE index, VALUE u)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->set_vertex_u(NUM2LL(index), NUM2DBL(u));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_set_v(VALUE self, VALUE index, VALUE v)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->set_vertex_v(NUM2LL(index), NUM2DBL(v));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_set_color(VALUE self, VALUE index, VALUE color)
		{
			VertexArray *va;
			Color *cl;
			Data_Get_Struct(self, VertexArray, va);
			Data_Get_Struct(color, Color, cl);

			va->set_vertex_color(NUM2LL(index), cl->color);

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_set_color_c(VALUE self, VALUE index, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->set_vertex_color(NUM2LL(index), al_map_rgba_f(NUM2DBL(r), NUM2DBL(g), NUM2DBL(b), NUM2DBL(a)));

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_dispose(VALUE self)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			va->dispose();

			return Qnil;
		}

		VALUE VertexArrayWrapper::rb_is_disposed(VALUE self)
		{
			VertexArray *va;
			Data_Get_Struct(self, VertexArray, va);

			return (va->disposed) ? Qtrue : Qfalse;
		}

		void VertexArrayWrapper::load_ruby_class(void)
		{
			VALUE rage = rb_define_module("RAGE");

			rb_rageVertexArrayClass = rb_define_class_under(rage, "VertexArray", rb_cObject);

			rb_define_alloc_func(rb_rageVertexArrayClass, VertexArrayWrapper::rb_allocate);

			rb_define_method(rb_rageVertexArrayClass, "initialize", RFUNC(VertexArrayWrapper::rb_initialize), -1);
			rb_define_method(rb_rageVertexArrayClass, "push", RFUNC(VertexArrayWrapper::rb_push), 6);
			rb_define_method(rb_rageVertexArrayClass, "pushC", RFUNC(VertexArrayWrapper::rb_push_c), 9);
			rb_define_method(rb_rageVertexArrayClass, "pop", RFUNC(VertexArrayWrapper::rb_pop), 0);
			rb_define_method(rb_rageVertexArrayClass, "remove", RFUNC(VertexArrayWrapper::rb_remove), 1);
			rb_define_method(rb_rageVertexArrayClass, "clear", RFUNC(VertexArrayWrapper::rb_clear), 0);
			rb_define_method(rb_rageVertexArrayClass, "size", RFUNC(VertexArrayWrapper::rb_size), 0);
			rb_define_method(rb_rageVertexArrayClass, "change", RFUNC(VertexArrayWrapper::rb_change), 7);
			rb_define_method(rb_rageVertexArrayClass, "changeC", RFUNC(VertexArrayWrapper::rb_change_c), 10);
			rb_define_method(rb_rageVertexArrayClass, "getX", RFUNC(VertexArrayWrapper::rb_get_x), 1);
			rb_define_method(rb_rageVertexArrayClass, "getY", RFUNC(VertexArrayWrapper::rb_get_y), 1);
			rb_define_method(rb_rageVertexArrayClass, "getZ", RFUNC(VertexArrayWrapper::rb_get_z), 1);
			rb_define_method(rb_rageVertexArrayClass, "getU", RFUNC(VertexArrayWrapper::rb_get_u), 1);
			rb_define_method(rb_rageVertexArrayClass, "getV", RFUNC(VertexArrayWrapper::rb_get_v), 1);
			rb_define_method(rb_rageVertexArrayClass, "getColor", RFUNC(VertexArrayWrapper::rb_get_color), 1);
			rb_define_method(rb_rageVertexArrayClass, "getColorTo", RFUNC(VertexArrayWrapper::rb_get_color_to), 2);
			rb_define_method(rb_rageVertexArrayClass, "setX", RFUNC(VertexArrayWrapper::rb_set_x), 2);
			rb_define_method(rb_rageVertexArrayClass, "setY", RFUNC(VertexArrayWrapper::rb_set_y), 2);
			rb_define_method(rb_rageVertexArrayClass, "setZ", RFUNC(VertexArrayWrapper::rb_set_z), 2);
			rb_define_method(rb_rageVertexArrayClass, "setU", RFUNC(VertexArrayWrapper::rb_set_u), 2);
			rb_define_method(rb_rageVertexArrayClass, "setV", RFUNC(VertexArrayWrapper::rb_set_v), 2);
			rb_define_method(rb_rageVertexArrayClass, "setColor", RFUNC(VertexArrayWrapper::rb_set_color), 2);
			rb_define_method(rb_rageVertexArrayClass, "setColorC", RFUNC(VertexArrayWrapper::rb_set_color_c), 5);
			rb_define_method(rb_rageVertexArrayClass, "dispose", RFUNC(VertexArrayWrapper::rb_dispose), 0);
			rb_define_method(rb_rageVertexArrayClass, "disposed?", RFUNC(VertexArrayWrapper::rb_is_disposed), 0);
		}

		VALUE VertexArrayWrapper::get_ruby_class(void)
		{
			return rb_rageVertexArrayClass;
		}

		VALUE VertexArrayWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rageVertexArrayClass);
		}

	}
}
