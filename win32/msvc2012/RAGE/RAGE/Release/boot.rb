begin


puts "System - " + getEnvVar("SystemRoot")
puts Encoding.list

bit = RAGE::Bitmap.new
bit.load "test.bmp"

png = RAGE::Bitmap.new
png.load "pngtest.png"



x,y = 0, 0
speed = 10
i = 0
loop do
    #RAGE::Graphics.clear
	RAGE::Graphics.clearBackgroundColor 150 + x, 12 - x, 40 + x
	bit.drawRegion(100 * i, 0, 100, 95, 30 + x, 30 + y)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150, 30, RAGE::BITMAP_FLIP_H)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 30, 150, RAGE::BITMAP_FLIP_V)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150, 150, RAGE::BITMAP_FLIP_VH)
	png.draw 10, 10
	RAGE::Events.update
	case RAGE::Events.getKeyCode
	when 84 # Up
	  y -= speed
	when 85 # Down
	  y += speed
	when 82 # Left
	  x -= speed
	when 83 # Right
	  x += speed
	end
	RAGE::Graphics.update # Flips buffers
	
	sleep 0.05 # Make animation a bit smoother
	i += 1
	i = 0 if i >= 9
end

rescue Exception => e  
	unless e.message == "exit"
		puts "\n\nBoot.rb Error:\n\t\n" + e.message
		puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
		gets
	end
end



