#include "ParticleEngine.h"

namespace RAGE
{
	namespace Graphics
	{
		ParticleEngine::ParticleEngine(void)
		{
			disposed = false;
		}

		void ParticleEngine::initialize(ALLEGRO_BITMAP* particle, int emitter_count, float emitter_duration, float emitter_direction, float emitter_spread, EmitterType type)
		{
			particle_tex = particle;
			particles = (Particle*)al_malloc(sizeof(Particle) * emitter_count);
			particles_len = emitter_count;
		}

		void ParticleEngine::update(float dt) { }
		void ParticleEngine::draw(){ }
		void ParticleEngine::draw(float x, float y){ }
		void ParticleEngine::increase_particles(int amount){ }
		void ParticleEngine::decrease_particles(int amount){ }
		void ParticleEngine::calculate_next_particle(float* last_particle_x, float* last_particle_y){ }

		void ParticleEngine::set_next_frame_speed(EmitterFrameType type, uint64_t index, float speed)
		{
			RAGE_CHECK_DISPOSED(disposed);

			switch (type)
			{
				case EmitterFrameType::Angle:
					if (index < angle_frames_len)
						angle_frames[index].next_frame_speed = speed;
					break;
				case EmitterFrameType::AngleVelocity:
					if (index < angle_velocity_frames_len)
						angle_velocity_frames[index].next_frame_speed = speed;
					break;
				case EmitterFrameType::Velocity:
					if (index < velocity_frames_len)
						velocity_frames[index].next_frame_speed = speed;
					break;
				case EmitterFrameType::Color:
					if (index < color_frames_len)
						color_frames[index].next_frame_speed = speed;
					break;
				case EmitterFrameType::ScaleX:
					if (index < scale_x_frames_len)
						scale_x_frames[index].next_frame_speed = speed;
					break;
				case EmitterFrameType::ScaleY:
					if (index < scale_y_frames_len)
						scale_y_frames[index].next_frame_speed = speed;
					break;
			}
		} 
		
		float ParticleEngine::get_next_frame_speed(EmitterFrameType type, uint64_t index)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			switch (type)
			{
				case EmitterFrameType::Angle:
					if (index < angle_frames_len)
						return angle_frames[index].next_frame_speed;
				case EmitterFrameType::AngleVelocity:
					if (index < angle_velocity_frames_len)
						return angle_velocity_frames[index].next_frame_speed;
				case EmitterFrameType::Velocity:
					if (index < velocity_frames_len)
						return velocity_frames[index].next_frame_speed;
				case EmitterFrameType::Color:
					if (index < color_frames_len)
						return color_frames[index].next_frame_speed;
				case EmitterFrameType::ScaleX:
					if (index < scale_x_frames_len)
						return scale_x_frames[index].next_frame_speed;
				case EmitterFrameType::ScaleY:
					if (index < scale_y_frames_len)
						return scale_y_frames[index].next_frame_speed;
			}

			return 0;
		}

		void ParticleEngine::set_angle_frame(uint64_t index, float angle){ }
		void ParticleEngine::set_angle_velocity_frame(uint64_t index, float angle_velocity){ }
		void ParticleEngine::set_velocity_frame(uint64_t index, float velocity){ }
		void ParticleEngine::set_scale_x_frame(uint64_t index, float scale_x){ }
		void ParticleEngine::set_scale_y_frame(uint64_t index, float scale_y){ }
		void ParticleEngine::set_color_frame(uint64_t index, ALLEGRO_COLOR color){ }

		float ParticleEngine::get_angle_frame(uint64_t index){ }
		float ParticleEngine::get_angle_velocity_frame(uint64_t index){ }
		float ParticleEngine::get_velocity_frame(uint64_t index){ }
		float ParticleEngine::get_scale_x_frame(uint64_t index){ }
		float ParticleEngine::get_scale_y_frame(uint64_t index){ }
		ALLEGRO_COLOR ParticleEngine::get_color_frame(uint64_t index){ }

		void ParticleEngine::add_angle_frame(float angle, float next_frame_speed){ }
		void ParticleEngine::add_angle_velocity_frame(float angle_velocity, float next_frame_speed){ }
		void ParticleEngine::add_velocity_frame(float velocity, float next_frame_speed){ }
		void ParticleEngine::add_scale_x_frame(float scale_x, float next_frame_speed){ }
		void ParticleEngine::add_scale_y_frame(float scale_y, float next_frame_speed){ }

		void ParticleEngine::add_color_frame(ALLEGRO_COLOR color, float next_frame_speed)
		{
			RAGE_CHECK_DISPOSED(disposed);

			ADD_TO_FRAME(color_frames, color_frames_len, EmitterColorFrame, color, color, next_frame_speed);
		}

		void ParticleEngine::remove_angle_frame(uint64_t index) 
		{
			RAGE_CHECK_DISPOSED(disposed);

			REMOVE_FROM_ARY(angle_frames, EmitterAngleFrame, angle_frames_len, index);
		}

		void ParticleEngine::remove_angle_velocity_frame(uint64_t index) 
		{
			RAGE_CHECK_DISPOSED(disposed);

			REMOVE_FROM_ARY(angle_velocity_frames, EmitterAngleVelocityFrame, angle_velocity_frames_len, index);
		}

		void ParticleEngine::remove_velocity_frame(uint64_t index) 
		{
			RAGE_CHECK_DISPOSED(disposed);

			REMOVE_FROM_ARY(velocity_frames, EmitterVelocityFrame, velocity_frames_len, index);
		}

		void ParticleEngine::remove_scale_x_frame(uint64_t index)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			REMOVE_FROM_ARY(scale_x_frames, EmitterScaleXFrame, scale_x_frames_len, index);
		}

		void ParticleEngine::remove_scale_y_frame(uint64_t index) 
		{
			RAGE_CHECK_DISPOSED(disposed);

			REMOVE_FROM_ARY(scale_y_frames, EmitterScaleYFrame, scale_y_frames_len, index);
		}

		void ParticleEngine::remove_color_frame(uint64_t index) 
		{
			RAGE_CHECK_DISPOSED(disposed);

			REMOVE_FROM_ARY(color_frames, EmitterColorFrame, color_frames_len, index);
		}

		void ParticleEngine::clear_angle_frames(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_free(angle_frames);

			angle_frames_len = 0;
		}
		void ParticleEngine::clear_angle_velocity_frames(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_free(angle_velocity_frames);

			angle_velocity_frames_len = 0;
		}

		void ParticleEngine::clear_velocity_frames(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_free(velocity_frames);

			velocity_frames_len = 0;
		}

		void ParticleEngine::clear_scale_x_frames(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_free(scale_x_frames);

			scale_x_frames_len = 0;
		}

		void ParticleEngine::clear_scale_y_frames(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_free(scale_y_frames);

			scale_y_frames_len = 0;
		}

		void ParticleEngine::clear_color_frames(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			al_free(color_frames);

			color_frames_len = 0;
		}

		void ParticleEngine::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			clear_angle_frames();
			clear_angle_velocity_frames();
			clear_velocity_frames();
			clear_scale_x_frames();
			clear_scale_y_frames();
			clear_color_frames();

			al_free(particles);

			disposed = true;
		}

		ParticleEngine::~ParticleEngine(void){ }
	}
}