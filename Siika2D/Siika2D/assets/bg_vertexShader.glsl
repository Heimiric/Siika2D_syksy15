attribute vec2 position;
attribute vec2 texture;
varying vec2 UV;
attribute vec4 color;
varying vec4 varyCol;
void main()
{
	UV = texture;
	varyCol = color;
	gl_Position =  vec4(position, 0, 1);
}