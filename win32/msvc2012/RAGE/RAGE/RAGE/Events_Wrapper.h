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

#pragma once
#include "rage_standard_headers.h"

#if RAGE_COMPILE_EVENTS

namespace RAGE
{
	namespace Events
	{
		class EventsWrapper
		{
		private:
			static VALUE rb_register_event(VALUE self, VALUE entry);
			static VALUE rb_unregister_event(VALUE self, VALUE entry);
			static VALUE rb_event_is_registered(VALUE self, VALUE entry);
			static VALUE rb_clear_events(VALUE self, VALUE event_type);
			static VALUE rb_clear_events2(VALUE self);
			static VALUE rb_freeze_events(VALUE self);
			static VALUE rb_unfreeze_events(VALUE self);

			#if RAGE_COMPILE_KEYBOARD_EVENT
			static VALUE rb_process_keyboard(VALUE self, VALUE val);
			#endif

			#if RAGE_COMPILE_MOUSE_EVENT
			static VALUE rb_process_mouse(VALUE self, VALUE val);
			#endif

			#if RAGE_COMPILE_JOY_EVENT
			static VALUE rb_process_joystick(VALUE self, VALUE val);
			#endif

			#if RAGE_COMPILE_SCREEN_EVENT
			static VALUE rb_process_display(VALUE self, VALUE val);
			#endif

			static VALUE rb_get_events_array(VALUE self);
			static VALUE rb_update_events(VALUE self);
		public:
			static ALLEGRO_EVENT_QUEUE* get_queue(void);
			static void unregister_event(VALUE ev);
			static void init_queue(void);
			static void finalize_queue(void);
			static void load_wrappers(void);
		};
	}
}

#endif