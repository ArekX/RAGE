#include <iostream>
#include "ruby.h"


using namespace std;

/**
 * Main Initialize Function
 * Arguments:
 * argc, argv
**/
int main(char* args, int argv)
{
	ruby_sysinit(&argv, (char***)&args);
    {
		RUBY_INIT_STACK;
		ruby_init();
		ruby_init_loadpath();

		VALUE protected_objects = rb_hash_new();
		rb_gc_register_address(&protected_objects);

		rb_eval_string("puts 'Welcome to Ruby Awesome Game Engine! Written in C++, support to Ruby.'\n gets");
    }

	return 0;
}