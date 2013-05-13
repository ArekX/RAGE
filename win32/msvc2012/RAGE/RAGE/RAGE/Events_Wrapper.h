#pragma once
#include "RubyInterpreter.h"

namespace RAGE
{
	namespace Events
	{
		class EventsWrapper
		{
		private:
			 static VALUE rb_update_events(VALUE self);
			 static VALUE rb_get_key(VALUE self);
		public:
			static ALLEGRO_EVENT_QUEUE* get_queue();
			static void init_queue();
			static void finalize_queue();
			static void load_wrappers();
		};
	}
}

