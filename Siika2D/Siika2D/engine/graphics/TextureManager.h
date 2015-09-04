#pragma once

#include "../core/ResourceManager.h"
#include "Texture.h"

namespace core
{
	class Siika2D;
}

namespace graphics
{
	/**
		Textures are created in TextureManager.
		Keeps track of created textures.
		*/
	class TextureManager
	{

	friend class core::Siika2D;

	public:
		/**
			Constructor.
			Takes a reference to ResourceMananager as a parameter.
			*/
		TextureManager(core::ResourceManager* resourceManager);
		~TextureManager();

		/**
			Creates new texture from image file or returns an existing one.
			Image is loaded with ResourceManager.
			*/
		Texture* createTexture(std::string filename);

	private:
		core::ResourceManager* _resourceManager;
		std::map<std::string, Texture> _createdTextures;
	};
}