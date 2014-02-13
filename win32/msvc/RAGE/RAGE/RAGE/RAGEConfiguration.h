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
#include "defines.h"
#include <ruby.h>

namespace RAGE
{
	class RAGEConfiguration
	{
	private:
		VALUE hash;
		bool is_default;
	public:
		RAGEConfiguration(VALUE conf_hash);
		bool is_on(char* name);
		void set_game_name(char* set_name);
		int get_screen_width(void);
		int get_screen_height(void);
		bool fullscreen_on(void);
		bool vsync_on(void);
		bool maximized_on(void);
		bool frameless_on(void);
		bool is_current_version(void);
		~RAGEConfiguration(void);
	};
}