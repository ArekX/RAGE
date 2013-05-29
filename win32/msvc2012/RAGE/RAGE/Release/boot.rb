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
   end
   
   def update
	 @counter += 1
	 if @counter > 25
		@frm = (@frm + 1) % 4
		@counter = 0
	 end
   end
   
   def reset
     @couter = 0
	 @frm = 0
   end
end

begin

c = XPChar.new("chao.png")
facing = "down"

bit = RAGE::Bitmap.new
bit.load "test.bmp"

png = RAGE::Bitmap.new
png.load "pngtest.png"

x,y = 0, 0
speed = 1
i = 0

if $DEBUGS
  puts "DEBUG VERSION!!!"
end

aud = RAGE::Sfx.new
aud.load "bgm.ogg"
aud.play

	
RAGE::Graphics.setBackgroundColor(120, 120, 14)

ev = RAGE::KeyEvent.new
me = RAGE::MouseEvent.new

#  unsigned int buttons, int x, int y, int wheel)
me.register 8, Proc.new{|buttons, x, y, wheel|
   puts "X: #{x}, Y: #{y}"
}

ev.register 1, Proc.new{|key|
  puts "Key: #{key}"
}

screen = RAGE::ScreenEvent.new
screen.register RAGE::Events::SCREEN_CLOSE, Proc.new{
  Kernel::exit(0)
}

RAGE::Events.register(screen)

loop do
        RAGE::Graphics.clear
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 30 )
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150, 30, RAGE::Graphics::BITMAP_FLIP_H)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 30, 150, RAGE::Graphics::BITMAP_FLIP_V)
	bit.drawRegionOpt(100 * i, 0, 100, 95, 150, 150, RAGE::Graphics::BITMAP_FLIP_VH)
        c.draw(x, y, facing)
	png.draw 10 , 10
	RAGE::Input.updateKeyboard
	RAGE::Input.updateMouse
	
	
	if (RAGE::Input.isKeyDown?(84))
		  y -= speed
		  facing = "up"
		  c.update
		elsif (RAGE::Input.isKeyDown?(85))
		  y += speed
		  facing = "down"
		  c.update
		end
		if (RAGE::Input.isKeyDown?(82))
		  x -= speed
		  facing = "left"
		  c.update
		elsif (RAGE::Input.isKeyDown?(83))
		  x += speed
		  facing = "right"
		  c.update
		end
	
	
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