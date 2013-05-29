#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Audio
	{
		extern class Audio
		{
		protected:
			ALLEGRO_MIXER *mixer;
			bool disposed;
			bool is_loop;
		public:
			virtual void load(char* filename) = 0;
			virtual void play() = 0;
			virtual void pause() = 0;
			virtual void stop() = 0;
			virtual void set_pan(float pan) = 0;
			virtual void set_speed(float speed) = 0;
			virtual void set_gain(float gain) = 0;
			virtual void set_loop(bool loop) = 0;
			virtual float get_pan() = 0;
			virtual float get_speed() = 0;
			virtual float get_gain() = 0;
			virtual bool get_loop() = 0;
			virtual void dispose() = 0;
			virtual bool is_disposed() {
				return disposed;
			};
		};
	}
}