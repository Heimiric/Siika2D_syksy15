#pragma once
#include <stdio.h>
#include <string>
namespace core
{
	class ResourceManager;
}
namespace misc
{
	/**
	Class for accessing files in external storage (SD card)
	Called from siika2d->UI()->getFile(filename)
	Has methods for writting, appending and reading files
	*/
	class File
	{
	friend class core::ResourceManager;
	public:
		/**
			Reads the file and returns contents as a std::string
			Returns empty string if no file exists
		*/
		std::string readFile();
		/**
			Creates a new file or empties existing file and writes the contents of toWrite into it
			Returns length of the file or -1 if error occurs
		*/
		long writeFile(std::string toWrite);
		/**
			Appends toWrite to the end of the file or creates a new file
			Returns length of the file or -1 if error occurs
		*/
		long appendToFile(std::string toWrite);
		/**
			Gives access to the c FILE object for manual handling 
			Clearing memory is handled by resourceManager do not delete
		*/
		FILE * getFilePtr(){ return _file; }
		//std::string readLine(){};
		//long writeLine(){};
		
		~File(){ delete _file; _file = nullptr; }
	protected:
		File(std::string name) :_name(name),_file(nullptr){};

	private:
		long getLength();
		bool openFile(std::string mode);
		void closeFile(){ fclose(_file); }
		long _length;
		FILE * _file;
		std::string _name;
		//Path of the stored files
		std::string _path = "/sdcard/";
	};
}