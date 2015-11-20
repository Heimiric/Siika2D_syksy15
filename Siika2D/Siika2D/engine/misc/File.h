#pragma once
#include <stdio.h>
#include <string>
namespace core
{
	class ResourceManager;
}
namespace misc
{
	class File
	{
	friend class core::ResourceManager;
	public:
		/**
			Reads the file and returns it as a std::string
		*/
		std::string readFile();
		/**
			Empties the file and writes the contents of toWrite to it
		*/
		long writeFile(std::string toWrite);
		/**
			Appends toWrite to the end of the file
		*/
		long appendToFile(std::string toWrite);
		/**
			Gives access to the c FILE object for manual handling
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
		long _position,_length;
		FILE * _file;
		std::string _name;
		std::string _path = "/sdcard/";
	};
/*	sFile::~sFile()
	{
		fclose(_file);
		delete _file;
	}
	*/
}