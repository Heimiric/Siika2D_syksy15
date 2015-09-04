#include "ErrorHandler.h"

using namespace core;

void ErrorHandler::logError(int lineNumber, std::string filename)
{
	s2d_error("FILE: %s LINE: %i", filename.c_str(), lineNumber);
}