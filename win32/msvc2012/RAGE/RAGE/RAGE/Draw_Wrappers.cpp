#define ALLEGRO_STATICLINK
#include "Draw_Wrappers.h"

namespace RAGE
{
	namespace Graphics
	{

		VALUE DrawWrappers::draw_line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE color, VALUE thickness)
		{
			al_draw_line(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), al_map_rgb(255, 255, 255), NUM2DBL(thickness));
			return Qnil;
		}

		VALUE DrawWrappers::map_color(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a)
		{
			return Qnil;
		}

		void DrawWrappers::load_wrappers()
		{
			VALUE rage = rb_define_module("RAGE");
			VALUE draw = rb_define_module_under(rage, "Draw");

			rb_define_module_function(draw, "line", RFUNC(DrawWrappers::draw_line), 6);
			rb_define_module_function(draw, "mapColor", RFUNC(NULL), 4);
		}
	}
}
