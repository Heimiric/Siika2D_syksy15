varying lowp vec4 varyCol;
varying lowp vec2 UV;
uniform sampler2D sampler;
void main()
{
	gl_FragColor = texture2D(sampler, UV) + varyCol;
}