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
		
		void Sfx::play()
		{ 
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_playing(inst, true);
		}
		
		void Sfx::pause()
		{ 
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_playing(inst, false);
		}
		
		void Sfx::stop()
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
		
		float Sfx::get_pan()
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_pan(inst);
		}
		
		float Sfx::get_speed()
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_speed(inst); 
		}
		
		float Sfx::get_gain()
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_gain(inst); 
		}
		
		unsigned int Sfx::get_length()
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_length(inst);
		}
		
		unsigned int Sfx::get_pos()
		{ 
			RAGE_CHECK_DISPOSED_RET(disposed, 0);
			
			return al_get_sample_instance_position(inst);
		}

		void Sfx::set_pos(unsigned int pos)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_set_sample_instance_position(inst, pos);
		}

		bool Sfx::get_loop()
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return is_loop; 
		}

		void Sfx::dispose()
		{ 
			RAGE_CHECK_DISPOSED(disposed);

			if (inst != NULL)
				al_destroy_sample_instance(inst);

			if (spl != NULL)
				al_destroy_sample(spl);

			disposed = true;
		}
	}
}