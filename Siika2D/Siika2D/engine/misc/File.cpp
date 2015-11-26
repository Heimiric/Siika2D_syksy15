#include "File.h"
using namespace misc;

long File::getLength()
{
	FILE * lngth = fopen((_path + _name).c_str(), "r");
	fseek(lngth, 0, SEEK_END);
	_length = ftell(lngth);
	rewind(lngth);
	fclose(lngth);
	return _length;
}
bool File::openFile(std::string mode)
{
	_file = fopen((_path + _name).c_str(), mode.c_str());
}
long File::appendToFile(std::string toWrite)
{
	if (openFile("a"))
	{
		fputs(toWrite.c_str(), _file);
		long pos = ftell(_file);
		fflush(_file);
		fclose(_file);
		return pos;
	}
	return -1;
}

long File::writeFile(std::string toWrite)
{
	if (openFile("w"))
	{
		fputs(toWrite.c_str(), _file);
		long pos = ftell(_file);
		fflush(_file);
		fclose(_file);
		return pos;
	}
	return -1;
}
std::string File::readFile()
{
	if (openFile("r"))
	{
		getLength();
		char * buffer = (char*)malloc(sizeof(char)*_length);
		fread(buffer, 1, _length, _file);
		//buffer[_length] = '\0';
		std::string retVal = buffer;
		delete buffer;
		fclose(_file);
		return retVal;
	}
	return "";

}