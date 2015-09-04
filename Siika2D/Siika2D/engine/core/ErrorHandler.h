#pragma once

#include <string>
#include <android/log.h>
#include <cstdlib>

#ifndef NDEBUG
#define s2d_assert(expression) if(!expression)(core::ErrorHandler::logError(__LINE__,__FILE__), abort())
#define s2d_error(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "s2d_error", __VA_ARGS__))
#define s2d_info(...) ((void)__android_log_print(ANDROID_LOG_INFO, "s2d_info", __VA_ARGS__))
#endif

namespace core
{

	/**
		Static class.

		Used for assertion-like error handling.
		Handler logs custom message to logcat(tag: s2d_error).
		Aborts program on error while debugging is defined.
		*/
	class ErrorHandler
	{
	public:

		/**
			Prints filename and line number to logcat.
			Aborts program.
			Use __LINE__ macro for lineNumber and __FILE__ for filename.
			*/
		static void logError(int lineNumber, std::string filename);
	
	};
}