/*
Copyright (c) 2014 Aleksandar Panic

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

#include "Audio.h"
#include "rage_standard_headers.h"

#if RAGE_COMPILE_AUDIO && RAGE_COMPILE_SFX

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
			VALUE rage_file;
		public:
			Sfx(ALLEGRO_MIXER *mx);
			~Sfx(void);
			void load(char* filename);
			void load_rage_file(VALUE r_file, char *ext);
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
			void gc_mark(void);
			void dispose(void);
		};
	}
}

#endif