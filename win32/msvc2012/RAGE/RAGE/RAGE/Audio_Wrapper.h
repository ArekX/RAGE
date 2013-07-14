#pragma once
#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Audio
	{
		class AudioWrappers
		{
		public:
			static void init_audio(void);
			static ALLEGRO_MIXER* get_mixer(void);
			static void load_wrappers(void);
		};
	}
}
