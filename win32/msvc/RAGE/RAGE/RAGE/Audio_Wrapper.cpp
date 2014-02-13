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

#include "Audio_Wrapper.h"
#include "RubyInterpreter.h"

#if RAGE_COMPILE_AUDIO

namespace RAGE
{
	namespace Audio
	{
		ALLEGRO_MIXER *mixer;
		ALLEGRO_VOICE *voice;

		bool AudioWrappers::is_enabled(void)
		{
			return (
					Interpreter::Ruby::get_config()->is_on("RAGE::Music") &&
					Interpreter::Ruby::get_config()->is_on("RAGE::Sfx")
				   );
		}

		void AudioWrappers::init_audio(void)
		{
			if (!AudioWrappers::is_enabled()) return;

			voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
			mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
			
			if (voice == NULL)
			{
				PRINT(RAGE_ERROR_CANNOT_CREATE_VOICE);
				return;
			}
			
			if (mixer == NULL)
			{
				PRINT(RAGE_ERROR_CANNOT_CREATE_MIXER);
				return;
			}
			
			al_attach_mixer_to_voice(mixer, voice);
		}

		void AudioWrappers::finalize_audio(void)
		{
			if (!AudioWrappers::is_enabled()) return;

			if (mixer != NULL)
			{
				al_detach_mixer(mixer);
				al_destroy_mixer(mixer);
			}

			if (voice != NULL)
				al_destroy_voice(voice);
		}

		ALLEGRO_MIXER* AudioWrappers::get_mixer(void)
		{
			return mixer;
		}

		void AudioWrappers::load_wrappers(void)
		{
			// VALUE rage = rb_define_module("RAGE");
			
			// Interface for creating mixers, joining and other here, to be done...
		}
	}
}

#endif