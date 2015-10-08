#include "TextureManager.h"

using namespace graphics;

TextureManager::TextureManager(core::ResourceManager* resourceManager)
{
	_resourceManager = resourceManager;
}

TextureManager::~TextureManager()
{

}

Texture* TextureManager::createTexture(std::string filename)
{
	std::map<std::string, Texture>::iterator it = _createdTextures.find(filename);
	if (it != _createdTextures.end())
		return &it->second;
	else
	{
		core::ImageData* image = _resourceManager->loadImage(filename);
		Texture texture(image->height, image->height, &image->data);

		_createdTextures.insert(std::make_pair(filename, texture));

		return &_createdTextures.at(filename);
	}
}

void TextureManager::InitializeTextures()
{
	std::map<std::string, Texture>::iterator it = _createdTextures.begin();
	for (it; it != _createdTextures.end(); it++)
	{
		it->second.initialize();
	}
}