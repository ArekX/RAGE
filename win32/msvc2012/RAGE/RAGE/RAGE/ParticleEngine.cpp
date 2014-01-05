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

#include "ParticleEngine.h"
#include "Logic_Wrappers.h"

namespace RAGE
{
	namespace Graphics
	{
		ParticleEngine::ParticleEngine(void)
		{
			disposed = false;
			em_particle_delay = 0;
			em_particle_delay_add = 0;

			em_particle_frame_velocity = 2;
			em_particle_frame_velocity_add = 0;

			em_particle_velocity = 60;
			em_particle_velocity_add = 0;

			em_particle_rot_angle = 0;
			em_particle_rot_angle_add = 0;

			em_particle_scale_x = 1;
			em_particle_scale_x_add = 0;
			em_particle_scale_y = 1;
			em_particle_scale_y_add = 0;

			em_particle_center_x = p_region_width / 2;
			em_particle_center_x_add = 0;
			em_particle_center_y = p_region_width / 2;
			em_particle_center_y_add = 0;

			em_particle_ox = 0;
			em_particle_oy = 0;

			em_line_width = 100;

			em_rect_width = 100;
			em_rect_height = 100;

			em_circle_inner_radius = 50;
			em_circle_outer_radius = 100;

			em_type = RAGE_POINT_EMITTER;

			em_particle_tint_r = 1;
			em_particle_tint_r_add = 0;
			em_particle_tint_g = 1;
			em_particle_tint_g_add = 0;
			em_particle_tint_b = 1;
			em_particle_tint_b_add = 0;
			em_particle_tint_a = 1;
			em_particle_tint_a_add = 0;

			em_spread = 0;

			em_angle = 90;

			frame_layers_len = 0;
			p_region_x = 0;
			p_region_y = 0;

			em_particle_appear_velocity = 4;

			particles = nullptr;
			particles_len = 0;

			em_blend_op = ALLEGRO_ADD;
			em_blend_src = ALLEGRO_ONE;
			em_blend_dst = ALLEGRO_INVERSE_ALPHA;
			em_blend_aop = -1;
			em_blend_asrc = 0;
			em_blend_adst = 0;

			em_use_blending = false;

			em_burst_emit = false;

			em_particle_x_add = 0;
			em_particle_y_add = 0;

			em_particle_region_instant_update = true;
		}

		void ParticleEngine::initialize(ALLEGRO_BITMAP* particle, int64_t emitter_count, float emitter_duration, bool emitter_loop, float emitter_x, float emitter_y)
		{
			ALLEGRO_STATE st;
			al_store_state(&st, ALLEGRO_STATE_BITMAP);
			al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
			particle_tex = al_clone_bitmap(particle);
			al_restore_state(&st);

			p_region_width = al_get_bitmap_width(particle);
			p_region_width = al_get_bitmap_height(particle);


			if (emitter_count > 0)
			{
				particles = (Particle*)al_malloc(sizeof(Particle) * emitter_count);
				particles_len = emitter_count;
			}

			em_loop = emitter_loop;

			em_x = emitter_x;
			em_y = emitter_y;

			em_particle_life = emitter_duration / 2;
			em_particle_life_add = emitter_duration / 2;

			em_burst_amount = 30;

			emit();
		}

		void ParticleEngine::emit(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			for (int64_t i = 0; i < particles_len; i++)
			{
				set_particle(&particles[i]);
				particles[i].time = particles[i].life * random_float();
				particles[i].delay = particles[i].time * random_float();
			}
			
		}

		void ParticleEngine::update(float dt) 
		{
			RAGE_CHECK_DISPOSED(disposed);

			register int j;

			for (int64_t i = 0; i < particles_len; i++)
			{
				if (particles[i].delay >= 0)
				{
					particles[i].delay -= em_particle_appear_velocity * dt;
				}
				else
				{
					if ((particles[i].visible == false) && em_burst_emit && (i >= em_burst_amount)) continue; 

					particles[i].visible = true;
					particles[i].x = particles[i].x + particles[i].velocity * sin(particles[i].tr_angle) * dt;
					particles[i].y = particles[i].y + particles[i].velocity * cos(particles[i].tr_angle) * dt;

					particles[i].time += particles[i].frame_velocity * dt;

					if (frame_layers_len > 0)
					{
						float frame_update = particles[i].frame_velocity * dt;

						particles[i].center_x = particles[i].base_center_x;
						particles[i].center_y = particles[i].base_center_y;
						particles[i].scale_x = particles[i].base_scale_x;
						particles[i].scale_y = particles[i].base_scale_y;
						particles[i].tr_angle = particles[i].base_tr_angle;
						particles[i].color = particles[i].base_color;
						particles[i].velocity = particles[i].base_velocity;
						particles[i].rot_angle = particles[i].base_rot_angle;
						particles[i].region_x = particles[i].base_region_x;
						particles[i].region_y = particles[i].base_region_y;
						particles[i].region_w = particles[i].base_region_w;
						particles[i].region_h = particles[i].base_region_h;
					

						for (j = 0; j < frame_layers_len; j++)
						{
						
							particles[i].current_frames[j] += frame_update;

							if (frame_layers[j].data_len > 0)
							{

								if (particles[i].current_frames[j] >= frame_layers[j].data[particles[i].current_frame_indices[j]].duration)
								{
									particles[i].base_center_x += frame_layers[j].data[particles[i].current_frame_indices[j]].center_x;
									particles[i].base_center_y += frame_layers[j].data[particles[i].current_frame_indices[j]].center_y;
									particles[i].base_scale_x += frame_layers[j].data[particles[i].current_frame_indices[j]].scale_x;
									particles[i].base_scale_y += frame_layers[j].data[particles[i].current_frame_indices[j]].scale_y;
									particles[i].base_tr_angle += frame_layers[j].data[particles[i].current_frame_indices[j]].tr_angle;
									particles[i].base_rot_angle += frame_layers[j].data[particles[i].current_frame_indices[j]].rot_angle;
									particles[i].base_velocity += frame_layers[j].data[particles[i].current_frame_indices[j]].velocity;
									particles[i].base_color.r += frame_layers[j].data[particles[i].current_frame_indices[j]].tint_r;
									particles[i].base_color.g += frame_layers[j].data[particles[i].current_frame_indices[j]].tint_g;
									particles[i].base_color.b += frame_layers[j].data[particles[i].current_frame_indices[j]].tint_b;
									particles[i].base_color.a += frame_layers[j].data[particles[i].current_frame_indices[j]].tint_a;
									particles[i].base_region_x += frame_layers[j].data[particles[i].current_frame_indices[j]].region_x; 
									particles[i].base_region_y += frame_layers[j].data[particles[i].current_frame_indices[j]].region_y;  
									particles[i].base_region_w += frame_layers[j].data[particles[i].current_frame_indices[j]].region_w;  
									particles[i].base_region_h += frame_layers[j].data[particles[i].current_frame_indices[j]].region_h; 

									particles[i].center_x = particles[i].base_center_x;
									particles[i].center_y = particles[i].base_center_y;
									particles[i].scale_x = particles[i].base_scale_x;
									particles[i].scale_y = particles[i].base_scale_y;
									particles[i].tr_angle = particles[i].base_tr_angle;
									particles[i].color = particles[i].base_color;
									particles[i].velocity = particles[i].base_velocity;
									particles[i].rot_angle = particles[i].base_rot_angle;
									particles[i].region_x = particles[i].base_region_x;
									particles[i].region_y = particles[i].base_region_y;
									particles[i].region_w = particles[i].base_region_w;
									particles[i].region_h = particles[i].base_region_h;

									particles[i].current_frame_indices[j]++;

									if (particles[i].current_frame_indices[j] >= frame_layers[j].data_len) 
										particles[i].current_frame_indices[j] = 0;

									particles[i].current_frames[j] = 0;
								}

								int index = particles[i].current_frame_indices[j];

								int b_index = (index > 0) ? index - 1 : 0;
								float delta = particles[i].current_frames[j] / frame_layers[j].data[index].duration;

								particles[i].tr_angle += frame_layers[j].data[index].tr_angle * delta;
								particles[i].scale_x += frame_layers[j].data[index].scale_x * delta;
								particles[i].scale_y += frame_layers[j].data[index].scale_y * delta;
								particles[i].center_x += frame_layers[j].data[index].center_x * delta;
								particles[i].center_y += frame_layers[j].data[index].center_y * delta;
								particles[i].velocity += frame_layers[j].data[index].velocity * delta;
								particles[i].rot_angle += frame_layers[j].data[index].rot_angle * delta;
								particles[i].color.r += frame_layers[j].data[index].tint_r * delta;
								particles[i].color.g += frame_layers[j].data[index].tint_g * delta;
								particles[i].color.b += frame_layers[j].data[index].tint_b * delta;
								particles[i].color.a += frame_layers[j].data[index].tint_a * delta;

								if (!em_particle_region_instant_update)
								{
									particles[i].region_x += frame_layers[j].data[index].region_x * delta; 
									particles[i].region_y += frame_layers[j].data[index].region_y * delta;  
									particles[i].region_w += frame_layers[j].data[index].region_w * delta;  
									particles[i].region_h += frame_layers[j].data[index].region_h * delta;  
								}

							}
						}
					}
				}

				if (particles[i].time >= particles[i].life)
				{
					particles[i].visible = false;

					if (em_loop)
						set_particle(&particles[i]);
						
				}
				
			}
		}

		void ParticleEngine::draw(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (em_use_blending)
			{
				al_get_separate_blender(&em_blend_rop, &em_blend_rsrc, &em_blend_rdst, &em_blend_raop, &em_blend_rasrc, &em_blend_radst);
				
				if (em_blend_aop != -1)
					al_set_separate_blender(em_blend_op, em_blend_src, em_blend_dst, em_blend_aop, em_blend_src, em_blend_dst);
				else
					al_set_blender(em_blend_op, em_blend_src, em_blend_dst);
			}

			for (int64_t i = 0; i < particles_len; i++)
			{
					if (particles[i].visible)
						al_draw_tinted_scaled_rotated_bitmap_region(
																	particle_tex, 
																	particles[i].region_x, 
																	particles[i].region_y, 
																	particles[i].region_w, 
																	particles[i].region_h, 
																	particles[i].color,
																	particles[i].center_x, 
																	particles[i].center_y, 
																	em_particle_ox + particles[i].x, 
																	em_particle_oy + particles[i].y, 
																	particles[i].scale_x, 
																	particles[i].scale_y, 
																	particles[i].rot_angle, 
																	0
																   );
			}

			if (em_use_blending)
				al_set_separate_blender(em_blend_rop, em_blend_rsrc, em_blend_rdst, em_blend_raop, em_blend_rasrc, em_blend_radst);
			
		}
		
		void ParticleEngine::set_emitter_position(float x, float y)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_x = x;
			em_y = y;
		}

		void ParticleEngine::set_particle(Particle *pa)
		{
			if (em_type == RAGE_POINT_EMITTER)
			{
				pa->x = em_x;
				pa->y = em_y;
			}
			else if (em_type == RAGE_LINE_EMITTER)
			{
				pa->x = em_x - em_line_width / 2 + em_line_width * random_float();
				pa->y = em_y;
			}
			else if (em_type == RAGE_RECT_EMITTER)
			{
				pa->x = em_x - em_rect_width / 2 + em_rect_width * random_float();
				pa->y = em_y - em_rect_height / 2 + em_rect_height * random_float();
			}
			else if (em_type == RAGE_CIRCLE_EMITTER)
			{
				pa->x = em_x + em_circle_inner_radius * random_float() * sin(2 * ALLEGRO_PI * random_float());
				pa->y = em_y + em_circle_inner_radius * random_float() * cos(2 * ALLEGRO_PI * random_float());
			}
			else if (em_type == RAGE_RING_EMITTER)
			{
				float size = (em_circle_inner_radius + em_circle_outer_radius) / 2 + abs(em_circle_outer_radius - em_circle_inner_radius) * random_float();
				pa->x = em_x + size * sin(2 * ALLEGRO_PI * random_float());
				pa->y = em_y + size * cos(2 * ALLEGRO_PI * random_float());
			}

			pa->x += em_particle_x_add > 0 ? em_particle_x_add * random_float() : 0;
			pa->y += em_particle_y_add > 0 ? em_particle_y_add * random_float() : 0;

			pa->region_x = p_region_x;
			pa->region_y = p_region_y;
			pa->region_w = p_region_width;
			pa->region_h = p_region_height;

			pa->scale_x = em_particle_scale_x + em_particle_scale_x_add * random_float();
			pa->scale_y = em_particle_scale_y + em_particle_scale_y_add * random_float();
			pa->frame_velocity = em_particle_frame_velocity + em_particle_frame_velocity_add * random_float();
			pa->color.r = em_particle_tint_r + em_particle_tint_r_add * random_float();
			pa->color.g = em_particle_tint_g + em_particle_tint_g_add * random_float();
			pa->color.b = em_particle_tint_b + em_particle_tint_b_add * random_float();
			pa->color.a = em_particle_tint_a + em_particle_tint_a_add * random_float();
			pa->center_x = em_particle_center_x + em_particle_center_x_add * random_float();
			pa->center_y = em_particle_center_y + em_particle_center_y_add * random_float();
			pa->delay = em_particle_delay + em_particle_delay_add * random_float();
			pa->life = em_particle_life + em_particle_life_add * random_float();
			pa->tr_angle = em_angle + em_spread * random_float();
			pa->velocity = em_particle_velocity + em_particle_velocity_add * random_float();
			pa->rot_angle = em_particle_rot_angle + em_particle_rot_angle_add * random_float();
			pa->time = 0;

			pa->base_region_x = pa->region_x;
			pa->base_region_y = pa->region_y;
			pa->base_region_w = pa->region_w;
			pa->base_region_h = pa->region_h;
			pa->base_tr_angle = pa->tr_angle;
			pa->base_scale_x = pa->scale_x;
			pa->base_scale_y = pa->scale_y;
			pa->base_velocity = pa->velocity;
			pa->base_center_x = pa->center_x;
			pa->base_center_y = pa->center_y;
			pa->base_rot_angle = pa->rot_angle;
			pa->base_color = pa->color;
			

			for (int i = 0; i < frame_layers_len; i++)
			{
				pa->current_frame_indices[i] = 0;
				pa->current_frames[i] = 0;
			}
			

			pa->visible = false;
		}

		void ParticleEngine::set_particle_tex(ALLEGRO_BITMAP* new_tex)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (particle_tex != nullptr)
				al_destroy_bitmap(particle_tex);

			if (new_tex != nullptr)
			{
				ALLEGRO_STATE st;

				al_store_state(&st, ALLEGRO_STATE_BITMAP);
				al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
				particle_tex = al_clone_bitmap(new_tex);
				al_restore_state(&st);
			}
		}

		void ParticleEngine::set_particle_region(float x, float y, int width, int height, bool center_rotation)
		{
			RAGE_CHECK_DISPOSED(disposed);

			p_region_x = x;
			p_region_y = y;
			p_region_width = width;
			p_region_height = height;

			if (center_rotation)
			{
				em_particle_center_x = p_region_width / 2;
				em_particle_center_y = p_region_height / 2;
			}
		}

		void ParticleEngine::set_frame_layers(int amount)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (amount < 0) amount = 0;

			if ((frame_layers_len == 0) && (amount > 0))
			{
				frame_layers = (EmitterFrameLayer*)al_malloc(sizeof(EmitterFrameLayer) * amount);

				for (int i = 0; i < amount; i++)
					frame_layers[i].data_len = 0;
			}
			else if ((amount > 0) && (amount < frame_layers_len))
			{
				for (int i = amount - 1; i < frame_layers_len; i++)
					if (frame_layers[i].data_len > 0) al_free(frame_layers[i].data);

				frame_layers = (EmitterFrameLayer*)al_realloc(frame_layers, (sizeof(EmitterFrameLayer) * amount));
			}
			else if ((amount > 0) && (amount > frame_layers_len))
			{
				frame_layers = (EmitterFrameLayer*)al_realloc(frame_layers, (sizeof(EmitterFrameLayer) * amount));
				
				for (int i = frame_layers_len - 1; i < amount; i++)
					frame_layers[i].data_len = 0;
			}
			else if ((frame_layers_len > 0) && (amount == 0))
			{	
				for (int i = 0; i < frame_layers_len; i++)
					if (frame_layers[i].data_len > 0) al_free(frame_layers[i].data);

				al_free(frame_layers);
			}
			
			for (int64_t i = 0; i < particles_len; i++)
			{
				if ((frame_layers_len == 0) && (amount > 0))
				{
					particles[i].current_frame_indices = (int*)al_malloc(sizeof(int) * amount);
					particles[i].current_frames = (float*)al_malloc(sizeof(float) * amount);
				}
				else if ((amount > 0) && (amount < frame_layers_len))
				{
					particles[i].current_frame_indices = (int*)al_realloc(particles[i].current_frame_indices, sizeof(int) * amount);
					particles[i].current_frames = (float*)al_realloc(particles[i].current_frames, sizeof(float) * amount);				
				}
				else if ((amount > 0) && (amount > frame_layers_len))
				{
					particles[i].current_frame_indices = (int*)al_realloc(particles[i].current_frame_indices, sizeof(int) * amount);
					particles[i].current_frames = (float*)al_realloc(particles[i].current_frames, sizeof(float) * amount);

					for (int j = frame_layers_len - 1; j < amount; j++)
					{
						particles[i].current_frame_indices[j] = 0;
						particles[i].current_frames[j] = 0;
					}
				}
				else if ((frame_layers_len > 0) && (amount == 0))
				{
					destroy_particle(&particles[i]);
				}
			}

			frame_layers_len = amount;

			emit();
		}

		void ParticleEngine::add_frame_to_layer(int layer_index, float duration, float scale_x, float scale_y, float tr_angle, float rot_angle, float velocity, float center_x, float center_y, float region_x, float region_y, float region_w, float region_h, float tint_r, float tint_g, float tint_b, float tint_a)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((layer_index >= frame_layers_len) || (layer_index < 0)) return;

			if (frame_layers[layer_index].data_len == 0)
			{
				frame_layers[layer_index].data = (EmitterFrameData*)al_malloc(sizeof(EmitterFrameData));
				frame_layers[layer_index].data_len = 1;
			}
			else
				frame_layers[layer_index].data = (EmitterFrameData*)al_realloc(frame_layers[layer_index].data, sizeof(EmitterFrameData) * ++frame_layers[layer_index].data_len);

			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].center_x = center_x;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].center_y = center_y;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].scale_x = scale_x;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].scale_y = scale_y;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].rot_angle = rot_angle;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].tr_angle = tr_angle;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].velocity = velocity;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].tint_r = tint_r;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].tint_g = tint_g;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].tint_b = tint_b;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].tint_a = tint_a;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].region_x = region_x;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].region_y = region_y;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].region_w = region_w;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].region_h = region_h;
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].duration = duration;
		}

		void ParticleEngine::remove_frame_from_layer(int layer_index, int frame_index)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((layer_index >= frame_layers_len) || (layer_index < 0)) return;
			if (frame_index >= frame_layers[layer_index].data_len) return;

			for(int i = frame_index; i < frame_layers[layer_index].data_len - 1; i++)
					frame_layers[layer_index].data[i] = frame_layers[layer_index].data[i + 1];
			
			frame_layers[layer_index].data = (EmitterFrameData*)al_realloc(frame_layers[layer_index].data, sizeof(EmitterFrameData) * --frame_layers[layer_index].data_len);
		}

		void ParticleEngine::clear_frames_from_layer(int layer_index)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if ((layer_index >= frame_layers_len) || (layer_index < 0)) return;
			if (layer_index >= frame_layers_len) return;

			frame_layers[layer_index].data_len = 0;

			al_free(frame_layers[layer_index].data);
		}

		bool ParticleEngine::box_collision(float x, float y, float w, float h)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			for (int64_t i = 0; i < particles_len; i++)
			{
				if (Logic::LogicWrappers::collision(x, y, w, h, em_particle_ox + particles[i].x - particles[i].center_x * particles[i].scale_x, em_particle_oy + particles[i].y - particles[i].center_y * particles[i].scale_y, particles[i].region_w * particles[i].scale_x, particles[i].region_h * particles[i].scale_y))
					return true; 
			}
			return false;
		}

		float ParticleEngine::get_emitter_angle(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_angle;
		}

		float ParticleEngine::get_emitter_spread(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_spread;
		}

		int ParticleEngine::get_emitter_type(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_type;
		}

		bool ParticleEngine::get_emitter_loop(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return em_loop;
		}

		void ParticleEngine::set_emitter_blend_alpha(int op, int src, int dst, int aop, int asrc, int adst)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_blend_op = op;
			em_blend_src = src;
			em_blend_dst = dst;
			em_blend_aop = aop;
			em_blend_asrc = asrc;
			em_blend_adst = adst;
		}

		void ParticleEngine::set_emitter_blend(int op, int src, int dst)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_blend_op = op;
			em_blend_src = src;
			em_blend_dst = dst;
			em_blend_aop = -1;
		}

		void ParticleEngine::set_particle_coords(float ox, float oy)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_particle_ox = ox;
			em_particle_oy = oy;
		}

		void ParticleEngine::set_loop(bool loop)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_loop = loop;
		}

		void ParticleEngine::set_angle(float angle)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_angle = angle;
		}

		void ParticleEngine::set_spread(float spread)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_spread = spread;
		}

		void ParticleEngine::set_type(int type)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (type > RAGE_RING_EMITTER) return;

			em_type = type;
		}

		void ParticleEngine::initialize_particle(Particle *pa)
		{
			if (frame_layers_len > 0)
			{
				pa->current_frame_indices = (int*)al_malloc(sizeof(int) * frame_layers_len);
				pa->current_frames = (float*)al_malloc(sizeof(float) * frame_layers_len);
			}

			set_particle(pa);
			pa->time = pa->life * random_float();
			pa->delay = pa->time * random_float();
		}

		void ParticleEngine::destroy_particle(Particle *pa)
		{
			if (frame_layers_len > 0)
			{
					al_free(pa->current_frame_indices);
					al_free(pa->current_frames);
			}
		}

		void ParticleEngine::set_particles_num(int64_t new_num)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			if (new_num < 0) return;
			
			for (int64_t i = 0; i < particles_len; i++)
				destroy_particle(&particles[i]);

			al_free(particles);

			particles = (Particle*)al_malloc(sizeof(Particle) * new_num);

			for (int64_t i = 0; i < new_num; i++)
				initialize_particle(&particles[i]);

			particles_len = new_num;
		}

		void ParticleEngine::set_emitter_line_width(float new_width)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_line_width = new_width;
		}

		void ParticleEngine::set_emitter_rectangle_width(float new_width)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_rect_width = new_width;
		}

		void ParticleEngine::set_emitter_rectangle_height(float new_height)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_rect_height = new_height;
		}

		void ParticleEngine::set_emitter_inner_circle_radius(float new_radius)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_circle_inner_radius = new_radius;
		}

		void ParticleEngine::set_emitter_outer_circle_radius(float new_radius)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_circle_outer_radius = new_radius;
		}

		void ParticleEngine::set_use_blending(bool use_blending)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_use_blending = use_blending;

			if (use_blending)
				al_get_separate_blender(&em_blend_op, &em_blend_src, &em_blend_dst, &em_blend_aop, &em_blend_asrc, &em_blend_rdst);
		}

		/* Get Ops */
		int64_t ParticleEngine::get_particles_num(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return particles_len;
		}

		float ParticleEngine::get_emitter_line_width(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_line_width;
		}

		float ParticleEngine::get_emitter_rectangle_width(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_rect_width;
		}

		float ParticleEngine::get_emitter_rectangle_height(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_rect_height;
		}

		float ParticleEngine::get_emitter_inner_circle_radius(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_circle_inner_radius;
		}

		float ParticleEngine::get_emitter_outer_circle_radius(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_circle_outer_radius;
		}

		bool ParticleEngine::get_use_blending(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return em_use_blending;
		}

		void ParticleEngine::set_particle_burst_amount(int64_t burst_amount)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (burst_amount < 0) burst_amount = 0;
			if (burst_amount > particles_len) burst_amount = particles_len;

			if ((burst_amount > 0) && (em_burst_amount > 0))
			{
				if (burst_amount > em_burst_amount)
					for (int64_t i = em_burst_amount - 1; i < burst_amount; i++)
					{
						set_particle(&particles[i]);
						particles[i].time = particles[i].life * random_float();
						particles[i].delay = particles[i].time * random_float();
					}
			}
			else
				emit();

			em_burst_amount = burst_amount;
		}

		int64_t ParticleEngine::get_particle_burst_amount(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_burst_amount;
		}

		void ParticleEngine::set_particle_region_instant_update(bool update)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_particle_region_instant_update = update;
		}

		bool ParticleEngine::get_particle_region_instant_update(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, false);

			return em_particle_region_instant_update;
		}

		void ParticleEngine::set_emitter_burst(bool emitter_burst)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_burst_emit = emitter_burst;
		}

		bool ParticleEngine::get_emitter_burst(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, true);

			return em_burst_emit;
		}

		void ParticleEngine::set_particle_life(float life)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (life < 0) life = 0;
			
			em_particle_life = life;

		}

 
		float ParticleEngine::get_particle_life(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_life;

		}


		void ParticleEngine::set_particle_life_add(float life_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_life_add = life_add;

		}

 
		float ParticleEngine::get_particle_life_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_life_add;

		}


		void ParticleEngine::set_particle_appear_velocity(float appear_velocity)
		{
			RAGE_CHECK_DISPOSED(disposed);
			if (appear_velocity < 0) appear_velocity = 0;

			em_particle_appear_velocity = appear_velocity;

		}

 
		float ParticleEngine::get_particle_appear_velocity(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			

			return em_particle_appear_velocity;

		}


		void ParticleEngine::set_particle_velocity(float velocity)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_velocity = velocity;

		}

 
		float ParticleEngine::get_particle_velocity(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_velocity;

		}


		void ParticleEngine::set_particle_velocity_add(float velocity_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_velocity_add = velocity_add;

		}

 
		float ParticleEngine::get_particle_velocity_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_velocity_add;

		}


		void ParticleEngine::set_particle_frame_velocity(float frame_velocity)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_frame_velocity = frame_velocity;

		}

 
		float ParticleEngine::get_particle_frame_velocity(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_frame_velocity;

		}


		void ParticleEngine::set_particle_frame_velocity_add(float frame_velocity_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_frame_velocity_add = frame_velocity_add;

		}

 
		float ParticleEngine::get_particle_frame_velocity_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_frame_velocity_add;

		}


		void ParticleEngine::set_particle_rot_angle(float rot_angle)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_rot_angle = rot_angle;

		}

 
		float ParticleEngine::get_particle_rot_angle(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_rot_angle;

		}


		void ParticleEngine::set_particle_rot_angle_add(float rot_angle_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_rot_angle_add = rot_angle_add;

		}

 
		float ParticleEngine::get_particle_rot_angle_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_rot_angle_add;

		}


		void ParticleEngine::set_particle_scale_x(float scale_x)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_scale_x = scale_x;

		}

 
		float ParticleEngine::get_particle_scale_x(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_scale_x;

		}


		void ParticleEngine::set_particle_scale_x_add(float scale_x_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_scale_x_add = scale_x_add;

		}

 
		float ParticleEngine::get_particle_scale_x_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_scale_x_add;

		}


		void ParticleEngine::set_particle_scale_y(float scale_y)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_scale_y = scale_y;

		}

 
		float ParticleEngine::get_particle_scale_y(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_scale_y;

		}


		void ParticleEngine::set_particle_scale_y_add(float scale_y_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_scale_y_add = scale_y_add;

		}

 
		float ParticleEngine::get_particle_scale_y_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_scale_y_add;

		}


		void ParticleEngine::set_particle_center_x(float center_x)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_center_x = center_x;

		}

 
		float ParticleEngine::get_particle_center_x(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_center_x;

		}


		void ParticleEngine::set_particle_center_x_add(float center_x_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_center_x_add = center_x_add;

		}

 
		float ParticleEngine::get_particle_center_x_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_center_x_add;

		}


		void ParticleEngine::set_particle_center_y(float center_y)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_center_y = center_y;

		}

 
		float ParticleEngine::get_particle_center_y(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_center_y;

		}


		void ParticleEngine::set_particle_center_y_add(float center_y_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_center_y_add = center_y_add;

		}

 
		float ParticleEngine::get_particle_center_y_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_center_y_add;

		}

		void ParticleEngine::set_particle_delay(float delay)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_delay = delay;

		}

 
		float ParticleEngine::get_particle_delay(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_delay;

		}


		void ParticleEngine::set_particle_delay_add(float delay_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_delay_add = delay_add;

		}

 
		float ParticleEngine::get_particle_delay_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_delay_add;

		}


		void ParticleEngine::set_particle_tint_r(float tint_r)
		{
			RAGE_CHECK_DISPOSED(disposed);

			em_particle_tint_r = tint_r;

		}

 
		float ParticleEngine::get_particle_tint_r(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_r;

		}


		void ParticleEngine::set_particle_tint_r_add(float tint_r_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_tint_r_add = tint_r_add;

		}

 
		float ParticleEngine::get_particle_tint_r_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_r_add;

		}


		void ParticleEngine::set_particle_tint_g(float tint_g)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_tint_g = tint_g;

		}

 
		float ParticleEngine::get_particle_tint_g(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_g;

		}


		void ParticleEngine::set_particle_tint_g_add(float tint_g_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_tint_g_add = tint_g_add;

		}

 
		float ParticleEngine::get_particle_tint_g_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_g_add;

		}


		void ParticleEngine::set_particle_tint_b(float tint_b)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_tint_b = tint_b;

		}

 
		float ParticleEngine::get_particle_tint_b(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_b;

		}


		void ParticleEngine::set_particle_tint_b_add(float tint_b_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_tint_b_add = tint_b_add;

		}

 
		float ParticleEngine::get_particle_tint_b_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_b_add;

		}


		void ParticleEngine::set_particle_tint_a(float tint_a)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_tint_a = tint_a;

		}

 
		float ParticleEngine::get_particle_tint_a(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_a;

		}


		void ParticleEngine::set_particle_tint_a_add(float tint_a_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_tint_a_add = tint_a_add;

		}

 
		float ParticleEngine::get_particle_tint_a_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_tint_a_add;

		}


		void ParticleEngine::set_particle_x_add(float x_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_x_add = x_add;

		}

 
		float ParticleEngine::get_particle_x_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_x_add;

		}


		void ParticleEngine::set_particle_y_add(float y_add)
		{
			RAGE_CHECK_DISPOSED(disposed);
			
			em_particle_y_add = y_add;

		}

 
		float ParticleEngine::get_particle_y_add(void)
		{
			RAGE_CHECK_DISPOSED_RET(disposed, 0);

			return em_particle_y_add;

		}

		void ParticleEngine::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);			

			if (frame_layers_len > 0) 
				set_frame_layers(0);
			
			if (particles_len > 0)
				al_free(particles);

			if (particle_tex != nullptr)
				al_destroy_bitmap(particle_tex);

			disposed = true;
		}

		ParticleEngine::~ParticleEngine(void)
		{
			if (!disposed)
				dispose();
		}
	}
}