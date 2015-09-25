#pragma once
#include "Texture.h"
#include "..\glm\vec2.hpp"
#include "glm.hpp"
#include "..\misc\color.h"
#include <gtx/transform.hpp>

namespace graphics
{
	/**
	Sprite 
	When sprite is created it gets assigned the currently used shader, if no shader is set default one will be used

	*/
	class Sprite
	{
		friend class SpriteManager;
	public:
		/**
		Sets texture for sprite with given bounds
		*/
		void setTexture(Texture * TextureToSet, glm::vec2 textureUpperLeft, glm::vec2 textureLowerRigth){ _texture = TextureToSet; _textureUL = textureUpperLeft; _textureLR = textureLowerRigth; }
		void setPosition(glm::vec2 position);
		void setSize(glm::vec2 size){ _size = size; }
		void setOrigin(glm::vec2 origin){ _origin = origin; }
		void setColor(Color col)
		{ 
			if(!_col)
				_col = new Color(0,0,0,0);
			_col->setRGBA(col.getR(), col.getG(), col.getB(), col.getA()); 
		}
		/**
		Sets sprite rotation angle in degrees
		*/
		void setRotation(GLfloat angle){ _rotationAngle = angle; }
		/**
		Sets Z used for draw order 
		*/
		void setZ(int Z){ _posZ = Z; }
		/**
		Gets sprite position in given rotation
		*/
		const glm::vec2 * getPosition(){ return &_position; }
		Color * getColor(){ return _col; };
		/**
		False = sprite will not be drawn
		*/
		void setVisible(bool visible){ _draw = visible; }
		/**
		Gets next sprite in spritesheet will cycle trough and go back to first sprite
		*/
		void setDelete(bool toDelete){ _delete = toDelete; }
		bool getVisible(){ return _draw; }
		bool getToDelete(){ return _delete; }
		void step();
	protected:
		Sprite(){};
		Sprite(glm::vec2 position, glm::vec2 size, glm::vec2 origin) :
			_position(position), _size(size), _origin(origin), _texture(nullptr), _col(nullptr), _rotationAngle(0)
		{
			_col = new Color(0, 0, 0, 0);
		};
		/**
		Position: position of the sprite
		Size: size of the sprite
		Origin: origin point of the sprite in pixels 0,0 is upper left corner
		TextureToSet: Texture of the sprite
		TextureUpperLeft: Upper left corner of the texture in texture coordinates ie 0,0 is upperleft corner of the texture while 0.5,0 is middle-top
		textureLowerRigth: Lower right corner of the texture use 1.0,1.0 for full texture
		To use sprite sheets give texture coordinates that do not use the full texture ie UL: 0.0, 0.0 LR,0.2,0.2 makes a 5x5 grid
		use sprite::step() to move to next frame

		*/
		Sprite(glm::vec2 position, glm::vec2 size, glm::vec2 origin, Texture * TextureToSet, glm::vec2 textureUpperLeft, glm::vec2 textureLowerRigth) :
			_position(position), _size(size), _origin(origin), _texture(TextureToSet), _textureUL(textureUpperLeft), _textureLR(textureLowerRigth), _col(nullptr), _rotationAngle(0), _draw(true), _delete(false)
		{
			_col = new Color(0, 0, 0, 0);
		};
		~Sprite()
		{
			delete _col;
		};
	private:
		///Gets bounds of the sprite at given position
		glm::vec2 * getBounds(glm::vec2 pos);
		glm::vec2 _bounds[4];
		glm::vec2 * getPositions();
		glm::vec2 * getTexturePos();
		void rotate();
		Texture * _texture;
		glm::vec2 _origin, _size, _position;
		glm::vec2 _textureUL, _textureLR; // upperLeft, lowerRight
		int _posZ;
		GLfloat _rotationAngle;
		glm::vec2 _positions[4];
		glm::vec2 _texPos[4];
		Color * _col;
		bool _draw, _delete;
		void moveSprite();
	};
}