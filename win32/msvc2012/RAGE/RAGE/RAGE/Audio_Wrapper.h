#pragma once
#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Audio
	{
		class AudioWrappers
		{
		private:
			static bool is_enabled(void);
		public:
			static void init_audio(void);
			static void finalize_audio(void);
			static ALLEGRO_MIXER* get_mixer(void);
			static void load_wrappers(void);
		};
	}
}
