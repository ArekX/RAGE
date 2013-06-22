#include "Sfx_Wrapper.h"

namespace RAGE
{
	namespace Audio
	{
		VALUE rb_rage_SfxClass;

		VALUE SfxWrapper::rb_sfx_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, SfxWrapper::rb_sfx_free, new Sfx(AudioWrappers::get_mixer()));
		}

		void SfxWrapper::rb_sfx_free(void* ptr)
		{
			free((Sfx*)ptr);
		}

		VALUE SfxWrapper::rb_load(VALUE self, VALUE filename)
		{
			if (Interpreter::Ruby::file_exists(filename) < 0)
			{
				
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}
			
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->load(StringValueCStr(filename));

			return Qtrue;
		}

		VALUE SfxWrapper::rb_play(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->play();

			return Qnil;
		}

		VALUE SfxWrapper::rb_pause(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->pause();

			return Qnil;
		}

		VALUE SfxWrapper::rb_stop(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->stop();

			return Qnil;
		}

		VALUE SfxWrapper::rb_set_position(VALUE self, VALUE val)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->set_pos(FIX2UINT(val));

			return Qnil;
		}

		VALUE SfxWrapper::rb_get_position(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			return INT2FIX(aud->get_pos());
		}

		VALUE SfxWrapper::rb_length(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			return INT2FIX(aud->get_length());
		}

		VALUE SfxWrapper::rb_set_speed(VALUE self, VALUE val)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->set_speed(NUM2DBL(val));

			return Qnil;
		}

		VALUE SfxWrapper::rb_get_speed(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			return DBL2NUM(aud->get_speed());
		}

		VALUE SfxWrapper::rb_set_volume(VALUE self, VALUE val)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->set_gain(NUM2DBL(val));

			return Qnil;
		}

		VALUE SfxWrapper::rb_get_volume(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			return DBL2NUM(aud->get_gain());
		}

		VALUE SfxWrapper::rb_set_pan(VALUE self, VALUE val)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->set_pan(NUM2DBL(val));

			return Qnil;
		}

		VALUE SfxWrapper::rb_get_pan(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			return DBL2NUM(aud->get_pan());
		}

		VALUE SfxWrapper::rb_set_loop(VALUE self, VALUE val)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			if (TYPE(val) == T_TRUE)
				aud->set_loop(true);
			else if (TYPE(val) == T_FALSE)
				aud->set_loop(false);

			return Qnil;
		}

		VALUE SfxWrapper::rb_get_loop(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			return aud->get_loop() ? Qtrue : Qfalse;
		}

		VALUE SfxWrapper::rb_disposed(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);
			
			return aud->is_disposed() ? Qtrue : Qfalse;
		}

		VALUE SfxWrapper::rb_dispose(VALUE self)
		{
			Sfx *aud;
			Data_Get_Struct(self, Sfx, aud);

			aud->dispose();

			return Qnil;
		}

		void SfxWrapper::load_ruby_class()
		{
			VALUE rage = rb_define_module("RAGE");
			rb_rage_SfxClass = rb_define_class_under(rage, "Sfx", rb_cObject);
			
			rb_define_alloc_func(rb_rage_SfxClass, SfxWrapper::rb_sfx_alloc);

			rb_define_method(rb_rage_SfxClass, "load", RFUNC(SfxWrapper::rb_load), 1);
			rb_define_method(rb_rage_SfxClass, "play", RFUNC(SfxWrapper::rb_play), 0);
			rb_define_method(rb_rage_SfxClass, "pause", RFUNC(SfxWrapper::rb_pause), 0);
			rb_define_method(rb_rage_SfxClass, "stop", RFUNC(SfxWrapper::rb_stop), 0);
			rb_define_method(rb_rage_SfxClass, "position=", RFUNC(SfxWrapper::rb_set_position), 1);
			rb_define_method(rb_rage_SfxClass, "position", RFUNC(SfxWrapper::rb_get_position), 0);
			rb_define_method(rb_rage_SfxClass, "length", RFUNC(SfxWrapper::rb_length), 0);
			rb_define_method(rb_rage_SfxClass, "speed=", RFUNC(SfxWrapper::rb_set_speed), 1);
			rb_define_method(rb_rage_SfxClass, "speed", RFUNC(SfxWrapper::rb_get_speed), 0);
			rb_define_method(rb_rage_SfxClass, "volume=", RFUNC(SfxWrapper::rb_set_volume), 1);
			rb_define_method(rb_rage_SfxClass, "volume", RFUNC(SfxWrapper::rb_get_volume), 0);
			rb_define_method(rb_rage_SfxClass, "pan=", RFUNC(SfxWrapper::rb_set_pan), 1);
			rb_define_method(rb_rage_SfxClass, "pan", RFUNC(SfxWrapper::rb_get_pan), 0);
			rb_define_method(rb_rage_SfxClass, "loop=", RFUNC(SfxWrapper::rb_set_loop), 1);
			rb_define_method(rb_rage_SfxClass, "loop", RFUNC(SfxWrapper::rb_get_loop), 0);
			rb_define_method(rb_rage_SfxClass, "disposed?", RFUNC(SfxWrapper::rb_disposed), 0);
			rb_define_method(rb_rage_SfxClass, "dispose", RFUNC(SfxWrapper::rb_dispose), 0);
		}

		VALUE SfxWrapper::get_ruby_class()
		{
			return rb_rage_SfxClass;
		}

		VALUE SfxWrapper::new_ruby_class_instance()
		{
			return rb_class_new_instance(0, NULL, rb_rage_SfxClass);
		}
	}
}