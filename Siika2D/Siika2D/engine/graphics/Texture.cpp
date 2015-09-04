#include "Texture.h"

using namespace graphics;

Texture::Texture(int width, int height, std::vector<unsigned char>* imageData)
{
	_width = width;
	_height = height;
	_imageData = imageData;

	initialize();
}

Texture::~Texture()
{

}

void Texture::initialize()
{
	GLint err = glGetError();
	glGenTextures(1, &_texture);  
	glBindTexture(GL_TEXTURE_2D, _texture);
	s2d_assert(glGetError() == 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _imageData->data());

}

GLuint Texture::getTexture()
{
	return _texture;
}