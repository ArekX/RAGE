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

#include "Sfx.h"

namespace RAGE
{
	namespace Audio
	{

		Sfx::Sfx(ALLEGRO_MIXER *mx)
		{
			mixer = mx;
			disposed = false;
			spl = NULL;
			rage_file = Qnil;
			inst = al_create_sample_instance(NULL);
			al_attach_sample_instance_to_mixer(inst, mixer);
		}


		Sfx::~Sfx(void)
		{
			if (!disposed)
				dispose();
		}

		void Sfx::load(char* filename)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (spl != NULL)
			{
				al_set_sample(inst, NULL);
				al_destroy_sample(spl);
				spl = NULL;
			}

			spl = al_load_sample(filename);

			if (spl == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_SFX_LOAD_FAIL, filename);
				return;
			}

			al_set_sample(inst, spl);
		}

		void Sfx::load_rage_file(VALUE r_file, char *ext)
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

			if (spl != NULL)
			{
				al_set_sample(inst, NULL);
				al_destroy_sample(spl);
				spl = NULL;
			}

			spl = al_load_sample_f(fl->file, ext);

			if (spl == NULL)
			{
				rb_raise(rb_eException, RAGE_ERROR_SFX_LOAD_FAIL, RAGE_BASE_FILE);
				return;
			}

			al_set_sample(inst, spl);
		}
		
		void Sfx::play(void)
		{ 
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_playing(inst, true);
		}
		
		void Sfx::pause(void)
		{ 
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_playing(inst, false);
		}
		
		void Sfx::stop(void)
		{ 
			RAGE_CHECK_DISPOSED(disposed);

			al_stop_sample_instance(inst);
		}

		void Sfx::set_pan(float pan)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_pan(inst, pan);
		}
		
		void Sfx::set_speed(float speed)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_speed(inst, speed);
		}
		
		void Sfx::set_gain(float gain)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_gain(inst, gain);
		}
		
		void Sfx::set_loop(bool loop)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (loop)
				al_set_sample_instance_playmode(inst, ALLEGRO_PLAYMODE_LOOP);
			else
				al_set_sample_instance_playmode(inst, ALLEGRO_PLAYMODE_ONCE);

			is_loop = loop;
		}
		
		float Sfx::get_pan(void)
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_pan(inst);
		}
		
		float Sfx::get_speed(void)
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_speed(inst); 
		}
		
		float Sfx::get_gain(void)
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_gain(inst); 
		}
		
		unsigned int Sfx::get_length(void)
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_length(inst);
		}
		
		unsigned int Sfx::get_pos(void)
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_position(inst);
		}

		void Sfx::set_pos(unsigned int pos)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_position(inst, pos);
		}

		void Sfx::gc_mark(void)
		{
			if (!disposed && (rage_file != Qnil))
				rb_gc_mark(rage_file);
		}

		void Sfx::dispose(void)
		{ 
			RAGE_CHECK_DISPOSED(disposed);

			if (inst != NULL)
				al_destroy_sample_instance(inst);

			if (spl != NULL)
				al_destroy_sample(spl);

			rage_file = Qnil;

			disposed = true;
		}
	}
}