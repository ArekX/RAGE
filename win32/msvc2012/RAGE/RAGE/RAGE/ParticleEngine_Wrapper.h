#pragma once

#include "ParticleEngine.h"

namespace RAGE
{
	namespace Graphics
	{

		class ParticleEngineWrapper
		{
		private:
			static VALUE rb_alloc(VALUE self);
			static void rb_destroy(void *ptr);
			static VALUE rb_initialize(VALUE self, VALUE tex, VALUE count, VALUE duration, VALUE loop, VALUE x, VALUE y);
			static VALUE rb_emit(VALUE self);
			static VALUE rb_update(VALUE self, VALUE dt);
			static VALUE rb_draw(VALUE self);
			static VALUE rb_set_particle_region(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height, VALUE center_rot);
			static VALUE rb_set_particle_bitmap(VALUE self, VALUE bitmap);
			static VALUE rb_set_emitter_position(VALUE self, VALUE x, VALUE y);
			static VALUE rb_set_emitter_loop(VALUE self, VALUE val);
			static VALUE rb_set_emitter_spread(VALUE self, VALUE spread);
			static VALUE rb_set_emitter_angle(VALUE self, VALUE angle);
			static VALUE rb_set_emitter_type(VALUE self, VALUE type);
			static VALUE rb_get_loop(VALUE self);
			static VALUE rb_get_spread(VALUE self);
			static VALUE rb_get_type(VALUE self);
			static VALUE rb_get_angle(VALUE self);
			static VALUE rb_set_particle_num(VALUE self, VALUE new_num);
			static VALUE rb_set_frame_layers(VALUE self, VALUE layer_num);
			static VALUE rb_set_particle_pos(VALUE self, VALUE x, VALUE y);
			static VALUE rb_get_particle_num(VALUE self);
			static VALUE rb_set_line_width(VALUE self, VALUE val);
			static VALUE rb_get_line_width(VALUE self);
			static VALUE rb_set_rect_width(VALUE self, VALUE val);
			static VALUE rb_get_rect_width(VALUE self);
			static VALUE rb_set_rect_height(VALUE self, VALUE val);
			static VALUE rb_get_rect_height(VALUE self);
			static VALUE rb_set_inner_circle_radius(VALUE self, VALUE val);
			static VALUE rb_get_inner_circle_radius(VALUE self);
			static VALUE rb_set_outer_circle_radius(VALUE self, VALUE val);
			static VALUE rb_get_outer_circle_radius(VALUE self);
			static VALUE rb_set_blender(VALUE self, VALUE op, VALUE src, VALUE dst);
			static VALUE rb_set_blender_alpha(VALUE self, VALUE op, VALUE src, VALUE dst, VALUE aop, VALUE asrc, VALUE adst);
			static VALUE rb_set_use_blending(VALUE self, VALUE val);
			static VALUE rb_get_use_blending(VALUE self);
			static VALUE rb_add_to_frame_layer(int argc, VALUE *args, VALUE self);
			static VALUE rb_box_collision(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h);

			static VALUE rb_set_particle_life(VALUE self, VALUE life); 
			static VALUE rb_get_particle_life(VALUE self);
			static VALUE rb_set_particle_life_add(VALUE self, VALUE life_add); 
			static VALUE rb_get_particle_life_add(VALUE self);
			static VALUE rb_set_particle_appear_velocity(VALUE self, VALUE appear_velocity); 
			static VALUE rb_get_particle_appear_velocity(VALUE self);
			static VALUE rb_set_particle_velocity(VALUE self, VALUE velocity); 
			static VALUE rb_get_particle_velocity(VALUE self);
			static VALUE rb_set_particle_velocity_add(VALUE self, VALUE velocity_add); 
			static VALUE rb_get_particle_velocity_add(VALUE self);
			static VALUE rb_set_particle_frame_velocity(VALUE self, VALUE frame_velocity); 
			static VALUE rb_get_particle_frame_velocity(VALUE self);
			static VALUE rb_set_particle_frame_velocity_add(VALUE self, VALUE frame_velocity_add); 
			static VALUE rb_get_particle_frame_velocity_add(VALUE self);
			static VALUE rb_set_particle_rot_angle(VALUE self, VALUE rot_angle); 
			static VALUE rb_get_particle_rot_angle(VALUE self);
			static VALUE rb_set_particle_rot_angle_add(VALUE self, VALUE rot_angle_add); 
			static VALUE rb_get_particle_rot_angle_add(VALUE self);
			static VALUE rb_set_particle_scale_x(VALUE self, VALUE scale_x); 
			static VALUE rb_get_particle_scale_x(VALUE self);
			static VALUE rb_set_particle_scale_x_add(VALUE self, VALUE scale_x_add); 
			static VALUE rb_get_particle_scale_x_add(VALUE self);
			static VALUE rb_set_particle_scale_y(VALUE self, VALUE scale_y); 
			static VALUE rb_get_particle_scale_y(VALUE self);
			static VALUE rb_set_particle_scale_y_add(VALUE self, VALUE scale_y_add); 
			static VALUE rb_get_particle_scale_y_add(VALUE self);
			static VALUE rb_set_particle_center_x(VALUE self, VALUE center_x); 
			static VALUE rb_get_particle_center_x(VALUE self);
			static VALUE rb_set_particle_center_x_add(VALUE self, VALUE center_x_add); 
			static VALUE rb_get_particle_center_x_add(VALUE self);
			static VALUE rb_set_particle_center_y(VALUE self, VALUE center_y); 
			static VALUE rb_get_particle_center_y(VALUE self);
			static VALUE rb_set_particle_center_y_add(VALUE self, VALUE center_y_add); 
			static VALUE rb_get_particle_center_y_add(VALUE self);
			static VALUE rb_set_particle_delay(VALUE self, VALUE delay); 
			static VALUE rb_get_particle_delay(VALUE self);
			static VALUE rb_set_particle_delay_add(VALUE self, VALUE delay_add); 
			static VALUE rb_get_particle_delay_add(VALUE self);
			static VALUE rb_set_particle_tint_r(VALUE self, VALUE tint_r); 
			static VALUE rb_get_particle_tint_r(VALUE self);
			static VALUE rb_set_particle_tint_r_add(VALUE self, VALUE tint_r_add); 
			static VALUE rb_get_particle_tint_r_add(VALUE self);
			static VALUE rb_set_particle_tint_g(VALUE self, VALUE tint_g); 
			static VALUE rb_get_particle_tint_g(VALUE self);
			static VALUE rb_set_particle_tint_g_add(VALUE self, VALUE tint_g_add); 
			static VALUE rb_get_particle_tint_g_add(VALUE self);
			static VALUE rb_set_particle_tint_b(VALUE self, VALUE tint_b); 
			static VALUE rb_get_particle_tint_b(VALUE self);
			static VALUE rb_set_particle_tint_b_add(VALUE self, VALUE tint_b_add); 
			static VALUE rb_get_particle_tint_b_add(VALUE self);
			static VALUE rb_set_particle_tint_a(VALUE self, VALUE tint_a); 
			static VALUE rb_get_particle_tint_a(VALUE self);
			static VALUE rb_set_particle_tint_a_add(VALUE self, VALUE tint_a_add); 
			static VALUE rb_get_particle_tint_a_add(VALUE self);
			static VALUE rb_set_particle_x_add(VALUE self, VALUE x_add); 
			static VALUE rb_get_particle_x_add(VALUE self);
			static VALUE rb_set_particle_y_add(VALUE self, VALUE y_add); 
			static VALUE rb_get_particle_y_add(VALUE self);

			static VALUE rb_set_particle_burst_amount(VALUE self, VALUE burst_amount);
			static VALUE rb_get_particle_burst_amount(VALUE self);
			static VALUE rb_set_emitter_burst(VALUE self, VALUE emitter_burst);
			static VALUE rb_get_emitter_burst(VALUE self);

			static VALUE rb_set_particle_region_instant_update(VALUE self, VALUE update);
			static VALUE rb_get_particle_region_instant_update(VALUE self);

			static VALUE rb_remove_frame_from_layer(VALUE self, VALUE layer_index, VALUE frame_index);
			static VALUE rb_clear_frames_from_layer(VALUE self, VALUE layer_index);

			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};

	}
}