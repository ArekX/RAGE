#include "Audio_Wrapper.h"

namespace RAGE
{
	namespace Audio
	{
		VALUE rb_rage_AudioClass;

		VALUE AudioWrapper::rb_audio_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, AudioWrapper::rb_audio_destroy, new Audio());
		}

		void AudioWrapper::rb_audio_destroy(void *value)
		{
			free((Audio*)value);
		}

		VALUE AudioWrapper::rb_load_f(VALUE self, VALUE filename, VALUE type)
		{
			VALUE fname = rb_find_file(filename);
			if (TYPE(fname) != T_STRING)
			{
				
				rb_raise(rb_eArgError, "File '%s' not found.", StringValueCStr(filename));
				return Qfalse;
			}
			
			Audio *aud;
			Data_Get_Struct(self, Audio, aud);

			switch(FIX2INT(type))
			{
				case RAGE_AUDIO_STREAM:
					aud->load_stream(StringValueCStr(fname));
					return Qtrue;
					
				case RAGE_AUDIO_SFX:
					aud->load_sound(StringValueCStr(fname));
					return Qtrue;

				default:
					rb_raise(rb_eArgError, "Unrecognized sound type.");
			}

			return Qfalse;
		}

		VALUE AudioWrapper::rb_play(VALUE self)
		{
			Audio *aud;
			Data_Get_Struct(self, Audio, aud);

			aud->play();

			return Qtrue;
		}

		VALUE AudioWrapper::rb_stop(VALUE self)
		{
			Audio *aud;
			Data_Get_Struct(self, Audio, aud);

			aud->stop();

			return Qtrue;
		}

		VALUE AudioWrapper::rb_dispose(VALUE self)
		{
			Audio *aud;
			Data_Get_Struct(self, Audio, aud);

			aud->dispose();

			return Qtrue;
		}

		void AudioWrapper::load_ruby_class()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE audio = rb_define_module_under(rage, "Sound");
			rb_define_const(audio, "STREAM", INT2FIX(RAGE_AUDIO_STREAM));
			rb_define_const(audio, "SFX", INT2FIX(RAGE_AUDIO_SFX));
			rb_rage_AudioClass = rb_define_class_under(rage, "Audio", rb_cObject);

			rb_define_alloc_func(rb_rage_AudioClass, AudioWrapper::rb_audio_alloc);

			rb_define_method(rb_rage_AudioClass, "load", RFUNC(AudioWrapper::rb_load_f), 2);
			rb_define_method(rb_rage_AudioClass, "play", RFUNC(AudioWrapper::rb_play), 0);
			rb_define_method(rb_rage_AudioClass, "stop", RFUNC(AudioWrapper::rb_stop), 0);
			rb_define_method(rb_rage_AudioClass, "dispose", RFUNC(AudioWrapper::rb_dispose), 0);
			// TODO: Finish Audio class, add position seeking, pause, other...
		}

		VALUE AudioWrapper::get_ruby_class()
		{
			return rb_rage_AudioClass;
		}

		VALUE AudioWrapper::new_ruby_class_instance()
		{
			return rb_class_new_instance(0, NULL, rb_rage_AudioClass);
		}
	}
}
