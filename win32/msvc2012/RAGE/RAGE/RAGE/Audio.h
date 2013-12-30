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

#pragma once

#include "rage_standard_headers.h"

#if RAGE_COMPILE_AUDIO

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

#endif
