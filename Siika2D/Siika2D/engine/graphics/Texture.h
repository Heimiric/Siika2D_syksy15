#pragma once

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vector>
#include <glm.hpp>

#include"../core/ErrorHandler.h"

namespace graphics
{
	/**
		Class for drawing images with OpenGL.
		*/
	class Texture
	{
	public:
		/**
			Constructor.
			Set texture size and image data
			Calls initialize.
			*/
		Texture(int width, int height, std::vector<unsigned char>* imageData);
		~Texture();

		/**
			Get the OpenGL texture unit.
			*/
		GLuint getTexture();

		/**
			Returns the size of the texture.
		*/
		glm::vec2 getSize()
		{
			return glm::vec2(_width, _height);
		}

	private:
		int _width, _height;
		GLuint _texture;
		std::vector<unsigned char>* _imageData;

		/**
			Generates OpenGL texture names.
			Specifies OpenGL texture image and sets texture parameters.
			*/
		void initialize();
	};
}