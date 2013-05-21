#pragma once

#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Audio
	{

		class Audio
		{
		
		public:
			ALLEGRO_SAMPLE *audio;
			ALLEGRO_SAMPLE_ID audio_id;
			ALLEGRO_SAMPLE_INSTANCE *inst;
			ALLEGRO_AUDIO_STREAM *as;
			bool audio_stream;
			bool disposed;

			Audio(void);
			~Audio(void);

			void load_sound(char* filename);
			void load_stream(char* filename);
			void play();
			void stop();
			void dispose();
		};

	}
}