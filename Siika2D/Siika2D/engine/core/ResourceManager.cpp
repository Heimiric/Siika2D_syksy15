#include "ResourceManager.h"

using namespace core;

ResourceManager::ResourceManager()
{
	_androidAssetManager = nullptr;
}

void ResourceManager::init(AAssetManager* assetManager)
{
	if (_androidAssetManager == nullptr)
	_androidAssetManager = assetManager;
}

ResourceManager::~ResourceManager()
{

}

ImageData* ResourceManager::loadImage(std::string filename)
{
	std::map<std::string, ImageData>::iterator it = _loadedImages.find(filename);
	if (it != _loadedImages.end())
		return &it->second;
	else
	{
		ImageData loadedImage;

		std::vector<unsigned char> assetData = loadAsset(filename);

		unsigned error = lodepng::decode(loadedImage.data, loadedImage.width, loadedImage.height, assetData);

		s2d_assert(error == 0);

		_loadedImages.insert(std::make_pair(filename, loadedImage));

		return &_loadedImages.at(filename);
	}
}

AudioData* ResourceManager::loadAudio(std::string filename)
{
	std::map<std::string, AudioData>::iterator it = _loadedAudio.find(filename);
	if (it != _loadedAudio.end())
		return &it->second;
	else
	{
		AudioData loadedAudio;

		AAsset* audioAsset = AAssetManager_open(_androidAssetManager, filename.c_str(), 2);
		s2d_assert((audioAsset != nullptr));

		int tempFileDescriptor = AAsset_openFileDescriptor(audioAsset, &loadedAudio.start, &loadedAudio.length);
		loadedAudio.fileDescriptor = tempFileDescriptor;

		_loadedAudio.insert(std::make_pair(filename, loadedAudio));

		AAsset_close(audioAsset);

		return &_loadedAudio.at(filename);
	}
}

std::string* ResourceManager::loadTextFile(std::string filename)
{
	std::map<std::string, std::string>::iterator it = _loadedTextFiles.find(filename);
	if (it != _loadedTextFiles.end())
	{
		return &it->second;
	}
	else
	{
		std::vector<unsigned char> assetData = loadAsset(filename);

		std::string loadedText(assetData.begin(), assetData.end());

		_loadedTextFiles.insert(std::make_pair(filename, loadedText));
		return &_loadedTextFiles.at(filename);
	}
}
FILE * ResourceManager::getFileForRead(std::string filename)
{
	char * buffer;
	std::string path = "/sdcard/" + filename;
	FILE* file = fopen(path.c_str(), "r");
	/*
	fseek(file, 0, SEEK_END);
	long lSize = ftell(file);
	rewind(file);
	buffer = (char*)malloc(sizeof(char)*lSize);
	fread(buffer, 1, lSize, file);
	s2d_info(buffer);
	*/
	return file;
}
FILE * ResourceManager::getFileForWrite(std::string filename)
{
	std::string path = "/sdcard/" +filename;
	FILE* file = fopen(path.c_str(), "w+");
	return file;
	/*
	fputs("HelloWorld !\n", file);
	fflush(file);
	fclose(file);
	return file;

	off_t start, length;
	AAsset* asset = nullptr;
	asset = AAssetManager_open(_androidAssetManager, filename.c_str(),AASSET_MODE_STREAMING);
	int i = AAsset_openFileDescriptor(asset, &start, &length);
	*/
	//FILE * file = fdopen(i, "w");
	//std::string path = "../assets/" + filename;
	//FILE * file = fopen(path.c_str(), "w");
	/*
	fseek(file, (long)start, SEEK_SET);
	fputs("hello world!\n", file);
	fflush(file);
	return file;
	*/
	//fclose(file);
}

std::vector<unsigned char>* ResourceManager::loadFile(std::string filename)
{
	std::map<std::string, std::vector<unsigned char>>::iterator it = _loadedData.find(filename);
	if (it != _loadedData.end())
		return &it->second;

	else
	{
		std::vector<unsigned char> assetData = loadAsset(filename);
		_loadedData.insert(std::make_pair(filename, assetData));
		return &_loadedData.at(filename);
	}
}

std::vector<unsigned char> ResourceManager::loadAsset(std::string filename)
{
	std::vector<unsigned char> assetData;
	AAsset* asset = nullptr;
	asset = AAssetManager_open(_androidAssetManager, filename.c_str(), 2);

	s2d_assert((asset != nullptr));

	unsigned int assetLength = AAsset_getLength(asset);
	//AAsset_read(asset, assetData.data(), assetLength);
	unsigned char * data = new unsigned char[assetLength];
	AAsset_read(asset, data, assetLength);
	for(int i = 0; i < assetLength; i++)
		assetData.push_back(data[i]);
	AAsset_close(asset);
	delete [] data;
	return assetData;
}