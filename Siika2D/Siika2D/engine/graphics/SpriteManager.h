#pragma once
#include <vector>
#include "Sprite.h"
#include "Shader.h"
#include "BufferManager.h"
#include "ShaderManager.h"
#include <unordered_map>
#include "../glm/vec2.hpp"
#include "Texture.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include <algorithm>

namespace core
{
	class Siika2D;
}

namespace graphics
{
	/**
		Class for managing sprites
	*/
	class SpriteManager
	{
		
		friend class core::Siika2D;

	public:
		SpriteManager(ShaderManager *shaderManager, BufferManager * bufMan);
		~SpriteManager();
		//Sprite * createSprite();
		/**Creates sprite with given parameters
		To use spritesheet use texture limits lower than 1
		For example 0.2 0.2 would create 5x5 sprite sheet
		*/
		Sprite * createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR);
		/**
			Creates sprite with the given texture.
			Sets location to 0,0
			Sets spriteSize to match the texture's size
			Sets origin to 0,0
			Sets texture bounds to the full texture
		*/
		Sprite * createSprite(Texture * texture);
		Sprite * createSprite(Sprite * sprite);
		//remove sprite
		void removeSprite(Sprite*);
		///Draws all created sprites
		void drawSprites();
	protected:
		struct sprites_buffer
		{
			std::vector<Sprite*> sprites;
			BufferManager buffer;
		};
		BufferManager * _bufferManager;
		std::vector<Sprite*>_sprites;
		//std::unordered_map<Shader*, sprites_buffer*> _sprites;
		///Batches the given vector of sprites
		void spriteBatcher(std::vector<Sprite*> *toBatch);
		ShaderManager* _shaderManager;
		//std::map<Shader*, sprites_buffer> _sprites;
		/**
		Compares Z position between 2 sprites from the 'sprites' vector
		*/
		bool compareSpriteZs(Sprite *sprite1, Sprite *sprite2);
		/**
		Sorts sprites vector by comparing Z positions and textures
		*/

	};
}