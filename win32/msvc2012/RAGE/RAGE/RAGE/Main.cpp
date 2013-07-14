#include "RubyInterpreter.h"

/**
 * Main Initialize Function
 * Arguments:
 * argc, argv
**/
int main(int argc, char** argv)
{
	/* Initialize Allegro Game Library */
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
    al_install_keyboard();
	al_install_joystick();
	al_install_audio();
	al_init_acodec_addon();

	#ifdef DEVELOPMENT_VERSION
	SetConsoleTitle(L"RAGE Development Console");
	#endif

    //	     RAGE::Physics (Box2D) module

	// LATER: RM versions? Or adjust scripts towards RAGE?

	/*
		[ RAGE 1.0.0, stable version ]
		- Audio will not be initialized if it is not needed.
		- RAGE::Audio::Mixer - class for creating sound mixers
		- RAGE::Audio::Voice - class for creating voices
		- RAGE::Audio::Synth - class for sound synthesis [maybe?]
		- RAGE::MIDI - class for loading and playing midi files.
		- Physics FS loading saving custom files. RAGE::File class.
			- RAGE::File.new(filename, mode)
			- RAGE::File.write make it like File.write, check endinaness
			- RAGE::File.writeXXX where XXX is BYT, WRD, DWR, QWR (2 DWR)
			- RAGE::File.readXXX() where XXX is same as write.
			- RAGE::File.setEndian(endianType) - RAGE::FS::LITTLE_ENDIAN, RAGE::FS::BIG_ENDIAN.
			- RAGE::FS::SEEK_SET, RAGE::FS::SEEK_CUR, RAGE::FS::SEEK_END
			- RAGE::File.seek(position, from)
			- RAGE::File.size() <- -1 if write mode.
			- RAGE::FS.fileSize(filename) <- -1 if cannot be determined.
			- RAGE::File.read([amount]) <- if amount not set use gvl threads, check endinaness
			- RAGE::File.close() <- or RAGE::File.dispose()
		- RAGE.require - should hold a list of loaded files, not to load them again.
		- Documentation needs to be written in Markdown
		- Add optional arguments to constructors of color, font, bitmap, music, sfx, inifile, ...
		- Add Particle Effects functionality - RAGE::ParticleEngine
			- RAGE::ParticleEngine.new(particleImage, amount, particleType)
			- RAGE::ParticleEngine.image
			- RAGE::ParticleEngine.amount
			- RAGE::ParticleEngine.particleType
			- RAGE::ParticleEngine.update()
			- RAGE::ParticleEngine.draw(x, y)
			- ...more functionality...
		- Add Socket functionality - RAGE::Net module.
			- RAGE::Net::TCP
			- RAGE::Net::UDP
			- RAGE::Net::Socket
			- RAGE::Net.downloadFile(uri, filename) - downloads and saves downloaded data to filename, returns success boolean
			- RAGE::Net.downloadString(uri) - downloads and returns downloaded string, returns string or "" on fail
		- Box2D physics - RAGE::Physics::World.new, RAGE::Physics::PulleyJoint...
		- add frameless option in conf.rb and RAGE
		- RAGE::Draw.getColorO(color)
		- RAGE::Draw.getColor() - returns color clone
		- RAGE::Draw.textBox(xStart, y, xEnd, text) - draws word-wrapped text.
		- RAGE::Graphics.getBackgroundColor()
		- RAGE::Graphics.getBackgroundColorO(color)
		- RAGE::Draw.getFont() - returns font clone.
		- RAGE::Draw.getFontO(font)
		- RAGE::Font.clone() - try memcpy
		- RAGE::IniFile.clone()
		- RAGE::Font.textHeight() should return - al_get_font_ascent()
		- RAGE::Color.clone()
		- RAGE::Font.createBuiltin()
		- fixup  config checking, make so that when load wrappers or load ruby class is called that it is checked then! And try to make a copy of config hash so that everyone can check (ie lose some dependency on ruby interpreter)
		- all event classes should have - isRegistered?
		- add more passing to GLSL - refer http://nehe.gamedev.net/article/glsl_an_introduction/25007/
		- check new_ruby_class_instance() - should return with required arguments where needed.
		- Free initialized hidden allegro variables.
	*/

	/*  Init PHYS_FS */
	PHYSFS_init(argv[0]);

	/* Initialize and start Interpreter */
	RAGE::Interpreter::Ruby ri(argc, argv);

	/* Destroy event queue */
	RAGE::Events::EventsWrapper::finalize_queue();

	PHYSFS_deinit();

	/* Close down allegro game system */
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_joystick();
	al_uninstall_audio();
	al_uninstall_system();

	return 0;
}

