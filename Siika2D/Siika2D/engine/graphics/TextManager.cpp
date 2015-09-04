#include "TextManager.h"

using namespace graphics;


TextManager::TextManager(core::ResourceManager* resourceManager, ShaderManager* shaderManager, glm::vec2 displaySize)
{
	_resourceManager = resourceManager;
	_shaderManager = shaderManager;
	_displaySize = displaySize;

	_textShader = createShaders();
	_program = _textShader->getProgram();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initFreetype();
}


TextManager::~TextManager()
{

}


Text* TextManager::createText()
{
	_texts.push_back(new Text(_resourceManager, &_library));
	return _texts.at(_texts.size()-1);
}


void TextManager::drawTexts()
{
	Shader* previousShader =_shaderManager->getShader();
	_shaderManager->setCurrentShader(_textShader);
	glUseProgram(_program);

	GLint error = glGetError();
	s2d_assert(error == 0);

	GLint textureSampler;
	GLuint texture;
	GLint positionLoc, colorLoc;

	setAttributes(positionLoc);
	setTextureUniform(textureSampler, texture);
	setColorUniform(colorLoc);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 0; i < _texts.size(); i++)
	{
		if (_texts.at(i)->isInitialized)
		{
			_texts.at(i)->draw(_displaySize, positionLoc, colorLoc);
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	_shaderManager->setCurrentShader(previousShader);
}

Shader* TextManager::createShaders()
{
	Shader* previousShader = _shaderManager->getShader();
	Shader* textShader = _shaderManager->createShader("vertexTextShader.glsl", "fragmentTextShader.glsl");
	_shaderManager->setCurrentShader(previousShader);

	GLint error = glGetError();
	s2d_assert(error == 0);

	return textShader;
}

void TextManager::setAttributes(GLint& positionLoc)
{
	positionLoc = glGetAttribLocation(_program, "coord");
	s2d_assert(!(positionLoc == -1));

	glEnableVertexAttribArray(positionLoc);

	GLint error = glGetError();
	s2d_assert(error == 0);
}

void TextManager::setColorUniform(GLint &colLoc)
{
	colLoc = glGetUniformLocation(_program, "color");

	GLint error = glGetError();
	s2d_assert(error == 0);
}

void TextManager::setTextureUniform(GLint& textureSampler, GLuint& texture )
{
	textureSampler = glGetUniformLocation(_program, "tex");

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	GLint error = glGetError();
	s2d_assert(error == 0);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	error = glGetError();
	s2d_assert(error == 0);

	glUniform1i(textureSampler, 0);
	error = glGetError();
	s2d_assert(error == 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	error = glGetError();
	s2d_assert(error == 0);
}


void TextManager::initFreetype()
{
	int error = FT_Init_FreeType(&_library);
	s2d_assert(error == 0);
}

