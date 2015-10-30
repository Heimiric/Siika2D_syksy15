#pragma once

#include "Component.h"
#include "../graphics/Sprite.h"

namespace misc
{
	/**
		Component class for adding sprite functionality to GameObject.
		Takes a pointer to a sprite as a parameter upon creation.
	*/
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(graphics::Sprite* sprite)
		{
			_sprite = sprite;
		}

		~SpriteComponent()
		{
			_sprite->setDelete(true);
			_sprite = nullptr;
		}

		/**
			Retrives sprite pointer from the component.
		*/
		graphics::Sprite* getSprite()
		{
			return _sprite;
		}
		/**
			Sets draw order higher is on front
		*/
		void setZ(int z)
		{
			_sprite->setZ(z);
		}

	private:
		graphics::Sprite* _sprite;
	};
}