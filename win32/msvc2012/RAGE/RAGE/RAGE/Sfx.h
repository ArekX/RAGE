#pragma once
#include "RubyInterpreter.h"
#include "Audio.h"

namespace RAGE
{
	namespace Audio
	{
		class Sfx :
			public Audio
		{
		private:
			ALLEGRO_SAMPLE *spl;
			ALLEGRO_SAMPLE_INSTANCE *inst;
		public:
			Sfx(ALLEGRO_MIXER *mx);
			~Sfx(void);
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
			unsigned int get_length();
			unsigned int get_pos();
			void set_pos(unsigned int pos);
			bool get_loop();
			void dispose();
		};
	}
}
