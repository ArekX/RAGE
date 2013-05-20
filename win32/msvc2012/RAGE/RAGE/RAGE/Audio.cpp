#include "Audio.h"

namespace RAGE
{
	namespace Audio
	{

		Audio::Audio(void)
		{
			if  (!al_reserve_samples(1))
				rb_raise(rb_eException, "Could not reserve samples for audio.");

			audio = NULL;
			as = NULL;
			inst = al_create_sample_instance(NULL);
		}

		Audio::~Audio(void)
		{
			dispose();
		}

		void Audio::load_sound(char* filename)
		{
			if (audio != NULL)
			{
				al_set_sample(inst, NULL);
				al_destroy_sample(audio);
			}

			if (audio_stream)
				al_destroy_audio_stream(as);

			audio_stream = false;

			audio = al_load_sample(filename);
			al_set_sample(inst, audio);

			al_set_sample_instance_gain(inst, 0);
			al_set_sample_instance_pan(inst, 1);
			al_set_sample_instance_speed(inst, 1);
			al_set_sample_instance_playmode(inst, ALLEGRO_PLAYMODE_ONCE);
		}

		void Audio::load_stream(char* filename)
		{
			if (as != NULL)
				al_destroy_audio_stream(as);

			as = al_load_audio_stream(filename, 1024, 1);
			al_set_audio_stream_playing(as, false);
			audio_stream = true;
		}

		void Audio::play()
		{
			if (!audio_stream && (audio == NULL))
			{
				rb_raise(rb_eException, "Cannot play audio. No audio loaded.");
				return;
			}

			if (audio_stream && (as == NULL))
			{
				rb_raise(rb_eException, "Cannot play audio stream. No stream loaded.");
				return;
			}

			if (audio_stream)
				al_set_audio_stream_playing(as, true);
			else
			{
				if (!al_get_sample_instance_playing(inst))
					al_play_sample_instance(inst);
			}
		}

		void Audio::stop()
		{
			if (!audio_stream && (audio == NULL))
			{
				rb_raise(rb_eException, "Cannot stop audio. No audio loaded.");
				return;
			}

			if (audio_stream && (as == NULL))
			{
				rb_raise(rb_eException, "Cannot stop audio stream. No stream loaded.");
				return;
			}

			if (audio_stream)
				al_set_audio_stream_playing(as, false);
			else
			{
				if (al_get_sample_instance_playing(inst))
					al_stop_sample_instance(inst);
			}


		}

		void Audio::dispose()
		{
			if (audio_stream && (as != NULL))
				al_destroy_audio_stream(as);

			if (audio != NULL)
			{
				al_destroy_sample_instance(inst);
				al_destroy_sample(audio);
			}

			inst = NULL;
			audio = NULL;
			as = NULL;

		}

	}
}