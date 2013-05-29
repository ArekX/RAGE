#pragma once
#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Audio
	{
		class AudioWrappers
		{
		public:
			static void init_audio();
			static ALLEGRO_MIXER* get_mixer();
			static void load_wrappers();
		};
	}
}
