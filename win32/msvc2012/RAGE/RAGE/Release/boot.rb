class Inputer
  def initialize
    begin
    @x, @y, @speed = 10, 10, 10
	pressProc = Proc.new {|key|
		if (key == 84)
		  @y -= @speed
		elsif (key == 85)
		  @y += @speed
		end
		if (key == 82)
		  @x -= @speed
		elsif (key == 83)
		  @x += @speed
		end
    }
	@tries = 1
	RAGE::Events.register(RAGE::Events::KEY_PRESS, pressProc)
	RAGE::Events.register RAGE::Events::ENGINE_CLOSE, Proc.new {
	  puts "Oh so you want to exit now?\n You tried #{@tries}/6 times."
	  
	  if @tries > 5
	    puts "Okay I will let you out. :)"
		sleep 2
		Kernel::exit(0)
	  end
	  @tries += 1
	}
	
    end
  end
  
  def getspeed
    return @speed
  end
  
  def getxy
    return @x, @y
  end
end
begin
h = Inputer.new
puts "System - " + RAGE.getEnvVar("SystemRoot")

bit = RAGE::Bitmap.new
bit.load "test.bmp"

png = RAGE::Bitmap.new
png.load "pngtest.png"



x,y = 0, 0


speed = 1
i = 0

RAGE::Graphics.setClippingRect(0, 0, 50, 50)
RAGE::Graphics.resetClippingRect()
loop do
    
	x, y = h.getxy
	speed = h.getspeed
	
    #RAGE::Graphics.clear
	RAGE::Graphics.clearBackgroundColor 150 + x, 12 - x, 40 + x
	bit.drawRegion(100 * i, 0, 100, 95, 30 + x, 30 + y)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150 + x, 30 + y, RAGE::Graphics::BITMAP_FLIP_H)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 30 + x, 150 + y, RAGE::Graphics::BITMAP_FLIP_V)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150 + x, 150 + y, RAGE::Graphics::BITMAP_FLIP_VH)

	png.draw 10, 10

	RAGE::Graphics.update # Flips buffers
	i += 1
	sleep 0.01
	i = 0 if i >= 9
end

rescue Exception => e  
	unless e.message == "exit"
		puts "\n\nBoot.rb Error:\n\t\n" + e.message
		puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
		gets
	end
end