attribute vec4 coord;
varying vec2 texcoord;
uniform mat4 window;
void main(void) 
{
//window *
  gl_Position = vec4(coord.xy, 0, 1);
  texcoord = coord.zw;
}