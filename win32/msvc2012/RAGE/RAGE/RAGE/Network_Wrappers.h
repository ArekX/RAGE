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

#if RAGE_COMPILE_NETWORK

namespace RAGE
{
	namespace Network
	{
		class NetworkWrappers
		{
		private:
			static VALUE rb_get_string(int argc, VALUE *args, VALUE self);
			static VALUE rb_post_string(int argc, VALUE *args, VALUE self);
			static VALUE rb_inet_ntop(VALUE self, VALUE ip_data, VALUE ip_type);
			static VALUE rb_inet_pton(VALUE self, VALUE ip, VALUE ip_type);
		public:
			static void load_wrappers(void);
		};
	}
}

#endif