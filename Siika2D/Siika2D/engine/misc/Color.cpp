#include "Color.h"

using namespace graphics;

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	_glRed = ((float) red) / 255.f;
	_glGreen =((float) green) / 255.f;
	_glBlue = ((float) blue) / 255.f;
	_glAlpha = ((float) alpha) / 255.f;
}

Color::Color(COLOR color)
{
	switch (color)
	{
	case RED:
		_glRed = 1.0f;
		_glGreen = 0.0f;
		_glBlue = 0.0f;
		_glAlpha = 1.0f;
		break;
	case GREEN:
		_glRed = 0.0f;
		_glGreen = 1.0f;
		_glBlue = 0.0f;
		_glAlpha = 1.0f;
		break;
	case BLUE:
		_glRed = 0.0f;
		_glGreen = 0.0f;
		_glBlue = 1.0f;
		_glAlpha = 1.0f;
		break;
	}
}

Color::~Color()
{

}

void Color::setColor(COLOR color)
{
	switch (color)
	{
	case RED:
		_glRed = 1.0f;
		_glGreen = 0.0f;
		_glBlue = 0.0f;
		_glAlpha = 1.0f;
		break;
	case GREEN:
		_glRed = 0.0f;
		_glGreen = 1.0f;
		_glBlue = 0.0f;
		_glAlpha = 1.0f;
		break;
	case BLUE:
		_glRed = 0.0f;
		_glGreen = 0.0f;
		_glBlue = 1.0f;
		_glAlpha = 1.0f;
		break;
	}
}

void Color::setRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	_glRed = red / 255.f;
	_glGreen = green / 255.f;
	_glBlue = blue / 255.f;
	_glAlpha = alpha / 255.f;
}

void Color::setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
	_glRed = red / 255.f;
	_glGreen = green / 255.f;
	_glBlue = blue / 255.f;
}

void Color::setAlpha(uint8_t alpha)
{
	_glAlpha = alpha / 255.f;
}

uint8_t Color::getR()
{
	return uint8_t(_glRed * 255);
}

uint8_t Color::getG()
{
	return uint8_t(_glGreen * 255);
}

uint8_t Color::getB()
{
	return uint8_t(_glBlue * 255);
}

uint8_t Color::getA()
{
	return uint8_t(_glAlpha * 255);
}

glm::vec4 Color::getGLColor()
{
	return glm::vec4(_glRed, _glGreen, _glBlue, _glAlpha);
}