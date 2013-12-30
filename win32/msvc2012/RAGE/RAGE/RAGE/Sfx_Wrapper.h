/*
Copyright (c) 2013 Aleksandar Panic

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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_AUDIO && RAGE_COMPILE_SFX

namespace RAGE
{
	namespace Audio
	{

		class SfxWrapper
		{
		private:
			static VALUE rb_sfx_alloc(VALUE self);
			static void rb_sfx_free(void* ptr);
			static void rb_mark(void *ptr);
			static VALUE rb_initialize(int argc, VALUE *args, VALUE self);
			static VALUE rb_load(int argc, VALUE *args, VALUE self);
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
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};

	}
}

#endif