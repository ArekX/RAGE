begin
puts "Boot.rb script test"
puts "\$:: #{$:.to_s}"

puts "\$0: #{$0.to_s}"
puts "\$RARGV: #{$RARGV.to_s}"

puts "= Boot script ="
sleep 0.5
puts "- Title changing test - "
sleep 0.5
RAGE::Graphics::setTitle("Title changed from Boot.rb")
sleep 0.5
puts "- Windows position test -"
sleep 0.5
RAGE::Graphics::setWindowPosition(50, 50)
puts "- Fullscreen test -"
sleep 2
RAGE::Graphics::setFullscreen(true)
sleep 0.5
RAGE::Graphics::setFullscreen(false)

puts "- Draw text test -"
sleep 0.5
drawText("Text draw call from Boot.rb")


puts "- Cursor Show/Hide test -"
sleep 0.5
RAGE::Graphics::cursorVisible(false)
puts "Cursor Hidden"
sleep 5
RAGE::Graphics::cursorVisible(true)
puts "Cursor Visible"
sleep 4
puts "- Exception Test -"
sleep 1
error_nil_function()

rescue Exception => e  
  puts "\n\nBoot.rb Error:\n\t\n" + e.message
  puts "Backtrace:\n\t #{e.backtrace[0].to_s}\n\n"
end

puts "= Testing complete ="
sleep 5


