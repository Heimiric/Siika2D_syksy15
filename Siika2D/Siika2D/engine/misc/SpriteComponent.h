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

		~SpriteComponent(){}

		/**
			Retrives sprite pointer from the component for use.
		*/
		graphics::Sprite* getSprite()
		{
			return _sprite;
		}

	private:
		graphics::Sprite* _sprite;
	};
}