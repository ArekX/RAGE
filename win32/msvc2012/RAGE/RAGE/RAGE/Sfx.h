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
			unsigned int get_length(void);
			unsigned int get_pos(void);
			void set_pos(unsigned int pos);
			void dispose(void);
		};
	}
}
