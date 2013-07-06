begin
config = {
  "name" => "Game Name",
  "version"            => "0.0.2-beta",
  "width"             => 800,
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
  "RAGE::Shader"       => true,
  "RAGE::Font"         => true,
  "RAGE::Color"        => true,
  "RAGE::Events"       => true,
  "RAGE::FS"           => true,
  "RAGE::Draw"         => true,
  "RAGE::Input"        => true
}


RAGE.configure(config)
end