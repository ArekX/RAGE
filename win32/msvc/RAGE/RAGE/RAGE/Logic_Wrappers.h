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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_LOGIC

namespace RAGE
{
	namespace Logic
	{
		class LogicWrappers
		{
		private:
			static VALUE rb_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE w1, VALUE h1, VALUE x2, VALUE y2, VALUE w2, VALUE h2);

			#if RAGE_COMPILE_BITMAP
			static VALUE rb_bitmap_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp1, VALUE x2, VALUE y2, VALUE bmp2);
			static VALUE rb_bitmap_vs_box_collision(VALUE self, VALUE x1, VALUE y1, VALUE bmp, VALUE x2, VALUE y2, VALUE w2, VALUE h2);
			#endif
		public:
			static bool collision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
			static void load_wrappers(void);
		};
	}
}

#endif