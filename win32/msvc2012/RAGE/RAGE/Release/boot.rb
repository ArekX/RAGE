begin
	RAGE.about
	
	
	m = RAGE::Bitmap.new
	
	
	font = RAGE::Font.new
	font.load "acmesa.ttf", 120
	RAGE::Draw.setFont(font)
	
	
	cl = RAGE::Color.new
	cl.setName("blue")
	
	
	RAGE::Draw.setColorO(cl)
	
	str = "Hello World from RAGE!"

	#width = font.textWidth str
	#height = font.textHeight
	#RAGE::Draw.setFont(font)
	
	w = font.textWidth str
	h = font.textHeight
	
	m.create w, h
	
	
	RAGE::Graphics.setTarget(m)
	
	RAGE::Draw.text(0, 0, str)
	
	RAGE::Graphics.setTarget(nil)
	
	screen = RAGE::ScreenEvent.new
	screen.register RAGE::Events::SCREEN_CLOSE, Proc.new{
		Kernel::exit(0)
	}
	RAGE::Events.register screen
	
	scrBit = RAGE::Graphics.getTarget
	
	screenW = scrBit.width
	screenH = scrBit.height
	
	m.centerX = m.width / 2
	m.centerY = m.height / 2
	
	RAGE::Graphics.setBlendingMode RAGE::Graphics::ADD, RAGE::Graphics::BLEND_ALPHA, RAGE::Graphics::BLEND_INV_ALPHA
	
	rot = 0
	anim = 0
	
	updown = false
	
	x, y = 0, 0
	
	ltime = RAGE::Graphics.getTime
	dt = 0

	m.setTint(255, 255, 255, 100)
	d = RAGE::Bitmap.new
	d.load "icon.png"
	RAGE::Graphics.setIcon(d)
	

	d.scaleX = 6.25
	d.scaleY = 4.6875
	d.alpha = 0.2
	
	loop do
		RAGE::Graphics.clear
		d.draw(0, 0)
		dt = RAGE::Graphics.getTime - ltime
		ltime = RAGE::Graphics.getTime


		m.scaleX = anim
		m.scaleY = anim
		
		if anim < 5 && !updown
			anim += 0.005
			updown = true if anim > 4
		end
		
		if anim >= 0 && updown
			anim -= 0.005
			updown = false if anim < 0
		end
		  
		
		m.alpha = 0.2
		m.draw(screenW / 2 - m.width / 2 + 200 + x + 2 * Math.cos(rot), screenH / 2 - m.height / 2 + y + 80 * Math.sin(rot))
		m.alpha = 0.3
		m.draw(screenW / 2 - m.width / 2 + 200 + x + 2 * Math.cos(rot), screenH / 2 - m.height / 2 + y + 60 * Math.sin(rot))
		m.alpha = 0.5
		m.draw(screenW / 2 - m.width / 2 + 200 + x + 2 * Math.cos(rot), screenH / 2 - m.height / 2 + y + 40 * Math.sin(rot))
		m.alpha = 0.9
		m.draw(screenW / 2 - m.width / 2 + 200 + x + 2 * Math.cos(rot), screenH / 2 - m.height / 2 + y + 20 * Math.sin(rot))
		rot = (rot + (1 * dt) * Math::PI / 180) % (2 * Math::PI)
		
		m.angle = (m.angle + (50 * dt) * Math::PI / 180) % (2 * Math::PI)
		
		y += (100 * dt) if RAGE::Input.keyRepeat?(RAGE::Input::KEY_DOWN)
		y -= (100 * dt) if RAGE::Input.keyRepeat?(RAGE::Input::KEY_UP)
		x += (100 * dt) if RAGE::Input.keyRepeat?(RAGE::Input::KEY_RIGHT)
		x -= (100 * dt) if RAGE::Input.keyRepeat?(RAGE::Input::KEY_LEFT)
		
		break if RAGE::Input.keyRepeat?(RAGE::Input::KEY_ESC)

		if RAGE::Input.keyRepeat?(RAGE::Input::KEY_ALT) && RAGE::Input.keyDown?(RAGE::Input::KEY_ENTER)
			RAGE::Graphics.setFullscreen(true) 
			m.recreate
		end

		RAGE::Input.updateKeyboard
		RAGE::Graphics.update
	end
	
rescue Exception => e  
	unless e.message == "exit"
		puts "\n\nBoot.rb Error:\n\t\n" + e.message
		puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
		gets
	end

end