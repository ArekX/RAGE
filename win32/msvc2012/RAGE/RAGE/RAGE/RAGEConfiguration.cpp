#include "RAGEConfiguration.h"

namespace RAGE
{
	RAGEConfiguration::RAGEConfiguration(VALUE conf_hash)
	{
		is_default = false;

		if (conf_hash == 0) 
		{
			is_default = true;
			return;
		}
		else
			hash = conf_hash;

		rb_gc_register_address(&hash);
	}

	bool RAGEConfiguration::is_on(char* name)
	{
		if (is_default) return true;

		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2(name));

		if (TYPE(item) == T_NIL)
			return true;
		else
			return (TYPE(item) == T_TRUE);
	}

	void RAGEConfiguration::set_game_name(char* set_name)
	{
		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("name"));

		if (is_default || (TYPE(item) == T_NIL))
			strcpy(set_name, "RAGE Game");
		else
			strcpy(set_name, StringValueCStr(item));
	}
	int RAGEConfiguration::get_screen_width(void)
	{
		if (is_default) return 640;

		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("width"));

		if (TYPE(item) != T_NIL)
			return FIX2UINT(item);
		else
			return 640;
	}

	int RAGEConfiguration::get_screen_height(void)
	{
		if (is_default) return 480;

		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("height"));

		if (TYPE(item) != T_NIL)
			return FIX2UINT(item);
		else
			return 480;
	}

	bool RAGEConfiguration::fullscreen_on(void)
	{
		if (is_default) return false;

		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("fullscreen"));

		if (TYPE(item) == T_NIL)
			return false;
		else
			return (TYPE(item) == T_TRUE);
	}

	bool RAGEConfiguration::vsync_on(void)
	{
		if (is_default) return false;

		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("vsync"));

		if (TYPE(item) == T_NIL)
			return false;
		else
			return (TYPE(item) == T_TRUE);
	}

	bool RAGEConfiguration::maximized_on(void)
	{
		if (is_default) return false;

		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("maximizedWindow"));

		if (TYPE(item) == T_NIL)
			return false;
		else
			return (TYPE(item) == T_TRUE);
	}

	bool RAGEConfiguration::frameless_on(void)
	{
		if (is_default) return false;

		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("framelessWindow"));

		if (TYPE(item) == T_NIL)
			return false;
		else
			return (TYPE(item) == T_TRUE);
	}

	bool RAGEConfiguration::is_current_version(void)
	{
		VALUE item;
		if (hash != NULL)
			item = rb_hash_aref(hash, rb_str_new2("version"));

		if (TYPE(item) != T_NIL)
			return (strcmp(RAGE_ENGINE_VERSION, StringValueCStr(item)) == 0);
		else
			return true;
	}

	RAGEConfiguration::~RAGEConfiguration(void)
	{
		rb_gc_unregister_address(&hash);
	}
}