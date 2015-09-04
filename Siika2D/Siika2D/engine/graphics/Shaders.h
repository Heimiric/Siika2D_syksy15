#pragma once
/*
	File for all default shaders used in siika
*/

//"uniform mat4 windowProjection;\n"
//"uniform mat4 worldProjection;\n"
//"uniform mat4 viewProjection;\n"
// "   gl_Position = windowProjection * viewProjection * worldProjection * vec4(position, 0, 1);\n"
namespace graphics
{

	const GLchar* defVertexWithColor =
		"attribute vec2 position;\n"
		"attribute vec4 color;\n"
		"varying vec4 varyCol;\n"
		"void main() {\n"
		"	varyCol = color; \n"
		"   gl_Position = vec4(position, 0, 1);\n"
		"}\n";
	const GLchar* defFragmentWithColor =
		"varying lowp vec4 varyCol;\n"
		"void main()\n"
		"{\n"
		"   gl_FragColor = varyCol;\n"
		"}\n";

	const GLchar* defVertexWithTexture =
		"attribute vec2 position;\n"
		"attribute vec2 texture;\n"
		"varying vec2 UV;\n"
		//"uniform sampler2D sampler;\n"
		"void main() {\n"
		"	UV = texture;\n"
		"   gl_Position = vec4(position, 0, 1);\n"
		"}\n";
	const GLchar* defFragmentWithTexture =
		"varying lowp vec2 UV;\n"
		"uniform sampler2D sampler;\n"
		"void main()\n"
		"{\n"
		"   gl_FragColor = texture2D(sampler,UV);\n"
		"}\n";

	const GLchar* defVertexWithBoth =
		"attribute vec2 position;\n"
		"attribute vec2 texture;\n"
		"uniform mat4 world;\n"
		"uniform mat4 window;\n"
		"uniform mat4 view;\n"
		"varying vec2 UV;\n"
		"attribute vec4 color;\n"
		"varying vec4 varyCol;\n"
		"void main() {\n"
		"	UV = texture;\n"
		"	varyCol = color; \n"
		"   gl_Position =  window * vec4(position, 0, 1);\n"
		"}\n";
	const GLchar* defFragmentWithBoth =
		"varying lowp vec4 varyCol;\n"
		"varying lowp vec2 UV;\n"
		"uniform sampler2D sampler;\n"
		"void main()\n"
		"{\n"
		"   gl_FragColor = texture2D(sampler, UV) + varyCol;\n"
		"}\n";
	
}