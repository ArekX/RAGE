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
			free((ParticleEngine*)ptr);
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

		VALUE ParticleEngineWrapper::rb_add_to_frame_layer(VALUE self, VALUE index, VALUE duration, VALUE scale_x, VALUE scale_y, VALUE tr_angle, VALUE rot_angle, VALUE velocity, VALUE center_x, VALUE center_y, VALUE tint_r, VALUE tint_g, VALUE tint_b, VALUE tint_a)
		{
			ParticleEngine *pe;
			Data_Get_Struct(self, ParticleEngine, pe);

			pe->add_frame_to_layer(FIX2UINT(index), NUM2DBL(duration), NUM2DBL(scale_x), NUM2DBL(scale_y), NUM2DBL(tr_angle), NUM2DBL(rot_angle), NUM2DBL(velocity), NUM2DBL(center_x), NUM2DBL(center_y), NUM2DBL(tint_r), NUM2DBL(tint_g), NUM2DBL(tint_b), NUM2DBL(tint_a));

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
			rb_define_method(rb_rageParticleEngineClass, "setParticlePosition", RFUNC(ParticleEngineWrapper::rb_set_particle_pos), 2);
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
			rb_define_method(rb_rageParticleEngineClass, "maxParticles=", RFUNC(ParticleEngineWrapper::rb_set_particle_num), 1);
			rb_define_method(rb_rageParticleEngineClass, "maxParticles", RFUNC(ParticleEngineWrapper::rb_get_particle_num), 0);
			rb_define_method(rb_rageParticleEngineClass, "setFrameLayers", RFUNC(ParticleEngineWrapper::rb_set_frame_layers), 1);
			rb_define_method(rb_rageParticleEngineClass, "addFrameToLayer", RFUNC(ParticleEngineWrapper::rb_add_to_frame_layer), 13);
			rb_define_method(rb_rageParticleEngineClass, "inCollision?", RFUNC(ParticleEngineWrapper::rb_box_collision), 4);
			
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
