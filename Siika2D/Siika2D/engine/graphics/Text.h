#pragma once

#include "../core/ResourceManager.h"
#include "../misc/Color.h"
#include "Buffer.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace graphics
{
	/**
		Class for drawable text.
		Uses FreeType to load .ttf fonts.
	*/
	class Text
	{

		friend class TextManager;

	public:
		/**
		Constructor.
		Initializes FreeType and sets default values for position and font size.
		*/
		Text(core::ResourceManager* resourceManager, FT_Library* ftLibrary);
		~Text();
		/**
			Load font from file
		*/
		void setFont(std::string filename);

		/**
			Set font size in pixels
		*/
		void setFontSize(GLint size);

		/**
			Set the string of characters to display
		*/
		void setText(std::string text);

		/**
			Set text position. Origin: bottom-left
		*/
		void setPosition(GLfloat x, GLfloat y);

		/**
			Set text color.
		*/
		void setColor(Color color);

		/**
			Get text color.
		*/
		Color getColor();
	protected:
		/**
			Draws text. Generates textures for each character of the text and draws them.
		*/
		void draw(glm::vec2 displaySize, GLint posLoc, GLint colLoc);
		bool isInitialized; //Gives OK to textManager for drawing if true.

	private:

		core::ResourceManager* _resourceManager;
		Buffer _buffer;
		std::string _text;
		GLint _size;
		glm::vec2 _position;
		FT_Face _fontFace;
		FT_Library* _library;
		Color _color;
	};
}
