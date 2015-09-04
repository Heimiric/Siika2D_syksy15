varying lowp vec2 texcoord;
uniform sampler2D tex;
uniform lowp vec4 color;
 
void main(void) 
{
  gl_FragColor = lowp vec4(1, 1, 1, texture2D(tex, texcoord).a) * color;
}