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

#include "RubyInterpreter.h"

#define RAGE_POINT_EMITTER 0
#define RAGE_LINE_EMITTER 1
#define RAGE_RECT_EMITTER 2
#define RAGE_CIRCLE_EMITTER 3
#define RAGE_RING_EMITTER 4

namespace RAGE
{
	namespace Graphics
	{
		typedef struct 
		{
			float x;
			float y;
			float center_x;
			float center_y;
			float delay;
			float life;
			float frame_velocity;
			float scale_x;
			float scale_y;
			float tr_angle;
			float rot_angle;
			float velocity;
			float region_x;
			float region_y;
			float region_w;
			float region_h;
			bool visible;
			ALLEGRO_COLOR color;

			/* For frames */
			float base_tr_angle;
			float base_scale_x;
			float base_scale_y;
			float base_velocity;
			float base_center_x;
			float base_center_y;
			float base_rot_angle;
			float base_region_x;
			float base_region_y;
			float base_region_w;
			float base_region_h;

			float time;

			ALLEGRO_COLOR base_color;
			int *current_frame_indices;
			float *current_frames;
		} Particle;

		typedef struct {
			float scale_x;
			float scale_y;
			float tr_angle;
			float rot_angle;
			float velocity;
			float center_x;
			float center_y;
			float tint_r;
			float tint_g;
			float tint_b;
			float tint_a;
			float region_x;
			float region_y;
			float region_w;
			float region_h;
			float duration;
		} EmitterFrameData;

		typedef struct {
			EmitterFrameData *data;
			int data_len;
		} EmitterFrameLayer;

		class ParticleEngine
		{
		private:
			Particle *particles;
			EmitterFrameLayer *frame_layers;
			ALLEGRO_BITMAP *particle_tex;
			int64_t particles_len;
			int64_t em_burst_amount;
			int em_type;
			int frame_layers_len;
			float em_x;
			float em_y;
			float p_region_x;
			float p_region_y;
			int p_region_width;
			int p_region_height;
			float em_spread;
			float em_angle;
			
			float em_particle_life;
			float em_particle_life_add;
			float em_particle_appear_velocity;
			float em_particle_velocity;
			float em_particle_velocity_add;
			float em_particle_frame_velocity;
			float em_particle_frame_velocity_add;
			float em_particle_rot_angle;
			float em_particle_rot_angle_add;
			float em_particle_scale_x;
			float em_particle_scale_x_add;
			float em_particle_scale_y;
			float em_particle_scale_y_add;
			float em_particle_center_x;
			float em_particle_center_x_add;
			float em_particle_center_y;
			float em_particle_center_y_add;
			float em_particle_delay;
			float em_particle_delay_add;
			float em_particle_tint_r;
			float em_particle_tint_r_add;
			float em_particle_tint_g;
			float em_particle_tint_g_add;
			float em_particle_tint_b;
			float em_particle_tint_b_add;
			float em_particle_tint_a;
			float em_particle_tint_a_add;
			float em_particle_x_add;
			float em_particle_y_add;

			float em_line_width;
			float em_rect_width;
			float em_rect_height;
			float em_circle_inner_radius;
			float em_circle_outer_radius;
			float em_particle_ox;
			float em_particle_oy;
			int em_blend_op;
			int em_blend_src;
			int em_blend_dst;
			int em_blend_aop;
			int em_blend_asrc;
			int em_blend_adst;
			int em_blend_rop;
			int em_blend_rsrc;
			int em_blend_rdst;
			int em_blend_raop;
			int em_blend_rasrc;
			int em_blend_radst;
			bool em_use_blending;
			bool em_loop;
			bool em_particle_region_instant_update;
			bool em_burst_emit;
			void initialize_particle(Particle *pa);
			void destroy_particle(Particle *pa);
			void set_particle(Particle *pa);
		public:			
			bool disposed;
			ParticleEngine(void);
			void initialize(ALLEGRO_BITMAP* particle, int64_t emitter_count, float emitter_duration, bool emitter_loop, float x, float y);
			void emit(void);
			void update(float dt);
			void draw(void);
			void set_emitter_position(float x, float y);
			void set_particle_tex(ALLEGRO_BITMAP* new_tex);
			void set_particle_region(float x, float y, int width, int height, bool set_center);

			bool box_collision(float x, float y, float w, float h);

			/* Frame animation operations */
			float get_emitter_angle(void);
			float get_emitter_spread(void);
			int get_emitter_type(void);
			bool get_emitter_loop(void);

			void set_frame_layers(int amount);
			void add_frame_to_layer(int layer_index, float duration, float scale_x, float scale_y, float tr_angle, float rot_angle, float velocity, float center_x, float center_y, float region_x, float region_y, float region_w, float region_h, float tint_r, float tint_g, float tint_b, float tint_a);
			void remove_frame_from_layer(int layer_index, int frame_index);
			void clear_frames_from_layer(int layer_index);

			void set_emitter_blend_alpha(int op, int src, int dst, int aop, int asrc, int adst);
			void set_emitter_blend(int op, int src, int dst);
			void set_use_blending(bool use_blending);
			void set_particle_coords(float ox, float oy);
			void set_emitter_line_width(float new_width);
			void set_emitter_rectangle_width(float new_width);
			void set_emitter_rectangle_height(float new_height);
			void set_emitter_inner_circle_radius(float new_radius);
			void set_emitter_outer_circle_radius(float new_radius);
			void set_loop(bool loop);
			void set_angle(float angle);
			void set_spread(float spread);
			void set_type(int type);
			void set_particles_num(int64_t new_num);
			void set_particle_burst_amount(int64_t burst_amount);
			int64_t get_particle_burst_amount(void);
			void set_emitter_burst(bool emitter_burst);
			bool get_emitter_burst(void);
			void set_particle_region_instant_update(bool update);
			bool get_particle_region_instant_update(void);
			void set_particle_life(float life); 
			float get_particle_life(void);
			void set_particle_life_add(float life_add); 
			float get_particle_life_add(void);
			void set_particle_appear_velocity(float appear_velocity); 
			float get_particle_appear_velocity(void);
			void set_particle_velocity(float velocity); 
			float get_particle_velocity(void);
			void set_particle_velocity_add(float velocity_add); 
			float get_particle_velocity_add(void);
			void set_particle_frame_velocity(float frame_velocity); 
			float get_particle_frame_velocity(void);
			void set_particle_frame_velocity_add(float frame_velocity_add); 
			float get_particle_frame_velocity_add(void);
			void set_particle_rot_angle(float rot_angle); 
			float get_particle_rot_angle(void);
			void set_particle_rot_angle_add(float rot_angle_add); 
			float get_particle_rot_angle_add(void);
			void set_particle_scale_x(float scale_x); 
			float get_particle_scale_x(void);
			void set_particle_scale_x_add(float scale_x_add); 
			float get_particle_scale_x_add(void);
			void set_particle_scale_y(float scale_y); 
			float get_particle_scale_y(void);
			void set_particle_scale_y_add(float scale_y_add); 
			float get_particle_scale_y_add(void);
			void set_particle_center_x(float center_x); 
			float get_particle_center_x(void);
			void set_particle_center_x_add(float center_x_add); 
			float get_particle_center_x_add(void);
			void set_particle_center_y(float center_y); 
			float get_particle_center_y(void);
			void set_particle_center_y_add(float center_y_add); 
			float get_particle_center_y_add(void);
			void set_particle_delay(float delay); 
			float get_particle_delay(void);
			void set_particle_delay_add(float delay_add); 
			float get_particle_delay_add(void);
			void set_particle_tint_r(float tint_r); 
			float get_particle_tint_r(void);
			void set_particle_tint_r_add(float tint_r_add); 
			float get_particle_tint_r_add(void);
			void set_particle_tint_g(float tint_g); 
			float get_particle_tint_g(void);
			void set_particle_tint_g_add(float tint_g_add); 
			float get_particle_tint_g_add(void);
			void set_particle_tint_b(float tint_b); 
			float get_particle_tint_b(void);
			void set_particle_tint_b_add(float tint_b_add); 
			float get_particle_tint_b_add(void);
			void set_particle_tint_a(float tint_a); 
			float get_particle_tint_a(void);
			void set_particle_tint_a_add(float tint_a_add); 
			float get_particle_tint_a_add(void);
			void set_particle_x_add(float x_add); 
			float get_particle_x_add(void);
			void set_particle_y_add(float y_add); 
			float get_particle_y_add(void);


			/* Get Ops */
			int64_t get_particles_num(void);
			float get_emitter_line_width(void);
			float get_emitter_rectangle_width(void);
			float get_emitter_rectangle_height(void);
			float get_emitter_inner_circle_radius(void);
			float get_emitter_outer_circle_radius(void);
			bool get_use_blending(void);

			void dispose(void);
			~ParticleEngine(void);
		};
	}
}

