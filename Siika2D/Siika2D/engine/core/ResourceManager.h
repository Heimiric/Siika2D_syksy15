#pragma once

#include <lodepng.h>
#include <vector>
#include <map>
#include <android/asset_manager.h>
#include "..\misc\File.h"
#include "ErrorHandler.h"

namespace core
{
	/**
		Struct for storing image data, height and width.
		*/
	struct ImageData
	{
		std::vector<unsigned char> data;
		unsigned int height, width;
	};

	/**
		Struct for storing audio data, start and length
	*/
	struct AudioData
	{
		int fileDescriptor;
		off_t start, length;
	};

	/**
		All assets are loaded through ResourceManager.
		Keeps track of loaded assets.
		*/
	class ResourceManager
	{

	public:
		ResourceManager();
		~ResourceManager();


		void init(AAssetManager* assetManager);

		/**
			Loads png image with given filename or returns an existing one.
			Uses lodepng and android assetmanager for decoding.
			Returns image struct.
			*/
		ImageData* loadImage(std::string filename);

		/**
			Loads audio file with given filename or returns an existing one.
			Uses AAsset_openFileDescriptor. Only supports OGG files.
			Returns Audio struct.
		*/
		AudioData* loadAudio(std::string filename);

		/**
			Loads text file with given filename or returns an existing one.
			Uses android assetmanager.
			Returns text from file as a std::string
			*/
		std::string* loadTextFile(std::string filename);
		/**
		Gets an open file from external storage for write. Need to call fclose() when done
		*/
		FILE * getFileForWrite(std::string filename);
		/**
		Gets a open file from external storage for read. Need to call fclose() when done
		*/
		FILE * getFileForRead(std::string filename);
		/**
			Loads any file type or returns an existing one.
			Returns file data as a vector of unsigned characters.
		
		*/
		misc::File * getFile(std::string filename);
		std::vector<unsigned char>* loadFile(std::string filename);
		//TODO:
		//loadSound()
		//loadFont()

	private:
		std::map<std::string, ImageData> _loadedImages;
		std::map<std::string, AudioData> _loadedAudio;
		std::map<std::string, std::string> _loadedTextFiles;
		std::map<std::string, std::vector<unsigned char>> _loadedData;
		AAssetManager* _androidAssetManager;
		std::map<std::string, misc::File> _FilesInExtStrg;
		//Load asset file from android's assetmanager
		std::vector<unsigned char> loadAsset(std::string filename);
		//TODO: container for other file types

	};
}

