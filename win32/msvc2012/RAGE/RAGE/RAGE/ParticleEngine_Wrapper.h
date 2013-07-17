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
			static VALUE rb_add_to_frame_layer(VALUE self, VALUE index, VALUE duration, VALUE scale_x, VALUE scale_y, VALUE tr_angle, VALUE rot_angle, VALUE velocity, VALUE center_x, VALUE center_y, VALUE tint_r, VALUE tint_g, VALUE tint_b, VALUE tint_a);
			static VALUE rb_dispose(VALUE self);
			static VALUE rb_disposed(VALUE self);
		public:
			static void load_ruby_class(void);
			static VALUE get_ruby_class(void);
			static VALUE new_ruby_class_instance(void);
		};

	}
}