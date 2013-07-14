#pragma once
#include "RubyInterpreter.h"
#include "Audio.h"

namespace RAGE
{
	namespace Audio
	{
		class Music :
			public Audio
		{
		private:
			ALLEGRO_AUDIO_STREAM *audio;
		public:
			Music(ALLEGRO_MIXER *mx);
			~Music(void);
			void load(char* filename);
			void play(void);
			void pause(void);
			void stop(void);
			void set_pan(float pan);
			void set_speed(float speed);
			void set_gain(float gain);
			void set_loop(bool loop);
			float get_pan(void);
			float get_speed(void);
			float get_gain(void);
			double get_length_secs(void);
			double get_pos_secs(void);
			void set_pos_secs(double pos);
			void dispose(void);
		};
	}
}