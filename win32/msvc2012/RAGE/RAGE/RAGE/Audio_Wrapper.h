#pragma once
#include "RubyInterpreter.h"
#include "Audio.h"

#define RAGE_AUDIO_SFX 1
#define RAGE_AUDIO_STREAM 2

namespace RAGE
{
	namespace Audio
	{
		class AudioWrapper
		{
		public:
			static VALUE rb_audio_alloc(VALUE self);
			static void rb_audio_destroy(void *value);
			static VALUE rb_load_f(VALUE self, VALUE filename, VALUE type);
			static VALUE rb_play(VALUE self);
			static VALUE rb_stop(VALUE self);
			static VALUE rb_dispose(VALUE self);

			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};
	}
}
