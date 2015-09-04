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
		return &it->second;
	else
	{
		std::vector<unsigned char> assetData = loadAsset(filename);

		std::string loadedText(assetData.begin(), assetData.end());

		_loadedTextFiles.insert(std::make_pair(filename, loadedText));

		return &_loadedTextFiles.at(filename);
	}
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