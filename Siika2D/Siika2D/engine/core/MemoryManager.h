#pragma once

#include <typeinfo>
#include <string>
//#include <iostream>
#include <map>
//#include <sstream>
//#include "ErrorHandler.h"


namespace core
{

	/** MemoryManager class keeps count of objects created by overloaded new will print out list of unfreed memory at ~MemoryManager

	*/
	class MemoryManager
	{
	public:
		#define print(...) ((void)__android_log_print(ANDROID_LOG_WARN, "MemoryManager", __VA_ARGS__))
		//void print(std::string line)
		//{
		//	std::cout << line;
		//}

		static MemoryManager& getInstance()
		{
			static MemoryManager mm;
			return mm;
		}
		///Adds file linenumber memoryaddress and size information of object created by new() to map
		void addRef(void * ptr, const char* file, int line, size_t size)
		{
			new_ptr_list list;
			list.file = file;
			list.line = line;
			list.size = size;
			nRefs.insert(std::pair<void*, new_ptr_list>(ptr, list));
		}
		///Removes information from map called on delete
		bool removeRef(void * ptr)
		{
			if(nRefs.size() < 1)
				return false;
			std::map<void *, new_ptr_list>::iterator it = nRefs.find(ptr);
			if(it != nRefs.end())
			{
				free(ptr);
				nRefs.erase(nRefs.find(ptr));
				return true;
			}
			return false;
		}

		/// Prints out reserved memory
		void getCount()
		{
			unsigned long size = 0;
			//std::ostringstream ss;
			print("Memory Reserved at: \n");
			for(std::map<void *, new_ptr_list>::iterator it = nRefs.begin(); it != nRefs.end(); it++)
			{
				//ss << (void*)it->first << " size: " << it->second.size << " file: " << it->second.file << ":" << it->second.line << "\n";
				print("%p size %i file: %s :%i", it->first, it->second.size, it->second.file, it->second.line);
				size += (unsigned long)it->second.size;
			}
			//ss << "Total size: " << size << "\n";
			print("Total size: %l", size);
			//print("%s", ss.str());
			//print(ss.str());

		}

	private:
		struct new_ptr_list
		{
			const char*         file;
			int                 line;
			size_t              size;
		};

		MemoryManager(){};
		~MemoryManager()
		{
			if(nRefs.size() > 0)
			{
				print("Memory leak\n");
				getCount();
			}
			else
				print("No leaks\n");
		};


		std::map <void *, new_ptr_list> nRefs;
	};

}

void* operator new(size_t size, const char* file, int line)
{
	void * ref = malloc(size);
	core::MemoryManager::getInstance().addRef(ref, file, line, size);
	return ref;
}
void* operator new(size_t size)
{
	return malloc(size);
	//return operator new(size, "<Unknown>", 0);
}
void* operator new[](size_t size, const char* file, int line)
{
	void * ref = operator new[](size);
	core::MemoryManager::getInstance().addRef(ref, file, line, size);
	return ref;
}
void operator delete(void* ptr)
{
	if(!core::MemoryManager::getInstance().removeRef(ptr))
		free(ptr);

}
void operator delete[](void* ptr)
{
	if(!core::MemoryManager::getInstance().removeRef(ptr))
		free(ptr);
}
//void operator delete(void* ptr, const char* file, int line) _NOEXCEPT;
//void operator delete[](void* ptr, const char* file, int line) _NOEXCEPT;
#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW
/*
#ifndef NDEBUG
#define NEW new(__FILE__, __LINE__)
#else
#define NEW new
#endif
*/