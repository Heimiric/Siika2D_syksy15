#pragma once
#include <stdlib.h>
#include "vec4.hpp"
#include "GLES2\gl2.h"


namespace graphics
{
	/**
		Enumerators for basic colors:
		RED, GREEN, BLUE
		*/
	enum COLOR
	{
		RED, GREEN, BLUE
	};

	/**
		Basic color, 4 channels RGBA.
		Values are given in 0-255 format as uint8_t and stored internally as floats between 0-1.

		Enums for basic colors.
		*/
	class Color
	{
	public:



		/**
			Constructor.
			Set RGBA color values between 0-255.
			Default value for alpha = 255.
			*/
		Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

		/**
			Constructor.
			Set RGBA color values according to color enum.
			*/
		Color(COLOR color);
		~Color();

		/**
			Set RGBA color values according to color enum.
			*/
		void setColor(COLOR color);

		/**
			Set RGBA color values between 0-255.
			*/
		void setRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

		/**
			Set RGB color values between 0-255.
			*/
		void setRGB(uint8_t red, uint8_t green, uint8_t blue);

		/**
			Set alpha channel value between 0-255.
			*/
		void setAlpha(uint8_t alpha);

		/**
			Returns red channel value
			*/
		uint8_t getR();

		/**
			Returns green channel value
			*/
		uint8_t getG();

		/**
			Returns blue channel value
			*/
		uint8_t getB();

		/**
			Returns alpha channel value
			*/
		uint8_t getA();

		/**
			Returns GLfloat color values 
		*/
		glm::vec4 getGLColor();


	private:
		GLfloat _glRed, _glGreen, _glBlue, _glAlpha;

	};
}