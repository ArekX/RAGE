#pragma once
#include "RubyInterpreter.h"

extern class BaseEvent
{
protected:
	bool disposed;
public:
	virtual void callback(ALLEGRO_EVENT *ev) = 0;

	bool is_disposed() {
	   return disposed;	
	};
};

