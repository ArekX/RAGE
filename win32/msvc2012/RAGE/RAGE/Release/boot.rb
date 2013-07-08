begin

va = RAGE::VertexArray.new
color = RAGE::Color.new
color.setRGBA(1, 1, 1, 1)

bmp = RAGE::Bitmap.new
bmp.load("data/mysha.pcx")

sX = RAGE::Graphics.screenWidth / 3
eX = RAGE::Graphics.screenWidth - RAGE::Graphics.screenWidth / 3

va.push(sX, 0, 2, sX, 0, color)
va.push(eX, 0, 2, eX, 0, color)
va.push(0, RAGE::Graphics.screenHeight, 0, 0, RAGE::Graphics.screenHeight, color)
va.push(RAGE::Graphics.screenWidth, RAGE::Graphics.screenHeight, 0, RAGE::Graphics.screenWidth, RAGE::Graphics.screenHeight, color)

va2 = RAGE::VertexArray.new

va2.push(eX, 0, 0, eX, 0, color)
va2.push(eX, RAGE::Graphics.screenHeight / 2, 0, eX, RAGE::Graphics.screenHeight / 2, color)
va2.push(RAGE::Graphics.screenWidth, RAGE::Graphics.screenHeight, 0, RAGE::Graphics.screenWidth, RAGE::Graphics.screenHeight, color)
va2.push(RAGE::Graphics.screenWidth, 0, 0, RAGE::Graphics.screenWidth, 0, color)


va3 = RAGE::VertexArray.new

va3.push(0, 0, 0, 0, 0, color)
va3.push(0, RAGE::Graphics.screenHeight, 0, 0, RAGE::Graphics.screenHeight, color)
va3.push(sX, 0, 0, sX, 0, color)
va3.push(sX, RAGE::Graphics.screenHeight / 2, 0, sX, RAGE::Graphics.screenHeight / 2, color)

angle = 0;

glsl = RAGE::Shader.new(RAGE::Graphics::FRAGMENT_SHADER, "
 uniform sampler2D tex;
 uniform float r;
 uniform float g;
 uniform float b;
 varying vec4 varying_color;
 varying vec2 tc;
 void main()
 {

   vec4 tmp = texture2D(tex, tc);

   tmp.r = r;
   tmp.g = 1.0 - r;
   tmp.b *= 1.2;
   if ((int(tc.y) % 3 == 0) && (int(tc.x) % 3 == 0))
    tmp.b = 0;
   gl_FragColor = tmp;
 }
")

 r = 0
loop do
  RAGE::Graphics.clear

  RAGE::Graphics.setShader(glsl)

  
  glsl.setFloat("r", r)
  glsl.setFloat("g", 1)
  glsl.setFloat("b", 1)

  r = (r + 0.02) % 1

  RAGE::Draw.prim(va, bmp, 0, va.size, RAGE::Draw::PRIM_TRIANGLE_FAN)
  RAGE::Draw.prim(va2, bmp, 0, va2.size, RAGE::Draw::PRIM_TRIANGLE_FAN)
  RAGE::Draw.indexedPrim(va3, bmp, [0, 1, 2, 3], 4, RAGE::Draw::PRIM_TRIANGLE_FAN)
  
  angle = (angle + 8) % 360

  #va.setX(0, sX + 25 * Math.cos(angle * Math::PI / 180))
  #va.setX(1, eX + 25 * Math.cos(angle * Math::PI / 180))
  RAGE::Input.updateKeyboard()
  break if RAGE::Input.keyDown?(RAGE::Input::KEY_ESCAPE)

  RAGE::Graphics.setShader(nil)

  RAGE::Graphics.update
end

rescue Exception => e
   puts e.message
   gets
end