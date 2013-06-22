#include "Music_Wrapper.h"

namespace RAGE
{
	namespace Audio
	{
		VALUE rb_rage_MusicClass;

		VALUE MusicWrapper::rb_music_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, MusicWrapper::rb_music_free, new Music(AudioWrappers::get_mixer()));
		}

		void MusicWrapper::rb_music_free(void* ptr)
		{
			free((Music*)ptr);
		}

		VALUE MusicWrapper::rb_load(VALUE self, VALUE filename)
		{
			if (Interpreter::Ruby::file_exists(filename) < 0)
			{
				
				rb_raise(rb_eArgError, RAGE_RB_FILE_MISSING_ERROR, StringValueCStr(filename));
				return Qfalse;
			}
			
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->load(StringValueCStr(filename));

			return Qtrue;
		}

		VALUE MusicWrapper::rb_play(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->play();

			return Qnil;
		}

		VALUE MusicWrapper::rb_pause(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->pause();

			return Qnil;
		}

		VALUE MusicWrapper::rb_stop(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->stop();

			return Qnil;
		}

		VALUE MusicWrapper::rb_set_position(VALUE self, VALUE val)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->set_pos_secs(NUM2DBL(val));

			return Qnil;
		}

		VALUE MusicWrapper::rb_get_position(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			return DBL2NUM(aud->get_pos_secs());
		}

		VALUE MusicWrapper::rb_length(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			return DBL2NUM(aud->get_length_secs());
		}

		VALUE MusicWrapper::rb_set_speed(VALUE self, VALUE val)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->set_speed(NUM2DBL(val));

			return Qnil;
		}

		VALUE MusicWrapper::rb_get_speed(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			return DBL2NUM(aud->get_speed());
		}

		VALUE MusicWrapper::rb_set_volume(VALUE self, VALUE val)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->set_gain(NUM2DBL(val));

			return Qnil;
		}

		VALUE MusicWrapper::rb_get_volume(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			return DBL2NUM(aud->get_gain());
		}

		VALUE MusicWrapper::rb_set_pan(VALUE self, VALUE val)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->set_pan(NUM2DBL(val));

			return Qnil;
		}

		VALUE MusicWrapper::rb_get_pan(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			return DBL2NUM(aud->get_pan());
		}

		VALUE MusicWrapper::rb_set_loop(VALUE self, VALUE val)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			if (TYPE(val) == T_TRUE)
				aud->set_loop(true);
			else if (TYPE(val) == T_FALSE)
				aud->set_loop(false);

			return Qnil;
		}

		VALUE MusicWrapper::rb_get_loop(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			return aud->get_loop() ? Qtrue : Qfalse;
		}

		VALUE MusicWrapper::rb_disposed(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);
			
			return aud->is_disposed() ? Qtrue : Qfalse;
		}

		VALUE MusicWrapper::rb_dispose(VALUE self)
		{
			Music *aud;
			Data_Get_Struct(self, Music, aud);

			aud->dispose();

			return Qnil;
		}

		void MusicWrapper::load_ruby_class()
		{
			VALUE rage = rb_define_module("RAGE");
			rb_rage_MusicClass = rb_define_class_under(rage, "Music", rb_cObject);
			
			rb_define_alloc_func(rb_rage_MusicClass, MusicWrapper::rb_music_alloc);
			rb_define_method(rb_rage_MusicClass, "load", RFUNC(MusicWrapper::rb_load), 1);
			rb_define_method(rb_rage_MusicClass, "play", RFUNC(MusicWrapper::rb_play), 0);
			rb_define_method(rb_rage_MusicClass, "pause", RFUNC(MusicWrapper::rb_pause), 0);
			rb_define_method(rb_rage_MusicClass, "stop", RFUNC(MusicWrapper::rb_stop), 0);
			rb_define_method(rb_rage_MusicClass, "position=", RFUNC(MusicWrapper::rb_set_position), 1);
			rb_define_method(rb_rage_MusicClass, "position", RFUNC(MusicWrapper::rb_get_position), 0);
			rb_define_method(rb_rage_MusicClass, "length", RFUNC(MusicWrapper::rb_length), 0);
			rb_define_method(rb_rage_MusicClass, "speed=", RFUNC(MusicWrapper::rb_set_speed), 1);
			rb_define_method(rb_rage_MusicClass, "speed", RFUNC(MusicWrapper::rb_get_speed), 0);
			rb_define_method(rb_rage_MusicClass, "volume=", RFUNC(MusicWrapper::rb_set_volume), 1);
			rb_define_method(rb_rage_MusicClass, "volume", RFUNC(MusicWrapper::rb_get_volume), 0);
			rb_define_method(rb_rage_MusicClass, "pan=", RFUNC(MusicWrapper::rb_set_pan), 1);
			rb_define_method(rb_rage_MusicClass, "pan", RFUNC(MusicWrapper::rb_get_pan), 0);
			rb_define_method(rb_rage_MusicClass, "loop=", RFUNC(MusicWrapper::rb_set_loop), 1);
			rb_define_method(rb_rage_MusicClass, "loop", RFUNC(MusicWrapper::rb_get_loop), 0);
			rb_define_method(rb_rage_MusicClass, "disposed?", RFUNC(MusicWrapper::rb_disposed), 0);
			rb_define_method(rb_rage_MusicClass, "dispose", RFUNC(MusicWrapper::rb_dispose), 0);
		}

		VALUE MusicWrapper::get_ruby_class()
		{
			return rb_rage_MusicClass;
		}

		VALUE MusicWrapper::new_ruby_class_instance()
		{
			return rb_class_new_instance(0, NULL, rb_rage_MusicClass);
		}
	}
}