#include "Shader.h"
#include "Shaders.h"
using namespace graphics;

Shader::Shader(bool color, bool texture):
_color(color), _texture(texture)
{
	_default = true;
	init();
	
	if(color && texture)
	{
		_fragSource = defFragmentWithBoth;
		_vertSource = defVertexWithBoth;
	}
	else
	{
		if(texture)
		{
			_fragSource = defFragmentWithTexture;
			_vertSource = defVertexWithTexture;
		}
		else  //Will always have atleast the default color shaders
		{
			_fragSource = defFragmentWithColor;
			_vertSource = defVertexWithColor;
		}

	}
	
	_valid = compileShaders();
	if(_valid)
		_valid = linkProgram();
	//valid = true if neither complie or link returned false
}

Shader::Shader(const GLchar * fragmentSource, const GLchar * vertexSource, bool color, bool texture) :
_fragSource(fragmentSource), _vertSource(vertexSource), _color(color), _texture(texture)
{
	_default = false;
	init();
	_valid = compileShaders();
	if(_valid)
		_valid = linkProgram();
	//valid = true if neither compile or link returned false
}

Shader::~Shader()
{
	
}

std::string Shader::getShaderInfoLog(GLuint handle)
{
	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	GLchar * infoLog = new GLchar[length + 1];
	glGetShaderInfoLog(handle, length + 1, &length, infoLog);
	std::string log;
	log.append(infoLog);
	delete infoLog;
	return log;
}
std::string Shader::getProgramInfoLog(GLuint handle)
{
	GLint length;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
	GLchar * infoLog = new GLchar[length + 1];
	glGetProgramInfoLog(handle, length + 1, &length, infoLog);
	std::string log;
	log.copy(infoLog, length);
	delete infoLog;
	return log;
}
bool Shader::compileShaders()
{
	GLint status;
	_program = glCreateProgram();
	_vertHandle = glCreateShader(GL_VERTEX_SHADER);
	_fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_vertHandle, 1, &_vertSource, NULL);
	glShaderSource(_fragHandle, 1, &_fragSource, NULL);
	glCompileShader(_vertHandle);
	glCompileShader(_fragHandle);

	glGetShaderiv(_vertHandle, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		std::string infoLog = getShaderInfoLog(_vertHandle);
		//s2d_error("Vertex shader complile failed \n" << getShaderInfoLog(_vertHandle));
		s2d_assert(status != GL_FALSE);
		return false;
	}

	glGetShaderiv(_fragHandle, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		std::string infoLog = getShaderInfoLog(_fragHandle);
		s2d_error("Fragment shader compile failed \n");
		s2d_assert(status != GL_FALSE);
		return false;
	}

	glAttachShader(_program, _vertHandle);
	glAttachShader(_program, _fragHandle);
	return true;
}
bool Shader::linkProgram()
{
	GLint status;
	glBindAttribLocation(_program, SHADER_ATTRIBUTE::position, _posString);
	if(_color)
		glBindAttribLocation(_program, SHADER_ATTRIBUTE::color, _colString);
	if(_texture)
		glBindAttribLocation(_program, SHADER_ATTRIBUTE::texture, _texString);



	glLinkProgram(_program);
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		//s2d_error("Linking program failed \n" << getProgramInfoLog(_program));
		s2d_assert(status);
		return false;
	}

	GLint error = glGetError();

	_windowLocation = glGetUniformLocation(_program, _windowString);

	assert(error == 0);

	return true;
}

void Shader::use(bool toUse)
{
	GLint err = glGetError();
	//s2d_assert(err == 0);

	if(toUse)
	{
		glUseProgram(_program);
		if(_texture)
			useSampler();
	}
	else
	{
		glUseProgram(0u);
	}
	// Moved to linkProgram()
	glEnableVertexAttribArray(SHADER_ATTRIBUTE::position);
	if(_color)
		glEnableVertexAttribArray(SHADER_ATTRIBUTE::color);
	if(_texture)
		glEnableVertexAttribArray(SHADER_ATTRIBUTE::texture);

	err = glGetError();
	s2d_assert(err == 0);

	return;
}

void Shader::init()
{
	_program = -1;
	_fragHandle = -1;
	_vertHandle = -1;
	_samplerHandle = -1;
}
void Shader::useSampler()
{
	_samplerHandle = glGetUniformLocation(_program, "sampler");
	glUniform1i(_samplerHandle, 0u);
}