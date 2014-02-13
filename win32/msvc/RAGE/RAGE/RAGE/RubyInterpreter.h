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

/* Include configuration class */
#include "RAGEConfiguration.h"

namespace RAGE
{
	namespace Interpreter
	{
		class Ruby
		{
		private:
			static VALUE rb_require_protect(VALUE filename);
			
		public:
			static int file_exists(VALUE filename);
			static char* get_file_path(VALUE filename);
			static RAGEConfiguration* get_config(void);
			Ruby(int argc, char** argv);
			~Ruby(void);
		};
	}
}
