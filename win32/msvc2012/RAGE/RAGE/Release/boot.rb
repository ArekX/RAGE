class XPChar
   def initialize(filename)
     @bit = RAGE::Bitmap.new
	 @bit.load(filename)
	 @frm = 0
	 @cw = @bit.width / 4
	 @ch = @bit.height / 4
	 @counter = 0
   end
   
   def draw(x, y, facing)
     case facing
	 when "down"
		@bit.drawRegion(@frm * @cw, 0, @cw, @ch, x, y)
	 when "left"
		@bit.drawRegion(@frm * @cw, @ch, @cw, @ch, x, y)
	 when "right"
		@bit.drawRegion(@frm * @cw, @ch * 2, @cw, @ch, x, y)
	 when "up"
		@bit.drawRegion(@frm * @cw, @ch * 3, @cw, @ch, x, y)
	 end
	 @counter += 1
	 if @counter > 50
	 @frm = (@frm + 1) % 4
	 @counter = 0
	 end
   end
end

begin

c = XPChar.new("chao.png")
facing = "down"

RAGE.about()

bit = RAGE::Bitmap.new
bit.load "test.bmp"

png = RAGE::Bitmap.new
png.load "pngtest.png"


x,y = 0, 0
speed = 5.5
i = 0

RAGE::Events.register RAGE::Events::KEY_PRESS, Proc.new {|key|
		if (key == 84)
		  y -= speed
		  facing = "up"
		elsif (key == 85)
		  y += speed
		  facing = "down"
		end
		if (key == 82)
		  x -= speed
		  facing = "left"
		elsif (key == 83)
		  x += speed
		  facing = "right"
		end
}
	
RAGE::Graphics.setBackgroundColor(14, 255, 14)

loop do
    RAGE::Graphics.clear
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 30 )
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150, 30, RAGE::Graphics::BITMAP_FLIP_H)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 30, 150, RAGE::Graphics::BITMAP_FLIP_V)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150, 150, RAGE::Graphics::BITMAP_FLIP_VH)
    c.draw(x, y, facing)
	png.draw 10, 10

	RAGE::Graphics.update # Flips buffers
	i += 1
	sleep 0.001
	i = 0 if i >= 9



end

rescue Exception => e  
	unless e.message == "exit"
		puts "\n\nBoot.rb Error:\n\t\n" + e.message
		puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
		gets
	end
end