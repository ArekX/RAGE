RAGE.require "util.rb"

require 'dl'
begin

# Print about information
RAGE.about()

puts RAGE::FS.startedFS?.to_s
RAGE::FS.startFS()
puts RAGE::FS.startedFS?.to_s

RAGE::FS.stopFS()
puts RAGE::FS.startedFS?.to_s

RAGE::FS.mountPath($:[0] + "/data", "/stuff", false)
RAGE::FS.mountPath($:[0] + "/game", "/multishit", false)
RAGE::FS.removeMount($:[0] + "/game")
ar = RAGE::FS.getMounts()
puts ar.to_s

positions = [
  [ 0, 0, 0],
  [ 0, 0, 0],
  [ 0, 0, 0]
]

score_x = 0
score_o = 0

bitmap_draws = []

# Load bitmaps
title, imgX, imgO, board = RAGE::Bitmap.new, RAGE::Bitmap.new, RAGE::Bitmap.new, RAGE::Bitmap.new
winx, wino, tied = RAGE::Bitmap.new, RAGE::Bitmap.new, RAGE::Bitmap.new

title.load "data/rage.png"
imgX.load "data/x.png"
imgO.load "data/o.png"
board.load "data/board.png"

winx.load "data/xwin.png"
wino.load "data/owin.png"
tied.load "data/tied.png"

newgame = SpinButton.new 10, 10, "data/new.png"

trgt = RAGE::Graphics.getTarget()

w, h = trgt.width, trgt.height

bgm = RAGE::Music.new
bgm.load "data/bgm.ogg"
bgm.play

brdtop    = title.height + 40
brdleft   = w / 2 - board.width / 2
brdright  = brdleft + board.width
brdbottom = brdtop + board.height

RAGE::Graphics.title = "RAGE::Tic-Tac-Toe [ X Wins: #{score_x}, O Wins: #{score_o} ]"

angle = 0
itensity = 1

puts "Welcome to Tic-Tac-Toe example game"
puts "Press UP to spin XO more."
puts "Press DOWN to spin XO less."
puts "Press S to reset.\n\n"

keyEv = RAGE::KeyEvent.new

keyEv.register RAGE::Events::KEY_PRESS, Proc.new {|key|
  if key == RAGE::Input::KEY_UP
    itensity += 0.2
  elsif key == RAGE::Input::KEY_DOWN
    itensity -= 0.2 if itensity > 0
  elsif key == RAGE::Input::KEY_S
    itensity = 0
  end
}

closeEv = RAGE::ScreenEvent.new
closeEv.register RAGE::Events::SCREEN_CLOSE, Proc.new {
   Kernel::exit(0)
}

RAGE::Events.register keyEv
RAGE::Events.register closeEv

turn = (rand(100) > 50) ? "O" : "X"
turns = 0
puts "A game of Tic-Tac-Toe has begun!\n\nFirst goes #{turn}\n\n"

won = false

message_anim_x = 0

loop do
	RAGE::Graphics.clear
     
	x, y = RAGE::Input.getMouseX, RAGE::Input.getMouseY

	newgame.drawUpdate(x, y)
	
	if RAGE::Input.mouseDown?(RAGE::Input::MOUSE_BTN1)
	  if newgame.checkclick(x, y)
	     turn = (rand(100) > 50) ? "O" : "X"
		 puts "\n\nA new game of Tic-Tac-Toe has begun!\n\nFirst goes #{turn}\n\n"
		 won = false
		 for i in 0..2
		   for j in 0..2
		     positions[i][j] = 0
		   end
		 end
		 bitmap_draws.clear
		 turns = 0
		 message_anim_x = 0
		 sleep 0.2
		 bgm.stop
		 bgm.play
	  end
	end
	
	title.draw(w / 2 - title.width / 2, 20)
	board.draw(brdleft, brdtop)
	
	if RAGE::Input.mouseRepeat?(RAGE::Input::MOUSE_BTN1) && !won
		
		if ((x >= brdleft) && (x <= brdright)) || ((y >= brdleft) && (y <= brdbottom))
			
			# Get indexes
			sx, sy = ((x - brdleft).abs / 150).floor, ((y - brdtop).abs / 150).floor
			
			sx = [sx, 2].min
			sy = [sy, 2].min
			
			# Fill position if not yet filled
			if positions[sy][sx] == 0
			  puts "#{turn} takes #{sx}, #{sy}!"
			  positions[sy][sx] = turn
			  draw_image = ((turn == "X") ? imgX : imgO)
			  bitmap_draws << [ draw_image, sx * 150 + brdleft + draw_image.width / 2, sy * 150 + brdtop + draw_image.height / 2 ]
			  won = checkwinner(positions, turn)
			  turns += 1
			  
			  # Check winner
			  if won 
				puts "Winner! #{turn}!"
				score_x += 1 if turn == "X"
				score_o += 1 if turn == "O"
				RAGE::Graphics.title = "RAGE::Tic-Tac-Toe [ X Wins: #{score_x}, O Wins: #{score_o} ]"
				puts "Current Statistics:\nX - #{score_x} wins.\nO - #{score_o} wins.\n\n"
			  else
			    if turns >= 9
				  puts "Tied!"
				else
				  turn = (turn == "X") ? "O" : "X";
				end
			  end
			end
		end
	end
	
	bitmap_draws.each{|entry|
	   entry[0].draw(entry[1] + itensity * Math.cos(angle), entry[2] + itensity * Math.sin(angle))
	}
	
	angle = (angle + 1) % 180
	
	message = tied if turns >= 9
	message = winx if won && turn == "X"
	message = wino if won && turn == "O"
	
	if won || (turns >= 9)
		message.drawRegion(0, 0, message_anim_x, message.height, 0, trgt.height / 2 - message.height / 2)
		if message_anim_x < message.width
		  message_anim_x += 5
	    else
		  message_anim_x = message.width
		end
	end
	
	RAGE::Input.updateMouse
	RAGE::Graphics.update
	
	sleep 0.001
end

rescue Exception => e  
	unless e.message == "exit"
		puts "\n\nError:\n\t\n" + e.message
		puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
		gets
	end
end