#pragma once

#include <EGL/egl.h>
#include <GLES2\gl2.h>
#include <../glm/vec2.hpp>
#include "../../native_app_glue/android_native_app_glue.h"
#include "../core/ErrorHandler.h"

/**
	Initializes OpenGL ES 2.0 context
		and wipes it when needed
*/
namespace core
{
	class Siika2D;
}

namespace graphics
{

	class GraphicsContext
	{

		friend class core::Siika2D;

	public:
	
	
	
		/**
			Clears the screen with a color (default green)
		*/
		void clear();
		/**
			Swap buffers
		*/
		void swap();

		glm::vec2 getDisplaySize();


	protected:

	

		/**
			Clears the context thoroughly
		*/
		void wipeContext();

		GraphicsContext(android_app *app);
		~GraphicsContext();

		/**
			Initializes OpenGL ES 2.0 context
		*/
		void initializeContext(android_app* app);

		EGLDisplay _display;
		EGLint _windowWidth, _windowHeight, _format, _numConfig;
		EGLConfig _config;
		EGLSurface _surface;
		EGLContext _context;

	};
}