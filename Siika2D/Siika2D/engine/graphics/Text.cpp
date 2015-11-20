#include "Text.h"

using namespace graphics;

Text::Text(core::ResourceManager* resourceManager, FT_Library* ftLibrary) :_color(255, 255, 255, 255)
{
	_resourceManager = resourceManager;
	_library = ftLibrary;

	setPosition(0, 0);
	_size = 18;
	isInitialized = false;
}


Text::~Text()
{

}


void Text::setFont(std::string filename)
{
	std::vector<unsigned char>* fontData = _resourceManager->loadFile(filename);
	int error = FT_New_Memory_Face(*_library, fontData->data(), sizeof(unsigned char)*fontData->size(), 0, &_fontFace);
	s2d_assert(error == 0);

	setFontSize(_size);

	isInitialized = true;
}


void Text::setFontSize(GLint size)
{
	_size = size;
	int error = FT_Set_Pixel_Sizes(_fontFace, _size, _size);
	s2d_assert(error == 0);
}


void Text::setText(std::string text)
{
	_text = text;
}


void Text::setPosition(GLfloat x, GLfloat y)
{
	_position = glm::vec2(x, -y);
}


void Text::setColor(Color color)
{
	_color = color;
}

Color Text::getColor()
{
	return _color;
}

void Text::draw(glm::vec2 displaySize, GLint posLoc, GLint colLoc, Buffer * buf, GLuint _program)
{
	//_buffer.bindBuffer();

	//Position vertex attribute pointer
	glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast <GLvoid*>(0));

	GLint textureSampler = glGetUniformLocation(_program, "tex");

	GLint error = glGetError();
	//GLuint texture;
	//glActiveTexture(GL_TEXTURE0);
	//glGenTextures(1, &texture);
	//GLint error = glGetError();
	//s2d_assert(error == 0);

	//glActiveTexture(GL_TEXTURE0);
	//error = glGetError();
	//s2d_assert(error == 0);

	//glBindTexture(GL_TEXTURE_2D, texture);
	//error = glGetError();
	//s2d_assert(error == 0);

	//glUniform1i(textureSampler, 0);
	//error = glGetError();
	//s2d_assert(error == 0);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//error = glGetError();
	//s2d_assert(error == 0);

	//glGetUniformLocation();

	//Uniform color
	glm::vec4 glCol = _color.getGLColor();
	GLfloat tempCol[4] = { glCol.r, glCol.g, glCol.b, glCol.a };
	glUniform4fv(colLoc, 1, tempCol);

	const char* pointerToText;

	FT_GlyphSlot glyph = _fontFace->glyph;
	//GLuint texname;
	float x = _position.x;
	float y = -_position.y;
	float scaleX = 2.0 / displaySize.x;
	float scaleY = 2.0 / displaySize.y;
	// Tämä silmukka piirtää tekstin. Joka kirjaimelle oma kuva (tekstuuri)
	
	for (pointerToText = _text.c_str(); *pointerToText; pointerToText++)
	{
		GLuint texture;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &texture);
		s2d_assert(error == 0);

		glActiveTexture(GL_TEXTURE0);
		error = glGetError();
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

		//glGenTextures(1, &texname);
		//glBindTexture(GL_TEXTURE_2D, texname);
		if (FT_Load_Char(_fontFace, *pointerToText, FT_LOAD_RENDER))
			continue;


		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyph->bitmap.width,
			glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyph->bitmap.buffer
			);

		GLint error = glGetError();
		s2d_assert(error == 0);

		float x2 = x + glyph->bitmap_left * scaleX;
		float y2 = -y - glyph->bitmap_top * scaleY;
		float w = glyph->bitmap.width * scaleX;
		float h = glyph->bitmap.rows * scaleY;

		GLfloat box[4][4] = {
			{ x2, -y2, 0, 0 },
			{ x2 + w, -y2, 1, 0 },
			{ x2, -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		buf->setBufferData(box, sizeof(box));
		//_buffer.setBufferData(box, sizeof(box));
		error = glGetError();
		s2d_assert(error == 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		error = glGetError();
		s2d_assert(error == 0);

		x += (glyph->advance.x >> 6) * scaleX;
		y += (glyph->advance.y >> 6) * scaleY;
		glDeleteTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//glBindTexture(GL_TEXTURE_2D, 0);

	//_buffer.unbindBuffer();
}