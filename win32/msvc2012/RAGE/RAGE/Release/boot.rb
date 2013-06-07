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


RAGE::Draw.setFont "acmesa.ttf", 48

x,y = 0, 0
speed = 1
i = 0

RAGE.about



if $DEBUGS
  puts "DEBUG VERSION!!!"
end
	
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

keyb = RAGE::KeyEvent.new
keyb.register RAGE::Events::KEY_UP, Proc.new {|key|
  Kernel::exit(0) if key == RAGE::Input::KEY_ESC
}

RAGE::Events.register(screen)
RAGE::Events.register(keyb)
RAGE::Graphics.title = "Miskoooo!"

bit.scaleX = 2
bit.scaleY = 2
bit.flip = RAGE::Graphics::FLIP_VH

dAngle = 1 * Math::PI / 180
RAGE::Graphics.setCursorVisible false

RAGE::Draw.setColorF 1.0, 1.0, 1.0, 1.0
oldtime = RAGE::Graphics.getTime
loop do

	
        RAGE::Graphics.clear
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 30 )
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 80 )
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 130 )
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 180 )
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 230 )
	bit.drawRegion(100 * i, 0, 100, 95, 30 , 280 )
	bit.drawRegion(100 * i, 0, 100, 95, 150 , 280 )
        c.draw(x, y, facing)
	RAGE::Draw.text 50, 50, "Misko misko test!"
	png.draw 120 , 110
	RAGE::Draw.line(10, 10, 100, 100, 5)
	RAGE::Draw.ellipse(50, 50, RAGE::Input.getMouseX, RAGE::Input.getMouseY, 4)
	RAGE::Input.updateKeyboard
	RAGE::Input.updateMouse
	
	puts "Key up check works!" if RAGE::Input.keyUp?(RAGE::Input::KEY_A)
	

	puts "Mouse Repeat works" if RAGE::Input.mouseRepeat?(RAGE::Input::MOUSE_BTN1)
	puts "Mouse Down works" if RAGE::Input.mouseDown?(RAGE::Input::MOUSE_BTN1)
	puts "Mouse Up works" if RAGE::Input.mouseUp?(RAGE::Input::MOUSE_BTN1)

	
	if (RAGE::Input.keyRepeat?(84))
		  y -= speed
		  facing = "up"
		  c.update
		elsif (RAGE::Input.keyRepeat?(85))
		  y += speed
		  facing = "down"
		  c.update
		end
		if (RAGE::Input.keyRepeat?(82))
		  x -= speed
		  facing = "left"
		  c.update
		elsif (RAGE::Input.keyRepeat?(83))
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