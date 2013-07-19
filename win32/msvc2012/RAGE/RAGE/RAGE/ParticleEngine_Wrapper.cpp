#include "ParticleEngine_Wrapper.h"

namespace RAGE
{
	namespace Graphics
	{
		VALUE rb_rageParticleEngineClass;


		VALUE ParticleEngineWrapper::rb_alloc(VALUE self)
		{
			return Data_Wrap_Struct(self, 0, ParticleEngineWrapper::rb_destroy, new ParticleEngine());
		}

		void ParticleEngineWrapper::rb_destroy(void *ptr)
		{
			delete ptr;
		}

		VALUE ParticleEngineWrapper::rb_initialize(VALUE self, VALUE tex, VALUE count, VALUE duration, VALUE loop, VALUE x, VALUE y)
		{
			ParticleEngine *pe;
			Bitmap *bmp;
			Data_Get_Struct(self, ParticleEngine, pe);
			Data_Get_Struct(tex, Bitmap, bmp);
			
			pe->initialize(bmp->bitmap, NUM2LL(count), NUM2DBL(duration), (TYPE(loop) == T_TRUE), NUM2DBL(x), NUM2DBL(y));

			return self;
		}
		
		VALUE ParticleEngineWrapper::rb_emit(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->emit();

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_update(VALUE self, VALUE dt)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->update(NUM2DBL(dt));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_draw(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->draw();

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_dispose(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->dispose();

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_disposed(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return pe->disposed ? Qtrue : Qfalse;
		}

		VALUE ParticleEngineWrapper::rb_set_particle_region(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height, VALUE center_rot)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_region(NUM2DBL(x), NUM2DBL(y), FIX2UINT(width), FIX2UINT(height), TYPE(center_rot) == T_TRUE);

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_particle_bitmap(VALUE self, VALUE bitmap)
		{
			ParticleEngine *pe;
			Bitmap *bmp;
			Data_Get_Struct(self, ParticleEngine, pe);
			Data_Get_Struct(bitmap, Bitmap, bmp);

			pe->set_particle_tex(bmp->bitmap);

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_emitter_position(VALUE self, VALUE x, VALUE y)
		{
			ParticleEngine *pe;
			
			Data_Get_Struct(self, ParticleEngine, pe);
			
			pe->set_emitter_position(NUM2DBL(x), NUM2DBL(y));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_emitter_loop(VALUE self, VALUE val)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_loop(TYPE(val) == T_TRUE);

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_emitter_spread(VALUE self, VALUE spread)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_spread(NUM2DBL(spread));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_emitter_angle(VALUE self, VALUE angle)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_angle(NUM2DBL(angle));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_emitter_type(VALUE self, VALUE type)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_type(FIX2UINT(type));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_particle_num(VALUE self, VALUE new_num)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particles_num(NUM2LL(new_num));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_particle_num(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return LL2NUM(pe->get_particles_num());
		}

		VALUE ParticleEngineWrapper::rb_add_to_frame_layer(int argc, VALUE *args, VALUE self)
		{
			if (argc < 2) return Qnil;

			if (argc > 17) argc = 17;

			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);
			
			int layer_num = FIX2UINT(args[0]);
			float duration = NUM2DBL(args[1]);

			float conf[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

			for (int i = 2; i < argc; i++) 
				conf[i - 2] = NUM2DBL(args[i]);

			pe->add_frame_to_layer(layer_num, duration, conf[0], conf[1], conf[2], conf[3], conf[4], conf[5], conf[6], conf[7], conf[8], conf[9], conf[10], conf[11], conf[12], conf[13], conf[14]);

			return Qnil;
		}	

		VALUE ParticleEngineWrapper::rb_set_frame_layers(VALUE self, VALUE layer_num)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_frame_layers(FIX2UINT(layer_num));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_particle_pos(VALUE self, VALUE x, VALUE y)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_coords(NUM2DBL(x), NUM2DBL(y));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_line_width(VALUE self, VALUE val)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_emitter_line_width(NUM2DBL(val));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_line_width(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_line_width());
		}

		VALUE ParticleEngineWrapper::rb_set_rect_width(VALUE self, VALUE val)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_emitter_rectangle_width(NUM2DBL(val));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_rect_width(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_rectangle_width());
		}

		VALUE ParticleEngineWrapper::rb_set_rect_height(VALUE self, VALUE val)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_emitter_rectangle_height(NUM2DBL(val));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_rect_height(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_rectangle_height());
		}

		VALUE ParticleEngineWrapper::rb_set_inner_circle_radius(VALUE self, VALUE val)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_emitter_inner_circle_radius(NUM2DBL(val));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_inner_circle_radius(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_inner_circle_radius());
		}

		VALUE ParticleEngineWrapper::rb_set_outer_circle_radius(VALUE self, VALUE val)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_emitter_outer_circle_radius(NUM2DBL(val));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_outer_circle_radius(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_outer_circle_radius());
		}

		VALUE ParticleEngineWrapper::rb_set_blender(VALUE self, VALUE op, VALUE src, VALUE dst)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);
			
			pe->set_emitter_blend(FIX2UINT(op), FIX2UINT(src), FIX2UINT(dst));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_blender_alpha(VALUE self, VALUE op, VALUE src, VALUE dst, VALUE aop, VALUE asrc, VALUE adst)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);
			
			pe->set_emitter_blend_alpha(FIX2UINT(op), FIX2UINT(src), FIX2UINT(dst), FIX2UINT(aop), FIX2UINT(asrc),FIX2UINT(adst));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_set_use_blending(VALUE self, VALUE val)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_use_blending((TYPE(val) == T_TRUE));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_use_blending(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return pe->get_use_blending() ? Qtrue : Qfalse;
		}

		VALUE ParticleEngineWrapper::rb_box_collision(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return pe->box_collision(NUM2DBL(x), NUM2DBL(y), NUM2DBL(w), NUM2DBL(h)) ? Qtrue : Qfalse;
		}


		VALUE ParticleEngineWrapper::rb_set_particle_life(VALUE self, VALUE life)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_life(NUM2DBL(life));
		
			return Qnil;
		}


		VALUE ParticleEngineWrapper::rb_get_particle_life(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_life());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_life_add(VALUE self, VALUE life_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_life_add(NUM2DBL(life_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_life_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_life_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_appear_velocity(VALUE self, VALUE appear_velocity)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_appear_velocity(NUM2DBL(appear_velocity));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_appear_velocity(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_appear_velocity());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_velocity(VALUE self, VALUE velocity)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_velocity(NUM2DBL(velocity));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_velocity(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_velocity());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_velocity_add(VALUE self, VALUE velocity_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_velocity_add(NUM2DBL(velocity_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_velocity_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_velocity_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_frame_velocity(VALUE self, VALUE frame_velocity)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_frame_velocity(NUM2DBL(frame_velocity));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_frame_velocity(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_frame_velocity());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_frame_velocity_add(VALUE self, VALUE frame_velocity_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_frame_velocity_add(NUM2DBL(frame_velocity_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_frame_velocity_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_frame_velocity_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_rot_angle(VALUE self, VALUE rot_angle)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_rot_angle(NUM2DBL(rot_angle));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_rot_angle(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_rot_angle());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_rot_angle_add(VALUE self, VALUE rot_angle_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_rot_angle_add(NUM2DBL(rot_angle_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_rot_angle_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_rot_angle_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_scale_x(VALUE self, VALUE scale_x)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_scale_x(NUM2DBL(scale_x));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_scale_x(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_scale_x());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_scale_x_add(VALUE self, VALUE scale_x_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_scale_x_add(NUM2DBL(scale_x_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_scale_x_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_scale_x_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_scale_y(VALUE self, VALUE scale_y)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_scale_y(NUM2DBL(scale_y));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_scale_y(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_scale_y());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_scale_y_add(VALUE self, VALUE scale_y_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_scale_y_add(NUM2DBL(scale_y_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_scale_y_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_scale_y_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_center_x(VALUE self, VALUE center_x)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_center_x(NUM2DBL(center_x));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_center_x(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_center_x());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_center_x_add(VALUE self, VALUE center_x_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_center_x_add(NUM2DBL(center_x_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_center_x_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_center_x_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_center_y(VALUE self, VALUE center_y)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_center_y(NUM2DBL(center_y));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_center_y(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_center_y());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_center_y_add(VALUE self, VALUE center_y_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_center_y_add(NUM2DBL(center_y_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_center_y_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_center_y_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tr_angle_change(VALUE self, VALUE tr_angle_change)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tr_angle_change(NUM2DBL(tr_angle_change));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tr_angle_change(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tr_angle_change());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_delay(VALUE self, VALUE delay)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_delay(NUM2DBL(delay));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_delay(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_delay());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_delay_add(VALUE self, VALUE delay_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_delay_add(NUM2DBL(delay_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_delay_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_delay_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_r(VALUE self, VALUE tint_r)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_r(NUM2DBL(tint_r));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_r(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_r());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_r_add(VALUE self, VALUE tint_r_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_r_add(NUM2DBL(tint_r_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_r_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_r_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_g(VALUE self, VALUE tint_g)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_g(NUM2DBL(tint_g));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_g(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_g());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_g_add(VALUE self, VALUE tint_g_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_g_add(NUM2DBL(tint_g_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_g_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_g_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_b(VALUE self, VALUE tint_b)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_b(NUM2DBL(tint_b));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_b(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_b());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_b_add(VALUE self, VALUE tint_b_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_b_add(NUM2DBL(tint_b_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_b_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_b_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_a(VALUE self, VALUE tint_a)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_a(NUM2DBL(tint_a));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_a(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_a());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_tint_a_add(VALUE self, VALUE tint_a_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_tint_a_add(NUM2DBL(tint_a_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_tint_a_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_tint_a_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_x_add(VALUE self, VALUE x_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_x_add(NUM2DBL(x_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_x_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_x_add());
		}


		VALUE ParticleEngineWrapper::rb_set_particle_y_add(VALUE self, VALUE y_add)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_y_add(NUM2DBL(y_add));
		
			return Qnil;
		}

 
		VALUE ParticleEngineWrapper::rb_get_particle_y_add(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_particle_y_add());
		}

		VALUE ParticleEngineWrapper::rb_set_particle_burst_amount(VALUE self, VALUE burst_amount)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_burst_amount(NUM2LL(burst_amount));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_particle_burst_amount(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return LL2NUM(pe->get_particle_burst_amount());
		}

		VALUE ParticleEngineWrapper::rb_set_emitter_burst(VALUE self, VALUE emitter_burst)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_emitter_burst(TYPE(emitter_burst) == T_TRUE);

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_emitter_burst(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return pe->get_emitter_burst() ? Qtrue : Qfalse;
		}

		VALUE ParticleEngineWrapper::rb_set_particle_region_instant_update(VALUE self, VALUE update)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->set_particle_region_instant_update(TYPE(update) == T_TRUE);

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_particle_region_instant_update(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return pe->get_particle_region_instant_update() ? Qtrue : Qfalse;
		}

		VALUE ParticleEngineWrapper::rb_remove_frame_from_layer(VALUE self, VALUE layer_index, VALUE frame_index)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->remove_frame_from_layer(FIX2UINT(layer_index), FIX2UINT(frame_index));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_clear_frames_from_layer(VALUE self, VALUE layer_index)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->clear_frames_from_layer(FIX2UINT(layer_index));

			return Qnil;
		}

		VALUE ParticleEngineWrapper::rb_get_loop(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return pe->get_emitter_loop() ? Qtrue : Qfalse;
		}

		VALUE ParticleEngineWrapper::rb_get_spread(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_spread());
		}

		VALUE ParticleEngineWrapper::rb_get_type(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_type());
		}

		VALUE ParticleEngineWrapper::rb_get_angle(VALUE self)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			return DBL2NUM(pe->get_emitter_angle());
		}

		void ParticleEngineWrapper::load_ruby_class(void)
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE g = rb_define_module_under(rage, "Graphics");

			rb_define_const(g, "POINT_EMITTER", INT2FIX(RAGE_POINT_EMITTER));
			rb_define_const(g, "LINE_EMITTER", INT2FIX(RAGE_LINE_EMITTER));
			rb_define_const(g, "RECTANGLE_EMITTER", INT2FIX(RAGE_RECT_EMITTER));
			rb_define_const(g, "CIRCLE_EMITTER", INT2FIX(RAGE_CIRCLE_EMITTER));
			rb_define_const(g, "RING_EMITTER", INT2FIX(RAGE_RING_EMITTER));

			rb_rageParticleEngineClass = rb_define_class_under(rage, "ParticleEngine", rb_cObject);

			rb_define_alloc_func(rb_rageParticleEngineClass, ParticleEngineWrapper::rb_alloc);

			rb_define_method(rb_rageParticleEngineClass, "initialize", RFUNC(ParticleEngineWrapper::rb_initialize), 6);
			rb_define_method(rb_rageParticleEngineClass, "emit", RFUNC(ParticleEngineWrapper::rb_emit), 0);
			rb_define_method(rb_rageParticleEngineClass, "update", RFUNC(ParticleEngineWrapper::rb_update), 1);
			rb_define_method(rb_rageParticleEngineClass, "draw", RFUNC(ParticleEngineWrapper::rb_draw), 0);
			rb_define_method(rb_rageParticleEngineClass, "setParticleRegion", RFUNC(ParticleEngineWrapper::rb_set_particle_region), 5);
			rb_define_method(rb_rageParticleEngineClass, "setEmitterOffset", RFUNC(ParticleEngineWrapper::rb_set_particle_pos), 2);
			rb_define_method(rb_rageParticleEngineClass, "setEmitterPosition", RFUNC(ParticleEngineWrapper::rb_set_emitter_position), 2);
			rb_define_method(rb_rageParticleEngineClass, "emitterLineWidth=", RFUNC(ParticleEngineWrapper::rb_set_line_width), 1);
			rb_define_method(rb_rageParticleEngineClass, "emitterLineWidth", RFUNC(ParticleEngineWrapper::rb_get_line_width), 0);
			rb_define_method(rb_rageParticleEngineClass, "emitterRectWidth=", RFUNC(ParticleEngineWrapper::rb_set_rect_width), 1);
			rb_define_method(rb_rageParticleEngineClass, "emitterRectWidth", RFUNC(ParticleEngineWrapper::rb_get_rect_width), 0);
			rb_define_method(rb_rageParticleEngineClass, "emitterRectHeight=", RFUNC(ParticleEngineWrapper::rb_set_rect_height), 1);
			rb_define_method(rb_rageParticleEngineClass, "emitterRectHeight", RFUNC(ParticleEngineWrapper::rb_get_rect_height), 0);
			rb_define_method(rb_rageParticleEngineClass, "emitterInnerCircleRadius=", RFUNC(ParticleEngineWrapper::rb_set_inner_circle_radius), 1);
			rb_define_method(rb_rageParticleEngineClass, "emitterInnerCircleRadius", RFUNC(ParticleEngineWrapper::rb_get_inner_circle_radius), 0);
			rb_define_method(rb_rageParticleEngineClass, "emitterOuterCircleRadius=", RFUNC(ParticleEngineWrapper::rb_set_outer_circle_radius), 1);
			rb_define_method(rb_rageParticleEngineClass, "emitterOuterCircleRadius", RFUNC(ParticleEngineWrapper::rb_get_outer_circle_radius), 0);
			rb_define_method(rb_rageParticleEngineClass, "useBlending=", RFUNC(ParticleEngineWrapper::rb_set_use_blending), 1);
			rb_define_method(rb_rageParticleEngineClass, "useBlending", RFUNC(ParticleEngineWrapper::rb_get_use_blending), 0);
			rb_define_method(rb_rageParticleEngineClass, "setBlender", RFUNC(ParticleEngineWrapper::rb_set_blender), 3);
			rb_define_method(rb_rageParticleEngineClass, "setBlenderAlpha", RFUNC(ParticleEngineWrapper::rb_set_blender), 6);
			rb_define_method(rb_rageParticleEngineClass, "particleBitmap=", RFUNC(ParticleEngineWrapper::rb_set_particle_bitmap), 1);
			rb_define_method(rb_rageParticleEngineClass, "loop=", RFUNC(ParticleEngineWrapper::rb_set_emitter_loop), 1);
			rb_define_method(rb_rageParticleEngineClass, "spread=", RFUNC(ParticleEngineWrapper::rb_set_emitter_spread), 1);
			rb_define_method(rb_rageParticleEngineClass, "angle=", RFUNC(ParticleEngineWrapper::rb_set_emitter_angle), 1);
			rb_define_method(rb_rageParticleEngineClass, "type=", RFUNC(ParticleEngineWrapper::rb_set_emitter_type), 1);
			rb_define_method(rb_rageParticleEngineClass, "loop", RFUNC(ParticleEngineWrapper::rb_get_loop), 0);
			rb_define_method(rb_rageParticleEngineClass, "spread", RFUNC(ParticleEngineWrapper::rb_get_spread), 0);
			rb_define_method(rb_rageParticleEngineClass, "angle", RFUNC(ParticleEngineWrapper::rb_get_angle), 0);
			rb_define_method(rb_rageParticleEngineClass, "type", RFUNC(ParticleEngineWrapper::rb_get_type), 0);
			rb_define_method(rb_rageParticleEngineClass, "maxParticles=", RFUNC(ParticleEngineWrapper::rb_set_particle_num), 1);
			rb_define_method(rb_rageParticleEngineClass, "maxParticles", RFUNC(ParticleEngineWrapper::rb_get_particle_num), 0);
			rb_define_method(rb_rageParticleEngineClass, "setFrameLayers", RFUNC(ParticleEngineWrapper::rb_set_frame_layers), 1);
			rb_define_method(rb_rageParticleEngineClass, "addFrameToLayer", RFUNC(ParticleEngineWrapper::rb_add_to_frame_layer), -1);
			rb_define_method(rb_rageParticleEngineClass, "removeFrameFromLayer", RFUNC(ParticleEngineWrapper::rb_remove_frame_from_layer), 2);
			rb_define_method(rb_rageParticleEngineClass, "clearFramesFromLayer", RFUNC(ParticleEngineWrapper::rb_clear_frames_from_layer), 1);
			
			rb_define_method(rb_rageParticleEngineClass, "inCollision?", RFUNC(ParticleEngineWrapper::rb_box_collision), 4);
			
			rb_define_method(rb_rageParticleEngineClass, "particleLife=", RFUNC(ParticleEngineWrapper::rb_set_particle_life), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleLife", RFUNC(ParticleEngineWrapper::rb_get_particle_life), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleLifeAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_life_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleLifeAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_life_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleAppearVelocity=", RFUNC(ParticleEngineWrapper::rb_set_particle_appear_velocity), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleAppearVelocity", RFUNC(ParticleEngineWrapper::rb_get_particle_appear_velocity), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleVelocity=", RFUNC(ParticleEngineWrapper::rb_set_particle_velocity), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleVelocity", RFUNC(ParticleEngineWrapper::rb_get_particle_velocity), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleVelocityAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_velocity_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleVelocityAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_velocity_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleFrameVelocity=", RFUNC(ParticleEngineWrapper::rb_set_particle_frame_velocity), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleFrameVelocity", RFUNC(ParticleEngineWrapper::rb_get_particle_frame_velocity), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleFrameVelocityAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_frame_velocity_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleFrameVelocityAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_frame_velocity_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleRotAngle=", RFUNC(ParticleEngineWrapper::rb_set_particle_rot_angle), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleRotAngle", RFUNC(ParticleEngineWrapper::rb_get_particle_rot_angle), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleRotAngleAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_rot_angle_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleRotAngleAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_rot_angle_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleScaleX=", RFUNC(ParticleEngineWrapper::rb_set_particle_scale_x), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleScaleX", RFUNC(ParticleEngineWrapper::rb_get_particle_scale_x), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleScaleXAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_scale_x_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleScaleXAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_scale_x_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleScaleY=", RFUNC(ParticleEngineWrapper::rb_set_particle_scale_y), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleScaleY", RFUNC(ParticleEngineWrapper::rb_get_particle_scale_y), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleScaleYAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_scale_y_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleScaleYAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_scale_y_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleCenterX=", RFUNC(ParticleEngineWrapper::rb_set_particle_center_x), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleCenterX", RFUNC(ParticleEngineWrapper::rb_get_particle_center_x), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleCenterXAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_center_x_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleCenterXAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_center_x_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleCenterY=", RFUNC(ParticleEngineWrapper::rb_set_particle_center_y), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleCenterY", RFUNC(ParticleEngineWrapper::rb_get_particle_center_y), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleCenterYAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_center_y_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleCenterYAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_center_y_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTrAngleChange=", RFUNC(ParticleEngineWrapper::rb_set_particle_tr_angle_change), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTrAngleChange", RFUNC(ParticleEngineWrapper::rb_get_particle_tr_angle_change), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleDelay=", RFUNC(ParticleEngineWrapper::rb_set_particle_delay), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleDelay", RFUNC(ParticleEngineWrapper::rb_get_particle_delay), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleDelayAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_delay_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleDelayAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_delay_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintR=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_r), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintR", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_r), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintRAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_r_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintRAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_r_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintG=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_g), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintG", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_g), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintGAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_g_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintGAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_g_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintB=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_b), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintB", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_b), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintBAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_b_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintBAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_b_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintA=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_a), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintA", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_a), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleTintAAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_tint_a_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleTintAAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_tint_a_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleXAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_x_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleXAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_x_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleYAdd=", RFUNC(ParticleEngineWrapper::rb_set_particle_y_add), 1); 
			rb_define_method(rb_rageParticleEngineClass, "particleYAdd", RFUNC(ParticleEngineWrapper::rb_get_particle_y_add), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleBurstAmount=", RFUNC(ParticleEngineWrapper::rb_set_particle_burst_amount), 1);
			rb_define_method(rb_rageParticleEngineClass, "particleBurstAmount", RFUNC(ParticleEngineWrapper::rb_get_particle_burst_amount), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleBurst=", RFUNC(ParticleEngineWrapper::rb_set_emitter_burst), 1);
			rb_define_method(rb_rageParticleEngineClass, "particleBurst", RFUNC(ParticleEngineWrapper::rb_get_emitter_burst), 0);
			rb_define_method(rb_rageParticleEngineClass, "particleRegionInstantUpdate=", RFUNC(ParticleEngineWrapper::rb_set_particle_region_instant_update), 1);
			rb_define_method(rb_rageParticleEngineClass, "particleRegionInstantUpdate", RFUNC(ParticleEngineWrapper::rb_get_particle_region_instant_update), 0);
			rb_define_method(rb_rageParticleEngineClass, "dispose", RFUNC(ParticleEngineWrapper::rb_dispose), 0);
			rb_define_method(rb_rageParticleEngineClass, "disposed?", RFUNC(ParticleEngineWrapper::rb_disposed), 0);
		}

		VALUE ParticleEngineWrapper::get_ruby_class(void)
		{
			return rb_rageParticleEngineClass;
		}

		VALUE ParticleEngineWrapper::new_ruby_class_instance(void)
		{
			return rb_class_new_instance(0, NULL, rb_rageParticleEngineClass);
		}
	}
}
