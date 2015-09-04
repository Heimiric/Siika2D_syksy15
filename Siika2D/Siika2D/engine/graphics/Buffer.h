#pragma once

#include "../core/ErrorHandler.h"

#include <GLES2\gl2.h>
#include <cstdlib>
#include <vector>


namespace graphics
{
	/**
		Buffers for drawn vertices and indices.
	*/
	class Buffer
	{

	public:

		/**
			Constructor.
			Set buffer type and usage pattern.
			Generate buffer.

			Use GLenum values for bufferType and usagePattern.
			usagePattern is GL_STATIC_DRAW by default.
		*/
		Buffer(GLenum bufferType, GLenum usagePattern = GL_STATIC_DRAW);

		/**
			Destructor.
			Unbind and delete buffer.
		*/
		~Buffer();

		/**
			Set usage pattern for buffer.
			Use GLenum values.
		*/
		void setUsagePattern(GLenum usagePattern);

		/**
			Redefines some or all of the data store for the buffer object.

			Give pointer to data and data size in bytes for buffer.
			Give offset measured in bytes, where to start replacing data.
			Offset is set to 0 by default.
		*/
		void subBufferData(void* bufferData, GLsizei size, GLint offset = 0);

		/**
			Give pointer to data and data size in bytes for buffer.
		*/
		void setBufferData(void* bufferData, GLsizei size);


		/**
			Bind buffer object.
		*/
		void bindBuffer();

		/**
			Unbind buffer object.
		*/
		void unbindBuffer();

	private:

		GLenum _bufferType;
		GLenum _usagePattern;
		GLuint _buffer;
	};
}