#include "Music.h"

namespace RAGE
{
	namespace Audio
	{

		Music::Music(ALLEGRO_MIXER *mx)
		//	: Audio(mx)
		{
			mixer = mx;
			disposed = false;
			audio = NULL;
		}

		Music::~Music(void)
		{
			if (!disposed)
				dispose();
		}

		void Music::load(char* filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			audio = al_load_audio_stream(filename, 4, 2048);
			
			al_set_audio_stream_playing(audio, false);

			al_attach_audio_stream_to_mixer(audio, mixer);
		}

		void Music::play()
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_playing(audio, true);
		}

		void Music::pause()
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_playing(audio, false);
		}

		void Music::stop()
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_playing(audio, false);
			al_rewind_audio_stream(audio);
		}

		void Music::set_pan(float pan)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_pan(audio, pan);
		}

		void Music::set_speed(float speed)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_speed(audio, speed);
		}

		void Music::set_gain(float gain)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_gain(audio, gain);
		}

		void Music::set_loop(bool loop)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (loop)
				al_set_audio_stream_playmode(audio, ALLEGRO_PLAYMODE_LOOP);
			else
				al_set_audio_stream_playmode(audio, ALLEGRO_PLAYMODE_ONCE);

			is_loop = loop;
		}

		float Music::get_pan()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_pan(audio);
		}

		float Music::get_speed()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_speed(audio);
		}

		float Music::get_gain()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_gain(audio);
		}

		bool Music::get_loop()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return is_loop;
		}

		double Music::get_length_secs()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_length_secs(audio);
		}

		double Music::get_pos_secs()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_position_secs(audio);
		}

		void Music::set_pos_secs(double pos)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_seek_audio_stream_secs(audio, pos);
		}

		void Music::dispose()
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (audio != NULL)
			{
				al_drain_audio_stream(audio);
				al_destroy_audio_stream(audio);
			}
			

			disposed = true;
		}
	}
}