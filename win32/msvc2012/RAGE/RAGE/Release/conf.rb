begin
config = {
  "name"               => "RAGE 0.0.3 - Fragment Shader Example",
  "version"            => "0.0.3-beta",
  "width"              => 800,
  "height"             => 600,
  "fullscreen"         => false,
  "maximizedWindow"    => false,
  "vsync"              => false,
  "RAGE::Bitmap"       => true,
  "RAGE::Music"        => true,
  "RAGE::Sfx"          => true,
  "RAGE::IniFile"      => true,  
  "RAGE::ScreenEvent"  => true,
  "RAGE::KeyEvent"     => true,
  "RAGE::MouseEvent"   => true,
  "RAGE::TimerEvent"   => true,
  "RAGE::Joystick"     => true,
  "RAGE::JoyEvent"     => true,
  "RAGE::VertexArray"  => true,
  "RAGE::Shader"       => true,
  "RAGE::Font"         => true,
  "RAGE::Color"        => true,
  "RAGE::Events"       => true,
  "RAGE::FS"           => true,
  "RAGE::Draw"         => true,
  "RAGE::Input"        => true,
  "DL"                 => true,
  "Zlib"               => true
}


RAGE.configure(config)
end