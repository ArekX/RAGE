#pragma once

#include "RubyInterpreter.h"
#include "Music.h"

namespace RAGE
{
	namespace Audio
	{

		class MusicWrapper
		{
		private:
			static VALUE rb_music_alloc(VALUE self);
			static void rb_music_free(void* ptr);
			static VALUE rb_load(VALUE self, VALUE filename);
			static VALUE rb_play(VALUE self);
			static VALUE rb_pause(VALUE self);
			static VALUE rb_stop(VALUE self);
			static VALUE rb_set_position(VALUE self, VALUE val);
			static VALUE rb_get_position(VALUE self);
			static VALUE rb_set_speed(VALUE self, VALUE val);
			static VALUE rb_get_speed(VALUE self);
			static VALUE rb_set_volume(VALUE self, VALUE val);
			static VALUE rb_get_volume(VALUE self);
			static VALUE rb_set_pan(VALUE self, VALUE val);
			static VALUE rb_get_pan(VALUE self);
			static VALUE rb_set_loop(VALUE self, VALUE val);
			static VALUE rb_get_loop(VALUE self);
			static VALUE rb_disposed(VALUE self);
			static VALUE rb_length(VALUE self);
			static VALUE rb_dispose(VALUE self);
		public:
			static void load_ruby_class();
			static VALUE get_ruby_class();
			static VALUE new_ruby_class_instance();
		};

	} // Audio
} // RAGE