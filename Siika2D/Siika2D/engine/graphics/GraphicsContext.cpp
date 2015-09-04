#include "GraphicsContext.h"

using namespace graphics;

GraphicsContext::GraphicsContext(android_app *app)
{
	s2d_info("GRAPHICS CONTEXT CREATED");
	initializeContext(app);
}


GraphicsContext::~GraphicsContext()
{
	wipeContext();
}

void GraphicsContext::wipeContext()
{
	if (_display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (_context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(_display, _context);
		}

		if (_surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(_display, _surface);
		}

		eglTerminate(_display);
	}

	s2d_info("WIPED GRAPHICS_CONTEXT");
	_display = EGL_NO_DISPLAY;
	_context = EGL_NO_CONTEXT;
	_surface = EGL_NO_SURFACE;

}


void GraphicsContext::initializeContext(android_app* app)
{

	s2d_info("INITING GRAPHICS CONTEXT");
	//Setting the color buffers' sizes etc.
	const EGLint configAttribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	EGLint contextAttribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	bool result;

	//This gets us the display of the android device
	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	result = (_display != nullptr && _display != EGL_NO_DISPLAY);
	s2d_assert(result == EGL_TRUE);

	//This initializes the display we just got
	result = eglInitialize(_display, 0, 0);
	s2d_assert(result == EGL_TRUE);

	//This sets the configurations for the display
	result = eglChooseConfig(_display, configAttribs, &_config, 1, &_numConfig);
	s2d_assert(result == EGL_TRUE);

	result = eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &_format);
	s2d_assert(result == EGL_TRUE);

	ANativeWindow_setBuffersGeometry(app->window, 0, 0,_format);

	_surface = eglCreateWindowSurface(_display, _config, app->window, NULL);
	result = (_surface != nullptr);
	s2d_assert(result == EGL_TRUE);

	_context = eglCreateContext(_display, _config, NULL, contextAttribs);
	result = (_context != nullptr);
	s2d_assert(result == EGL_TRUE);
	

	result = eglMakeCurrent(_display, _surface, _surface, _context);
	s2d_assert(result == EGL_TRUE);

	result = eglQuerySurface(_display, _surface, EGL_WIDTH, &_windowWidth);
	s2d_assert(result == EGL_TRUE);
	result = eglQuerySurface(_display, _surface, EGL_HEIGHT, &_windowHeight);
	s2d_assert(result == EGL_TRUE);
	

	glClearColor(0, 1, 0, 1);


	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

}

void GraphicsContext::swap()
{
	if (_display != EGL_NO_DISPLAY && _surface != EGL_NO_SURFACE)
	eglSwapBuffers(_display, _surface);
}
void GraphicsContext::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

glm::vec2 GraphicsContext::getDisplaySize()
{
	return glm::vec2(_windowWidth, _windowHeight);
}