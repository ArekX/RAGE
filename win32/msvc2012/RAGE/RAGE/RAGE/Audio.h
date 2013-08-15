#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Audio
	{
        class Audio
		{
		protected:
			ALLEGRO_MIXER *mixer;
		public:
			bool disposed;
			bool is_loop;
			virtual void load(char* filename) = 0;
			virtual void play(void) = 0;
			virtual void pause(void) = 0;
			virtual void stop(void) = 0;
			virtual void set_pan(float pan) = 0;
			virtual void set_speed(float speed) = 0;
			virtual void set_gain(float gain) = 0;
			virtual void set_loop(bool loop) = 0;
			virtual float get_pan(void) = 0;
			virtual float get_speed(void) = 0;
			virtual float get_gain(void) = 0;
			virtual void dispose(void) = 0;
		};
	}
}
