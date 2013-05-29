#include "Audio_Wrapper.h"

namespace RAGE
{
	namespace Audio
	{
		ALLEGRO_MIXER *mixer;
		ALLEGRO_VOICE *voice;

		
		void AudioWrappers::init_audio()
		{
			voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
			mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
			al_attach_mixer_to_voice(mixer, voice);
		}

		ALLEGRO_MIXER* AudioWrappers::get_mixer()
		{
			return mixer;
		}

		void AudioWrappers::load_wrappers()
		{
			// VALUE rage = rb_define_module("RAGE");
			
			// Interface for creating mixers, joining and other here, to be done...
		}
	}
}
