#include "SpriteManager.h"
using namespace graphics;



void SpriteManager::drawSprites()
{
	GLint err = glGetError();
	s2d_assert(err == 0);
	Texture * oldTexture = nullptr;
	std::vector<GLfloat> vertices;
	std::vector<GLint> indecis;
	int spriteCount = 0;
	std::vector<Sprite*> spritesToRemove;

	//GLfloat vertices[16]; // Pos Tex
	//Goes through a list of shaders in use and sprites drawn with them / std::list<sprite>
	for(std::unordered_map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		//needs to do spritebatch here
		//batchSprites(*it->second);
		GLint p = position, c = color, t = texture;
		Shader * curShader = it->first;

		err = glGetError();
		s2d_assert(err == 0);

		curShader->use();

		err = glGetError();
		s2d_assert(err == 0);
		//it->first->use(); // shader->use()
		// TODO: Check for changes before recreating buffer
		//BufferManager buf = (*it->second).buffer;
		if(!curShader->hasColor())
			c = unknown;
		if(!curShader->hasTexture())
			t = unknown;

		err = glGetError();
		s2d_assert(err == 0);

		//_bufferManager = &buf;

		_bufferManager->setAttributes(p, c, t);
		Sprite * sprt = *(*it->second).sprites.begin();
		//Goes through all sprites drawn with a specific shader
		for(std::vector<Sprite*>::iterator sit = (*it->second).sprites.begin(); sit != (*it->second).sprites.end(); sit++)
		{
			if(!(*sit)->_delete || !(*sit)->_draw)
			{
				glm::vec2 * positions = (*sit)->getPositions();
				glm::vec2 * textures = (*sit)->getTexturePos();
				graphics::Color * col = (*sit)->getColor();
				(*sit)->getPositions();
				if(c == unknown)
					_bufferManager->addRectangle(positions, textures, nullptr);
				else
					_bufferManager->addRectangle(positions, textures, col);

				//Pitää batchata / tarkistaa onko tekstuuri vaihtunut
				if(oldTexture != (*sit)->_texture);
					glBindTexture(GL_TEXTURE_2D, (*sit)->_texture->getTexture());
				_bufferManager->draw(); //This needs to be elsewhere
				_bufferManager->clear();
			}
			else
			{
				if((*sit)->_delete)
					spritesToRemove.push_back((*sit));
			}
			
		}
		//for(std::vector<sprite*>)
		spritesToRemove.clear();
		glBindTexture(GL_TEXTURE_2D, 0u);
		//err = glGetError();
		//s2d_assert(err == 0);
		//glBindTexture(GL_TEXTURE_2D, sprt->_texture->getTexture());
		//err = glGetError();
		//_bufferManager->draw();
		////buf.draw();
		//err = glGetError();
		//s2d_assert(err == 0);

		//glBindTexture(GL_TEXTURE_2D, 0u);
		////glActiveTexture(0);
		//_bufferManager->clear();
		//err = glGetError();
		//s2d_assert(err == 0);
		
		it->first->use(false);
	}
}
Sprite * SpriteManager::createSprite()
{
	return createSprite((Sprite*)nullptr);
}
SpriteManager::SpriteManager(ShaderManager *shaderManager, BufferManager * bufMan)
{
	_bufferManager = bufMan;
	_shaderManager = shaderManager;
	int size = _sprites.size();
}
SpriteManager::~SpriteManager()
{
	for(std::unordered_map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		(*it->second).sprites.clear();
	}

}
Sprite * SpriteManager::createSprite(Sprite * sprite)
{
	
	Shader * shdr = _shaderManager->getShader();
	if(!sprite)
		sprite = new Sprite();
	sprites_buffer * bfr;
	if(_sprites.size() != 0)
		for (std::unordered_map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
		{
			if(it->first == shdr) // Sprites with this shader already exist
			{
				(*it->second).sprites.push_back(sprite);
				return sprite;
			}
		}
	bfr = new sprites_buffer;
	//bfr->buffer.setAttributes(position, unknown, texture);
	bfr->sprites.push_back(sprite);
	_sprites.insert(std::pair<Shader*, sprites_buffer*>(shdr, bfr));
	return sprite;
}

Sprite * SpriteManager::createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR)
{
	Sprite * sprt = new Sprite(location, spriteSize, spriteOrigin, texture, textureUL, textureLR);
	createSprite(sprt);
	return sprt;
}

Sprite * SpriteManager::createSprite(Texture * texture)
{
	Sprite * sprt = new Sprite(glm::vec2(0.f, 0.f), texture->getSize() , glm::vec2(0.f, 0.f), texture, glm::vec2(0.f,0.f), glm::vec2(1.f, 1.f));
	createSprite(sprt);
	return sprt;
}

/*
SpriteManager::~SpriteManager()
{
	for(std::map<Shader*, sprites_buffer*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
	{
		(*it->second).sprites.empty();
	}

}
*/

bool SpriteManager::compareSpriteZs(Sprite &sprite1, Sprite &sprite2)
{
	if (sprite1._posZ > sprite2._posZ)
		return true;
	else
		return false;
}


void SpriteManager::spriteBatcher(std::vector<Sprite> *toBatch)
{
	int i, j;
	

	for ( i = 0; i < toBatch->size(); i++)
	{
		for (j = i + 1; j < toBatch->size(); j++)
		{
			if (!compareSpriteZs(toBatch->at(i), toBatch->at(j)))
			{
					Sprite temp = toBatch->at(j);
					toBatch->at(j) = toBatch->at(i);
					toBatch->at(i) = temp;
			}
		}
	}

	for (i = 0; i < toBatch->size(); i++)
	{
		for (j = i + 1; j < toBatch->size(); j++)
		{
			if (toBatch->at(i)._posZ == toBatch->at(j)._posZ)
			{
				if (toBatch->at(i)._texture->getTexture() < toBatch->at(j)._texture->getTexture())
				{
						Sprite temp = toBatch->at(j);
						toBatch->at(j) = toBatch->at(i);
						toBatch->at(i) = temp;
				}
			}
		}
	}

}