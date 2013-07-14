#pragma once
#include "RubyInterpreter.h"

extern class BaseEvent
{
public:
	bool disposed;
	virtual void callback(ALLEGRO_EVENT *ev) = 0;
};

