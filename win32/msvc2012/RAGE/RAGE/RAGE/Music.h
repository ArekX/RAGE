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
			void play();
			void pause();
			void stop();
			void set_pan(float pan);
			void set_speed(float speed);
			void set_gain(float gain);
			void set_loop(bool loop);
			float get_pan();
			float get_speed();
			float get_gain();
			double get_length_secs();
			double get_pos_secs();
			void set_pos_secs(double pos);
			bool get_loop();
			void dispose();
		};
	}
}