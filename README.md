RAGE
====

Ruby Awesome Game Engine, a 2D game engine with Ruby language support.

Using Ruby Version: 2.0.0-p195

Using Allegro Version: 5.0.8

Downloads
====

Current WIP: 

https://www.dropbox.com/s/ogmbngyo6yvh3op/RAGE20052013-2.7z




Other WIPs:

20.5.2013:
https://www.dropbox.com/s/5vittsw96apoptr/RAGE20052013.7z

17.5.2013:
https://www.dropbox.com/s/em9by8qnhdjf3gn/RAGE17052013.7z

12.5.2013:
https://www.dropbox.com/s/cyf2ffn9pk10hyg/RAGE12052013.zip

API
====

This API is still a work in progress, some (or all) of the names might change in first stable or beta version. 
Some things might be added, while other things might be removed.

* Main

```ruby
# RAGE.getEnvVar(envVar)
# Returns string which represents Enviroment Variable.
# Example:
RAGE.getEnvVar("windir") # returns full path to windows folder.

RAGE.about()
# Prints out version information.
```

* Graphics

```ruby
# RAGE::Graphics.setTitle(newTitle)
# Sets windows title to a new name.
# Example:
RAGE::Graphics.setTitle("My Game") # sets window title to My Game

# RAGE::Graphics.setVsync(bool)
# Turns Vertical Synchronization ON or OFF (true/false).
# Example:
RAGE::Graphics.setVsync(true) # Turns ON Vsync

# RAGE::Graphics.setFullscreen(bool)
# Turns Fullscreen ON or OFF (true/false).
# Example:
RAGE::Graphics.setFullscreen(true) # Turns ON Fullscreen

# RAGE::Graphics.setWindowPosition(x, y)
# Sets window position to specified coordinates.
# Example:
RAGE::Graphics.setWindowPosition(0, 0) # Moves window to top left corner of the screen

# RAGE::Graphics.cursorVisible(bool)
# Shows or hides cursor in window (true/false).
# Example:
RAGE::Graphics.cursorVisible(false) # Hides cursor while it's in window.

RAGE::Graphics.update()
# Updates current drawing changes (flips buffers).

RAGE::Graphics.clear()
# Clear current screen contents.

# RAGE::Graphics.setBackgroundColor(r, g, b)
# Sets new clear background color.
# Example:
RAGE::Graphics.setBackgroundColor(255, 255, 255)
RAGE::Graphics.clear() # Clears to white color

# RAGE::Graphics.setTarget(bitmap)
# Sets the target of all subsequent drawing operation to a RAGE::Bitmap class specified in argument.
# If nil is passed as an argument, target is reset to main screen.
# Example:
dst = RAGE::Bitmap.new
dst.create(300, 400)
RAGE::Graphics.setTarget(dst)

# RAGE::Graphics.getTarget()
# Returns new RAGE::Bitmap object current set target for drawing.
# Example:
scrBit = RAGE::Graphics.getTarget()
puts "Screen Width is: #{scrBit.width} px\n Screen Height is: #{scrBit.height} px"


# RAGE::Graphics.setClippingRect(x, y, width, height)
# Set the region of the target bitmap or screen that pixels get clipped to. 
# The default is to clip pixels to the entire screen.
# Example:
RAGE::Graphics.setClippingRect(0, 0, 50, 50)
RAGE::Graphics.clear # It will only clear a rectangle specified by RAGE::Graphics.setClippingRect

# RAGE::Graphics.resetClippingRect()
# Resets the region of the target bitmap or screen that pixels get clipped to. 
# The default is to clip pixels to the entire screen.
# Example:
RAGE::Graphics.setClippingRect(0, 0, 50, 50)
RAGE::Graphics.clear # It will only clear a rectangle specified by RAGE::Graphics.setClippingRect
RAGE::Graphics.resetClippingRect() 
RAGE::Graphics.clear # Whole screen will be cleared
```

* Events

```ruby
# Constants:
# RAGE::Events::KEY_UP
# Key Up Event.

# RAGE::Events::KEY_DOWN
# Key Down Event.

# RAGE::Events::KEY_PRESS
# Key Press Event.

# RAGE::Events::ENGINE_CLOSE
# Program exit button pressed event.

# RAGE::Events.register(eventType, Proc)
# Registers new procedure which will be called when event happens.
# Example:
RAGE::Events.register(RAGE::Events::KEY_PRESS, Proc.new({|key|
  puts "You pressed keycode #{key.to_s}" # Shows which key was pressed.
}))

# RAGE::Events.unregister(eventType, Proc)
# Un-registers new procedure which will be called when event happens.
# Example:
eventProc = Proc.new({|key|
  puts "You pressed keycode #{key.to_s}" # Shows which key was pressed.
}
RAGE::Events.register(RAGE::Events::KEY_PRESS, eventProc))
RAGE::Events.unregister(RAGE::Events::KEY_PRESS, eventProc)) # Unregisters registered eventProc

# RAGE::Events.clear(eventType)
# Un-registers all events for specified event type.
# Example:
RAGE::Events.clear(RAGE::Events::KEY_PRESS) # Unregisters all Key Press events.

RAGE::Events.freeze()
# Stops all events processing.

RAGE::Events.unfreeze()
# Resumes event processing.

# RAGE::Events.useKeyCodeNames(bool)
# Specifies whether to use key code names or just key code integers.
# Example:
RAGE::Events.register(RAGE::Events::KEY_PRESS, Proc.new({|key|
  puts "You pressed keycode #{key.to_s}" # Shows which key was pressed as a number.
}))
RAGE::Events.useKeyCodeNames(true) # After this it will show a name (like "LEFT") instead of a number of the key which was pressed.
```

* Input

```ruby
# Constants:
# RAGE::Input::MOUSE_BTN1
# Represents Left mouse click.

# RAGE::Input::MOUSE_BTN2
# Represents Right mouse click.

# RAGE::Input::MOUSE_BTN3
# Represents Middle mouse click.

# RAGE::Input::KEY_UP
# Represents Up key

# RAGE::Input::KEY_DOWN
# Represents Down key

# RAGE::Input::KEY_LEFT
# Represents Left key

# RAGE::Input::KEY_RIGHT
# Represents Right key

# RAGE::Input.updateKeyboard()
# Updates current keyboard state.

# RAGE::Input.isKeyDown?(keycode)
# Checks if keycode is pressed. Use this for repeating functions.
# Example:
RAGE::Input.updateKeyboard()
puts "Is left pressed? " + RAGE::Input.isDown?(RAGE::Input::KEY_LEFT)

# RAGE::Input.updateMouse()
# Updates current mouse state.

# RAGE::Input.isMouseDown?(button)
# Checks if mouse button is pressed.
# Example:
RAGE::Input.updateMouse()
puts "Left click? " + RAGE::Input.isMouseDown?(RAGE::Input::MOUSE_BTN1) # Returns true if clicked.

# Joystick functions coming soon.
```

** Classes

* Bitmap

```ruby
# Constants:
# RAGE::Graphics::BITMAP_FLIP_H
# Flip bitmap horizontally.
# Works with RAGE::Bitmap.drawOpt, RAGE::Bitmap.drawRegionOpt.

# RAGE::Graphics::BITMAP_FLIP_V
# Flip bitmap vertically.
# Works with RAGE::Bitmap.drawOpt, RAGE::Bitmap.drawRegionOpt.

# RAGE::Graphics::BITMAP_FLIP_VH
# Flip bitmap horizontally and vertically.
# Works with RAGE::Bitmap.drawOpt, RAGE::Bitmap.drawRegionOpt.

# RAGE::Bitmap.new
# Creates new instance of Bitmap Class
# Example:
bit = RAGE::Bitmap.new

# RAGE::Bitmap.load(filename)
# Loads image file from disk. Supported formats are: BMP, PCX, TGA, PNG, JPG
# Example:
bit = RAGE::Bitmap.new
bit.load("rage.png") # Loads rage.png file.

# RAGE::Bitmap.save(filename)
# Saves contents of a bitmap to filename. Image format will be determined from extension.
# Supported formats are: BMP, PCX, TGA, PNG, JPG
# Example:
bit = RAGE::Graphics.getTarget()
bit.save("c:/screenshot.bmp") # Saves a screenshot to a BMP file.

# RAGE::Bitmap.create(width, height)
# Creates an empty bitmap.
# Example:
bit = RAGE::Bitmap.new
bit.create(200, 300) # Creates new empty 200, 300 bitmap.

# RAGE::Bitmap.width()
# Returns bitmap width.
# Example:
bit = RAGE::Bitmap.new
bit.create(200, 300)
puts bit.width # Prints 200

# RAGE::Bitmap.height()
# Returns bitmap height.
# Example:
bit = RAGE::Bitmap.new
bit.create(200, 300)
puts bit.height # Prints 300

# RAGE::Bitmap.clone()
# Returns a copy of current bitmap object.
# Example:
bit = RAGE::Bitmap.new
bit.load("rage.png")
bit2 = bit.clone() # bit2 contains a new clone of bit.

# RAGE::Bitmap.dispose()
# Frees resources held by bitmap.
# Example:
bit = RAGE::Bitmap.new
bit.load("rage.png")
bit.dispose() # Frees all resources held by bit

# RAGE::Bitmap.draw(x, y)
# Draws bitmap on the screen on specified x, y coordinates.
# Example:
bit = RAGE::Bitmap.new
bit.load("rage.png")
bit.draw(10, 10) # Draws rage.png on 10, 10 coordinates on screen.

# RAGE::Bitmap.drawOpt(x, y, flip)
# Draws bitmap on the screen on specified x, y coordinates with flipping. Refer to constants for more info.
# Example:
bit = RAGE::Bitmap.new
bit.load("rage.png")
bit.draw(10, 10, RAGE::Graphics::BITMAP_FLIP_V) # Draws rage.png on 10, 10 coordinates on screen. flipped vertically.

# RAGE::Bitmap.drawRegion(sx, sy, sw, sh, dx, dy)
# Draws a part of the bitmap specified by sx, sy, sw, sh (sx, sy coordinate and sw - width, sh - height) on destination dx, dy coordinates.
# Example:
bit = RAGE::Bitmap.new
bit.load("rage.png")
bit.drawRegion(0, 0, 10, 50, 10, 10) # Draws part of rage.png on 10, 10 coordinates on screen.

# RAGE::Bitmap.drawRegion(sx, sy, sw, sh, dx, dy, flip)
# Draws a part of the bitmap specified by sx, sy, sw, sh (sx, sy coordinate and sw - width, sh - height) on destination dx, dy coordinates, with flipping.
# Example:
bit = RAGE::Bitmap.new
bit.load("rage.png")
bit.drawRegion(0, 0, 10, 50, 10, 10, RAGE::Graphics::BITMAP_FLIP_V) # Draws part of rage.png on 10, 10 coordinates on screen, flipped vertically.

```

* Audio

```ruby
# Constants:
# RAGE::Sound::STREAM
# Specifies that the sound loaded will be loaded as a stream.
# Streams are loaded and decompressed on the fly when they are needed. Use this for big files.

# RAGE::Sound::SFX
# Specifies that the sound loaded will be loaded as a sample.
# Samples are fully loaded and decompressed in memory before they are played which can be time consuming so
# avoid using this for big sound files.

# RAGE::Audio.new
# Creates new instance of Audio class.
# Example:
audio = RAGE::Audio.new

# RAGE::Audio.load(filename, type)
# Loads file from disk and prepares it for playing depending on type.
# Types are: RAGE::Sound::STREAM, RAGE::Sound::SFX
# Supported formats: OGG, WAV, FLAC, IT, MOD, S3M, XM
# Example:
bgm = RAGE::Audio.new
bgm.load("bgm.ogg", RAGE::Sound::STREAM) # Loads bgm.ogg audio stream from disk.

# RAGE::Audio.play()
# Plays loaded audio.
# Example:
bgm = RAGE::Audio.new
bgm.load("bgm.ogg", RAGE::Sound::STREAM)
bgm.play() # Plays audio

# RAGE::Audio.stop()
# Stops current playing audio.
# Example:
bgm = RAGE::Audio.new
bgm.load("bgm.ogg", RAGE::Sound::STREAM)
bgm.play()
bgm.stop() # Stops audio play

# RAGE::Audio.dispose()
# Frees resources used by audio.
# Example:
bgm = RAGE::Audio.new
bgm.load("bgm.ogg", RAGE::Sound::STREAM)
bgm.play()
bgm.stop() 
bgm.dispose() # Disposes allocated audio resources

```

License
====

This is a current WIP License and is a subject to change.

Copyright (c) 2013 Aleksandar Panic

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.

Ruby License: http://www.ruby-lang.org/en/about/license.txt

Allegro License: http://alleg.sourceforge.net/license.html
