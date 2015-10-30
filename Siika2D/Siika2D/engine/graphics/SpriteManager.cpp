#include "SpriteManager.h"
using namespace graphics;



void SpriteManager::drawSprites()
{
	GLint err = glGetError();
	Texture * oldTexture = nullptr;
	std::vector<GLfloat> vertices;
	std::vector<GLint> indecis;
	int spriteCount = 0;
	Shader * curShader = nullptr;
	std::vector<Sprite*> spritesToRemove;
	spriteBatcher(&_sprites);
	//Goes through a list of shaders in use and sprites drawn with them / std::list<sprite>
	for (unsigned int i = 0; i < _sprites.size(); i++)
	{
		GLint p = position, c = color, t = texture;
		curShader = _sprites[i]->_shader;

		err = glGetError();
		s2d_assert(err == 0);
		curShader->use();
		err = glGetError();
		s2d_assert(err == 0);
		if(!curShader->hasColor())
			c = unknown;
		if(!curShader->hasTexture())
			t = unknown;


		_bufferManager->setAttributes(p, c, t);
		Sprite * sprt = _sprites[i];
		//Goes through all sprites drawn with a specific shader		
		if(!(sprt)->_delete || !(sprt)->_draw)
		{
			glm::vec2 * positions = (sprt)->getPositions();
			glm::vec2 * textures = (sprt)->getTexturePos();
			graphics::Color * col = (sprt)->getColor();
			(sprt)->getPositions();
			if(c == unknown)
				_bufferManager->addRectangle(positions, textures, nullptr);
			else
				_bufferManager->addRectangle(positions, textures, col);

			//Tarkistaa onko tekstuuri vaihtunut
			if (oldTexture != (sprt)->_texture);
				glBindTexture(GL_TEXTURE_2D, (sprt)->_texture->getTexture());
			_bufferManager->draw();
			_bufferManager->clear();
		}
		else
		{
			if ((sprt)->_delete)
				spritesToRemove.push_back((sprt));
		}
			
	}
	//for(std::vector<sprite*>)
	for (unsigned int i = _sprites.size(); i == 0; i--)
		for (unsigned int u = spritesToRemove.size(); u == 0; u--)
		{
			if (_sprites[i] == spritesToRemove[u])
			{
				delete _sprites[i];
				_sprites.erase(_sprites.end()-i);
			}
		}
	spritesToRemove.clear();

	glBindTexture(GL_TEXTURE_2D, 0u);
	curShader->use(false);
}

//Sprite * SpriteManager::createSprite()
//{
//	return createSprite((Sprite*)nullptr);
//}

SpriteManager::SpriteManager(ShaderManager *shaderManager, BufferManager * bufMan)
{
	_bufferManager = bufMan;
	_shaderManager = shaderManager;
	int size = _sprites.size();
}
SpriteManager::~SpriteManager()
{
	for(unsigned int i = 0; i < _sprites.size(); i++)
	{
		delete _sprites[i];
	}
	_sprites.clear();
}
Sprite * SpriteManager::createSprite(Sprite * sprite)
{
	
	Shader * shdr = _shaderManager->getShader();
	if(!sprite)
		sprite = new Sprite();

	_sprites.push_back(sprite);
	//bfr->buffer.setAttributes(position, unknown, texture);
	return sprite;
}

Sprite * SpriteManager::createSprite(glm::vec2 location, glm::vec2 spriteSize, glm::vec2 spriteOrigin, Texture * texture, glm::vec2 textureUL, glm::vec2 textureLR)
{
	Sprite * sprt = new Sprite(location, spriteSize, spriteOrigin, texture, textureUL, textureLR, _shaderManager->_currentShader);
	createSprite(sprt);
	return sprt;
}

Sprite * SpriteManager::createSprite(Texture * texture)
{
	Sprite * sprt = new Sprite(glm::vec2(0.f, 0.f), texture->getSize() , glm::vec2(0.f, 0.f), texture, glm::vec2(0.f,0.f), glm::vec2(1.f, 1.f), _shaderManager->_currentShader);
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

bool SpriteManager::compareSpriteZs(Sprite *sprite1, Sprite *sprite2)
{
	if (sprite1->_posZ > sprite2->_posZ)
		return true;
	else
		return false;
}


void SpriteManager::spriteBatcher(std::vector<Sprite*> *toBatch)
{
	int i, j;
	
	auto sortZ = [](Sprite *s1, Sprite *s2)
	{
		if (s1->_posZ > s2->_posZ)
			return true;
		else
			return false;
	};

	auto sortT = [](Sprite *s1, Sprite *s2)
	{
		if (s1->_texture->getTexture() > s1->_texture->getTexture())
			return true;
		else
			return false;
	};

	std::sort(toBatch->begin(), toBatch->end(), sortZ);//Sort based on z vector

	std::vector<int> zstart;
	int tempzstart = 0;
	int tempz = toBatch->at(0)->_posZ;

	for (int i = 0; i < toBatch->size(); i++)//Get start + end of z ranges
	{
		if (tempz > toBatch->at(i)->_posZ)
		{
			zstart.push_back(tempzstart);
			zstart.push_back(i - 1);

			tempzstart = i;
			tempz = toBatch->at(i)->_posZ;
		}
	}

	for (int i = 0; i < zstart.size(); i+=2)//Sort based on texture
	{
		std::sort(toBatch->begin()+zstart.at(i), toBatch->begin() + zstart.at(i+1), sortT);
	}
	//
	/*
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
	*/
}