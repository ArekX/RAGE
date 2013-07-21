RAGE.require "rage_utils.rb"
RAGE.require "rage_utils.rb"
RAGE.require "rage_utils.rb"
RAGE.require "rage_utils.rb"
begin
    $close = false
    register_close_button {
      $close = true
    }

    # Load particle
    bit = RAGE::Bitmap.new
    bit.load "particle.png"

    # Initialize particle engine object
    pe = RAGE::ParticleEngine.new bit, 300, 25, true, 500, 500
    pe.setParticleRegion 0, 0, 32, 32, true

    pe.particleBurst = true
    pe.particleBurstAmount = 300
    # Add animation data for particle

    # .addToFrameLayer(layerIndex, frameDuration [, addScaleX, addScaleY, addTrajectoryAngle, addRotationAngle,
    #                  addSpeed, addCenterX, addCenterY, addParticleRegionX, addParticleRegionY, 
    #                  addParticleRegionWidth, addParticleRegionHeight, addParticleTintRed, addParticleTintGreen,
    #                  addParticleTintBlue])

    pe.setFrameLayers(2)
    pe.addFrameToLayer 0, 10, 2, 2, Math::PI
    pe.addFrameToLayer 0, 10, -2, -2, -Math::PI
    pe.addFrameToLayer 0, 10
    pe.addFrameToLayer 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.4, -0.5, -1, -0.2
    pe.addFrameToLayer 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.4, -0.5, -1, -0.2
    pe.addFrameToLayer 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.4, -0.5, -1, -0.2
    pe.particleFrameVelocity = 1.5

    # Get time from start of the egine
  	newTime = RAGE::Graphics.getTime()
  	oldTime = newTime
    dt = 0 # Initalize delta time

    RAGE::Draw.setColor(1, 0, 0, 1)
    do_draw = false
    RAGE::Draw.setBackgroundColor 0, 0, 0.2, 1
    type = 0
    pe_region_index = -1
	  loop do
      RAGE::Draw.clear
      
      
      if pe.inCollision?(400, 400, 50, 50)
        RAGE::Draw.setColor(1, 1, 0, 1)
      end

      RAGE::Draw.rectangle(400, 400, 450, 450, 2)

      # Get current engine time
      newTime = RAGE::Graphics.getTime()
      dt = newTime - oldTime # Get delta time

      # Get current mouse state
      RAGE::Input.updateMouse()

      # Set emitter position from mouse coordinates
      pe.setEmitterPosition RAGE::Input.getMouseX, RAGE::Input.getMouseY
      # If mouse is pressed down emit particles
      if RAGE::Input.mouseDown?(RAGE::Input::MOUSE_BTN1)
        pe.emit # Resets particles
        do_draw = true
      end

      # Get current keyboard state
      RAGE::Input.updateKeyboard()
      if RAGE::Input.keyDown?(RAGE::Input::KEY_A)
        if pe.spread > 2 * Math::PI
          pe.spread = 0
        else
          pe.spread += Math::PI / 2
        end
      end

      # If draw is on then draw current particle states
      if do_draw
        pe.type = type # Set emitter to current type index
        pe.update dt * 10 # * 10 means 10 times normal speed.
        pe.draw
      end

      pe.particleBurstAmount = pe.particleBurstAmount + 10 if RAGE::Input.keyDown?(RAGE::Input::KEY_UP)
      pe.particleBurstAmount = pe.particleBurstAmount - 10 if RAGE::Input.keyDown?(RAGE::Input::KEY_DOWN)

      if RAGE::Input.keyDown?(RAGE::Input::KEY_P)
        pe_region_index += 1
        case pe_region_index
        when 0
          pe.setParticleRegion 32, 0, 32, 32, true
        when 1
          pe.setParticleRegion 0, 32, 32, 32, true
        when 2
          pe.setParticleRegion 32, 32, 32, 32, true
        when 3
          pe.setParticleRegion 0, 0, 32, 32, true
          pe_region_index = -1
        end
      end

      # Change emitter type
      type = (type + 1) % 5  if RAGE::Input.mouseUp?(RAGE::Input::MOUSE_BTN2)
      
      # Do not draw emitter if mouse is not down
      if RAGE::Input.mouseUp?(RAGE::Input::MOUSE_BTN1)
        pe.emit # Resets particles
        do_draw = false
      end
      
      # Set old time and new time as the same
      oldTime = newTime

      RAGE::Draw.setColor(1, 0, 0, 1)
      RAGE::Draw.text 20, 20, "Left mouse click - emit particles."
      RAGE::Draw.text 20, 40, "Right mouse click - change type."
      RAGE::Draw.text 20, 60, "Key A - +90 degrees emitter spread."
      RAGE::Draw.text 20, 80, "Key P - change particle bitmap region."
      RAGE::Draw.text 20, 550, "Move particles next to the square to do a box region collision test."
      RAGE::Draw.text 20, 570, "Number of particles: " + pe.maxParticles.to_s

      break if RAGE::Input.keyDown?(RAGE::Input::KEY_ESCAPE) || $close

      RAGE::Graphics.update
	  end

# If exception occurs (other than exit which is normal) then show it.
rescue Exception => e  
	unless e.message == "exit"
		puts "\n\nError:\n\t\n" + e.message
		puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
		gets
	end
end