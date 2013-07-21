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