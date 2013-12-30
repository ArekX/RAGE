/*
Copyright (c) 2013 Aleksandar Panic

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

#include "Music.h"
#include "BaseFile.h"

#if RAGE_COMPILE_AUDIO && RAGE_COMPILE_MUSIC

namespace RAGE
{
	namespace Audio
	{

		Music::Music(ALLEGRO_MIXER *mx)
		{
			mixer = mx;
			disposed = false;
			audio = NULL;
			rage_file = Qnil;
		}

		Music::~Music(void)
		{
			if (!disposed)
				dispose();
		}

		void Music::load(char* filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (audio != NULL)
			{
				al_drain_audio_stream(audio);
				al_destroy_audio_stream(audio);
			}

			rage_file = Qnil;

			audio = al_load_audio_stream(filename, 4, 2048);
			
			if (audio == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_MUSIC_LOAD_FAIL, filename);
				return;
			}

			al_set_audio_stream_playing(audio, false);

			al_attach_audio_stream_to_mixer(audio, mixer);
		}

		void Music::load_rage_file(VALUE r_file, const char *ext)
		{
			RAGE_CHECK_DISPOSED(disposed);

			Filesystem::BaseFile *fl;
			Data_Get_Struct(r_file, Filesystem::BaseFile, fl);

			if (fl->disposed)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_DISPOSED_RAGE_FILE_READ);
				return;
			}

			if (fl->file == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_FS_RAGE_FILE_NOT_LOADED);
				return;
			}

			rage_file = r_file;

			if (audio != NULL)
			{
				al_drain_audio_stream(audio);
				al_destroy_audio_stream(audio);
			}

			audio = al_load_audio_stream_f(fl->file, ext, 4, 2048);
			
			if (audio == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_MUSIC_LOAD_FAIL, RAGE_BASE_FILE);
				return;
			}

			al_set_audio_stream_playing(audio, false);

			al_attach_audio_stream_to_mixer(audio, mixer);
		}

		void Music::gc_mark(void)
		{
			if (!disposed && (rage_file != Qnil))
				rb_gc_mark(rage_file);
		}

		void Music::play(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_playing(audio, true);
		}

		void Music::pause(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_audio_stream_playing(audio, false);
		}

		void Music::stop(void)
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

		float Music::get_pan(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_pan(audio);
		}

		float Music::get_speed(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_speed(audio);
		}

		float Music::get_gain(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_gain(audio);
		}

		double Music::get_length_secs(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_length_secs(audio);
		}

		double Music::get_pos_secs(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return al_get_audio_stream_position_secs(audio);
		}

		void Music::set_pos_secs(double pos)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_seek_audio_stream_secs(audio, pos);
		}

		void Music::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (audio != NULL)
			{
				al_drain_audio_stream(audio);
				al_destroy_audio_stream(audio);
			}
			
			rage_file = Qnil;

			disposed = true;
		}
	}
}

#endif