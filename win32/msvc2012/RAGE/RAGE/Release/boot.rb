begin

    bit = RAGE::Bitmap.new
    bit.load "particle.png"

	pe = RAGE::ParticleEngine.new(bit, 250, 40, true, 260, 260)
      pe.type = RAGE::Graphics::LINE_EMITTER
	pe.setParticleRegion(0, 0, 32, 32, true)
      pe.setFrameLayers(0)
      pe.addFrameToLayer(0, 5, 0, 0, Math::PI / 8, 0, 0, 0, 0, -1, -1, 0, 0)
      pe.addFrameToLayer(0, 5, 0, 0, -Math::PI / 8, 0, 0, 0, 0, 0, 0, 0, 0)
      pe.angle = Math::PI / 4
      pe.emitterLineWidth = 800
      pe.useBlending = true
      pe.emit
      pe.setBlenderAlpha RAGE::Graphics::ADD, RAGE::Graphics::BLEND_INV_SRC_COLOR, RAGE::Graphics::BLEND_INV_SRC_COLOR, RAGE::Graphics::SRC_MIN_DEST, RAGE::Graphics::BLEND_ALPHA, RAGE::Graphics::BLEND_INV_SRC_COLOR
	newTime = RAGE::Graphics.getTime()
	oldTime = newTime
      RAGE::Draw.setColor(1, 0, 0, 1)
	loop do  
       RAGE::Graphics.clear

	newTime = RAGE::Graphics.getTime()
	

      pe.update((newTime - oldTime) * 5)
      pe.draw()
      RAGE::Draw.text(300, 300, "Hellou! :D")
      RAGE::Input.updateKeyboard()

      oldTime = newTime

      pe.emit if RAGE::Input.keyDown?(RAGE::Input::KEY_E)

      break if RAGE::Input.keyDown?(RAGE::Input::KEY_ESCAPE)

       RAGE::Graphics.update
	end

rescue Exception => e  
	unless e.message == "exit"
		puts "\n\nError:\n\t\n" + e.message
		puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
		gets
	end
end