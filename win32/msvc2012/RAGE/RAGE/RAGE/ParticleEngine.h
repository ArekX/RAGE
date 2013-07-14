#pragma once

#include "RubyInterpreter.h"

#define REMOVE_FROM_ARY(ary, ary_type, ary_len, indx) if (indx >= ary_len) return; if (indx != (ary_len - 1)) { for(uint64_t i = indx; i < ary_len - 1; i++) ary[i] = ary[i + 1];} ary = (ary_type*)al_realloc(ary, sizeof(ary_type) * --ary_len);
#define ADD_TO_FRAME(frame_ary, ary_len, frame_type, ary_frame_data, frame_data, ary_next_frame_speed) frame_ary = (frame_type*)al_realloc(frame_ary, sizeof(frame_type) * (ary_len + 1)); frame_ary[ary_len].ary_frame_data = frame_data; frame_ary[ary_len++].next_frame_speed = ary_next_frame_speed;
#define MAX_PARTICLES 1024

namespace RAGE
{
	namespace Graphics
	{
		typedef struct 
		{
			float x;
			float y;
			float life;
			float scale_x;
			float scale_y;
			float tr_angle;
			float spin_angle;
			float angle_add;
			float velocity_add;
			float spin_velocity_add;
			float life_add;
			float r_add;
			float g_add;
			float b_add;
			float a_add;
			float scale_x_add;
			float scale_y_add;
		} Particle;

		typedef struct {
			ALLEGRO_COLOR color;
			float next_frame_speed;
		} EmitterColorFrame;

		typedef struct {
			float angle;
			float next_frame_speed;
		} EmitterAngleFrame;

		typedef struct {
			float angle_velocity;
			float next_frame_speed;
		} EmitterAngleVelocityFrame;

		typedef struct {
			float velocity;
			float next_frame_speed;
		} EmitterVelocityFrame;

		typedef struct {
			float scale_x;
			float next_frame_speed;
		} EmitterScaleXFrame;

		typedef struct {
			float scale_y;
			float next_frame_speed;
		} EmitterScaleYFrame;

		typedef enum {
			Point,
			Line,
			Rectangle,
			Circle,
			Ring
		} EmitterType;

		typedef enum {
			Add,
			Normal,
			Multiply,
			Black,
			White,
			Mask
		} EmitterBlendType;

		typedef enum {
			Set,
			Mix
		} EmitterColorMode;

		typedef enum {
			Color,
			Angle,
			AngleVelocity,
			Velocity,
			ScaleX,
			ScaleY
		} EmitterFrameType;

		class ParticleEngine
		{
		private:
			EmitterColorFrame *color_frames;
			EmitterAngleFrame *angle_frames;
			EmitterAngleVelocityFrame *angle_velocity_frames;
			EmitterVelocityFrame *velocity_frames;
			EmitterScaleXFrame *scale_x_frames;
			EmitterScaleYFrame *scale_y_frames;
			Particle *particles;
		public:
			uint64_t color_frames_len;
			uint64_t angle_frames_len;
			uint64_t angle_velocity_frames_len;
			uint64_t velocity_frames_len;
			uint64_t scale_x_frames_len;
			uint64_t scale_y_frames_len;
			uint64_t particles_len;
			float line_emitter_width;
			bool line_emmiter_two_side;
			float rectangle_emitter_width;
			float rectangle_emitter_height;
			float circle_emitter_radius;
			float ring_emitter_inner_radius;
			float ring_emitter_outer_radius;
			bool disposed;
			bool loop;
			EmitterType type;
			EmitterBlendType blend_type;
			EmitterColorMode color_mode;
			int frame_width;
			int frame_height;
			float current_frame;
			float total_frames;
			float emitter_x;
			float emitter_y;
			float emitter_spread;
			float emitter_angle;
			float emitter_duration;
			float angle_add_max;
			float velocity_add_max;
			float spin_velocity_add_max;
			float life_add_max;
			float r_add_max;
			float g_add_max;
			float b_add_max;
			float a_add_max;
			float scale_x_add_max;
			float scale_y_add_max;
			ALLEGRO_BITMAP *particle_tex;
			ParticleEngine(void);
			void initialize(ALLEGRO_BITMAP* particle, int emitter_count, float emitter_duration, float emitter_direction, float emitter_spread, EmitterType type);
			void update(float dt);
			void draw();
			void draw(float x, float y);
			void increase_particles(int amount);
			void decrease_particles(int amount);
			void calculate_next_particle(float* last_particle_x, float* last_particle_y);

			void set_next_frame_speed(EmitterFrameType type, uint64_t index, float speed); 
			float get_next_frame_speed(EmitterFrameType type, uint64_t index);

			void set_angle_frame(uint64_t index, float angle);
			void set_angle_velocity_frame(uint64_t index, float angle_velocity);
			void set_velocity_frame(uint64_t index, float velocity);
			void set_scale_x_frame(uint64_t index, float scale_x);
			void set_scale_y_frame(uint64_t index, float scale_y);
			void set_color_frame(uint64_t index, ALLEGRO_COLOR color);

			float get_angle_frame(uint64_t index);
			float get_angle_velocity_frame(uint64_t index);
			float get_velocity_frame(uint64_t index);
			float get_scale_x_frame(uint64_t index);
			float get_scale_y_frame(uint64_t index);
			ALLEGRO_COLOR get_color_frame(uint64_t index);

			void add_angle_frame(float angle, float next_frame_speed);
			void add_angle_velocity_frame(float angle_velocity, float next_frame_speed);
			void add_velocity_frame(float velocity, float next_frame_speed);
			void add_scale_x_frame(float scale_x, float next_frame_speed);
			void add_scale_y_frame(float scale_y, float next_frame_speed);
			void add_color_frame(ALLEGRO_COLOR color, float next_frame_speed);

			void remove_angle_frame(uint64_t index);
			void remove_angle_velocity_frame(uint64_t index);
			void remove_velocity_frame(uint64_t index);
			void remove_scale_x_frame(uint64_t index);
			void remove_scale_y_frame(uint64_t index);
			void remove_color_frame(uint64_t index);

			void clear_angle_frames(void);
			void clear_angle_velocity_frames(void);
			void clear_velocity_frames(void);
			void clear_scale_x_frames(void);
			void clear_scale_y_frames(void);
			void clear_color_frames(void);

			void dispose(void);

			~ParticleEngine(void);
		};
	}
}

