begin

    bit = RAGE::Bitmap.new
    bit.load "particle.png"

	pe = RAGE::ParticleEngine.new(bit, 120, 40, true, 260, 260)
      pe.type = RAGE::Graphics::LINE_EMITTER
	pe.setParticleRegion(0, 0, 32, 32, true)
      pe.setFrameLayers(1)
      pe.addFrameToLayer(0, 5, 0, 0, Math::PI / 8, 0, 0, 0, 0, -1, -1, 0, 0)
      pe.addFrameToLayer(0, 5, 5, 5, -Math::PI / 8, 0, 0, 0, 0, 0, 0, 0, 0)
      pe.angle = Math::PI / 4
      pe.emitterLineWidth = 800
      pe.useBlending = false
      pe.emit
      pe.setBlenderAlpha RAGE::Graphics::ADD, RAGE::Graphics::BLEND_INV_SRC_COLOR, RAGE::Graphics::BLEND_INV_SRC_COLOR, RAGE::Graphics::SRC_MIN_DEST, RAGE::Graphics::BLEND_ALPHA, RAGE::Graphics::BLEND_INV_SRC_COLOR
	newTime = RAGE::Graphics.getTime()
	oldTime = newTime
      RAGE::Draw.setColor(1, 0, 0, 1)
      count = 0
	loop do  
       RAGE::Graphics.clear

	newTime = RAGE::Graphics.getTime()

     RAGE::Input.updateMouse()
    
     x1 = RAGE::Input.getMouseX
     y1 = RAGE::Input.getMouseY
     x2 = x1 + 50
     y2 = y1
     x3 = x1
     y3 = y1 + 50
     x4 = x2
     y4 = y3
     

     #RAGE::Draw.setColor(1, 1, 1, 1)
     RAGE::Draw.rectangle(x1, y1, x4, y4, 2)
     RAGE::Graphics.title = "x: #{x1}, y: #{y1}"
     # RAGE::Logic.boxVsBoxCollision?(x1, y1, 50, 50, 100, 100, 50, 50)
     bit.red = 1
    if RAGE::Logic.boxVsBoxCollision?(x1, y1, 50, 50, 100, 100, 50, 50) #RAGE::Logic.bitmapVsBitmapCollision?(150, 150, bit, x1, y1, bit) #RAGE::Logic.bitmapVsBoxCollision?(x1, y1, bit, 100, 100, 50, 50)
     RAGE::Draw.setColor(0, 0, 1, 1)
     RAGE::Draw.rectangle(100, 100, 150, 150, 2)
    end

     #bit.draw x1, y1
     #bit.draw 150, 150

     if pe.inCollision?(400, 400, 50, 50)
      RAGE::Draw.setColor(1, 1, 0, 1)
     else
      RAGE::Draw.setColor(1, 0, 0, 1)
     end 

      RAGE::Draw.rectangle(400, 400, 450, 450, 2)

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