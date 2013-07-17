#include "ParticleEngine.h"

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

			em_particle_tr_angle_change = 0;

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

			particles = NULL;
			particles_len = 0;

			em_blend_op = -1;
			em_blend_src = 0;
			em_blend_dst = 0;
			em_blend_aop = -1;
			em_blend_asrc = 0;
			em_blend_adst = 0;

			em_use_blending = false;
		}


		/*
		 * TODO:
		 - RAGE_CHECK_DISPOSED for all (that means making every setting a function... ugh)
		 */

		void ParticleEngine::initialize(ALLEGRO_BITMAP* particle, uint64_t emitter_count, float emitter_duration, bool emitter_loop, float emitter_x, float emitter_y)
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

			emit();
		}

		void ParticleEngine::emit(void)
		{
			RAGE_CHECK_DISPOSED(disposed);

			for (uint64_t i = 0; i < particles_len; i++)
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

			for (uint64_t i = 0; i < particles_len; i++)
			{
				if (particles[i].delay >= 0)
				{
					particles[i].delay -= em_particle_appear_velocity * dt;
				}
				else
				{
					particles[i].visible = true;
					particles[i].x = particles[i].x + particles[i].velocity * sin(particles[i].tr_angle) * dt;
					particles[i].y = particles[i].y + particles[i].velocity * cos(particles[i].tr_angle) * dt;

					particles[i].current_frame += particles[i].frame_velocity * dt;
					particles[i].tr_angle += em_particle_tr_angle_change * dt;
					particles[i].time += particles[i].frame_velocity * dt;

					if (frame_layers_len > 0)
					{
						particles[i].center_x = particles[i].base_center_x;
						particles[i].center_y = particles[i].base_center_y;
						particles[i].scale_x = particles[i].base_scale_x;
						particles[i].scale_y = particles[i].base_scale_y;
						particles[i].tr_angle = particles[i].base_tr_angle;
						particles[i].color = particles[i].base_color;
						particles[i].velocity = particles[i].base_velocity;
						particles[i].rot_angle = particles[i].base_rot_angle;
					
						for (j = 0; j < frame_layers_len; j++)
						{
						
							if (frame_layers[j].data_len > 0)
							{

								if (particles[i].current_frame >= frame_layers[j].data[particles[i].current_frame_indices[j]].duration)
								{
									particles[i].base_center_x = particles[i].base_center_x + frame_layers[j].data[particles[i].current_frame_indices[j]].center_x;
									particles[i].base_center_y = particles[i].center_y + frame_layers[j].data[particles[i].current_frame_indices[j]].center_y;
									particles[i].base_scale_x =  particles[i].base_scale_x + frame_layers[j].data[particles[i].current_frame_indices[j]].scale_x;
									particles[i].base_scale_y = particles[i].base_scale_y + frame_layers[j].data[particles[i].current_frame_indices[j]].scale_y;
									particles[i].base_tr_angle = particles[i].base_tr_angle + frame_layers[j].data[particles[i].current_frame_indices[j]].tr_angle;
									particles[i].base_rot_angle = particles[i].base_rot_angle + frame_layers[j].data[particles[i].current_frame_indices[j]].rot_angle;
									particles[i].base_velocity = particles[i].base_velocity + frame_layers[j].data[particles[i].current_frame_indices[j]].velocity;
									particles[i].base_color.r = particles[i].base_color.r + frame_layers[j].data[particles[i].current_frame_indices[j]].tint_r;
									particles[i].base_color.g = particles[i].base_color.g + frame_layers[j].data[particles[i].current_frame_indices[j]].tint_g;
									particles[i].base_color.b = particles[i].base_color.b + frame_layers[j].data[particles[i].current_frame_indices[j]].tint_b;
									particles[i].base_color.a = particles[i].base_color.a + frame_layers[j].data[particles[i].current_frame_indices[j]].tint_a;

									particles[i].center_x = particles[i].base_center_x;
									particles[i].center_y = particles[i].base_center_y;
									particles[i].scale_x = particles[i].base_scale_x;
									particles[i].scale_y = particles[i].base_scale_y;
									particles[i].tr_angle = particles[i].base_tr_angle;
									particles[i].color = particles[i].base_color;
									particles[i].velocity = particles[i].base_velocity;
									particles[i].rot_angle = particles[i].base_rot_angle;
								
									particles[i].current_frame_indices[j]++;

									if (particles[i].current_frame_indices[j] >= frame_layers[j].data_len) 
										particles[i].current_frame_indices[j] = 0;

									particles[i].current_frame = 0;
								}

								int index = particles[i].current_frame_indices[j];

								int b_index = (index > 0) ? index - 1 : 0;
								float delta = particles[i].current_frame / frame_layers[j].data[index].duration;

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

			for (uint64_t i = 0; i < particles_len; i++)
			{
					if (particles[i].visible)
						al_draw_tinted_scaled_rotated_bitmap_region(
																	particle_tex, 
																	p_region_x, 
																	p_region_y, 
																	p_region_width, 
																	p_region_height, 
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

			pa->current_frame = 0;
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

			pa->base_tr_angle = pa->tr_angle;
			pa->base_scale_x = pa->scale_x;
			pa->base_scale_y = pa->scale_y;
			pa->base_velocity = pa->velocity;
			pa->base_center_x = pa->center_x;
			pa->base_center_y = pa->center_y;
			pa->base_rot_angle = pa->rot_angle;
			pa->base_color = pa->color;
			

			for (int i = 0; i < frame_layers_len; i++)
				pa->current_frame_indices[i] = 0;
			

			pa->visible = false;
		}

		void ParticleEngine::set_particle_tex(ALLEGRO_BITMAP* new_tex)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (particle_tex != NULL)
				al_destroy_bitmap(particle_tex);

			if (new_tex != NULL)
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
					al_free(frame_layers[i].data);
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
					al_free(frame_layers[i].data);

				al_free(frame_layers);
			}
			
			for (uint64_t i = 0; i < particles_len; i++)
			{
				if ((frame_layers_len == 0) && (amount > 0))
					particles[i].current_frame_indices = (int*)al_malloc(sizeof(int) * amount);
				else if ((amount > 0) && (amount < frame_layers_len))
				{
					particles[i].current_frame_indices = (int*)al_realloc(particles[i].current_frame_indices, sizeof(int) * amount);
				}
				else if ((amount > 0) && (amount > frame_layers_len))
				{
					particles[i].current_frame_indices = (int*)al_realloc(particles[i].current_frame_indices, sizeof(int) * amount);
					for (int j = frame_layers_len - 1; j < amount; j++)
						particles[j].current_frame_indices = 0;
				}
				else if ((frame_layers_len > 0) && (amount == 0))
					al_free(particles[i].current_frame_indices);
			}

			frame_layers_len = amount;

			emit();
		}

		void ParticleEngine::add_frame_to_layer(int layer_index, float duration, float scale_x, float scale_y, float tr_angle, float rot_angle, float velocity, float center_x, float center_y, float tint_r, float tint_g, float tint_b, float tint_a)
		{
			if (layer_index >= frame_layers_len) return;

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
			frame_layers[layer_index].data[frame_layers[layer_index].data_len - 1].duration = duration;
		}

		void ParticleEngine::remove_frame_from_layer(int layer_index, int frame_index)
		{
			if (layer_index >= frame_layers_len) return;
			if (frame_index >= frame_layers[layer_index].data_len) return;


			for(int i = frame_index; i < frame_layers[layer_index].data_len - 1; i++)
					frame_layers[layer_index].data[i] = frame_layers[layer_index].data[i + 1];
			
			frame_layers[layer_index].data = (EmitterFrameData*)al_realloc(frame_layers[layer_index].data, sizeof(EmitterFrameData) * --frame_layers[layer_index].data_len);
		}

		void ParticleEngine::clear_frames_from_layer(int layer_index)
		{
			if (layer_index >= frame_layers_len) return;

			frame_layers[layer_index].data_len = 0;

			al_free(frame_layers[layer_index].data);
		}

		/* Get/Set Ops */
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

			em_type = type;
		}

		void ParticleEngine::set_particles_num(uint64_t new_num)
		{
			RAGE_CHECK_DISPOSED(disposed);

			if (particles_len == 0)
			{
				particles = (Particle*)al_malloc(sizeof(Particle) * new_num);
				particles_len = new_num;

				emit();
			}
			else if (particles_len < new_num)
			{
				particles = (Particle*)al_realloc(particles, sizeof(Particle) * new_num);

				for (uint64_t i = particles_len - 1; i < new_num; i++)
					set_particle(&particles[i]);

				particles_len = new_num;
			}
			else
			{
				particles = (Particle*)al_realloc(particles, sizeof(Particle) * new_num);
				particles_len = new_num;
			}
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
		uint64_t ParticleEngine::get_particles_num(void)
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

		void ParticleEngine::dispose(void)
		{
			RAGE_CHECK_DISPOSED(disposed);			

			if (frame_layers_len > 0) set_frame_layers(0);
			
			if (particles_len > 0)
				particles_len = 0;

			al_free(particles);

			if (particle_tex != NULL)
				al_destroy_bitmap(particle_tex);

			disposed = true;
		}

		ParticleEngine::~ParticleEngine(void){ }
	}
}