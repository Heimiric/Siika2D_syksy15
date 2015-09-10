#include "GameObject.h"

using namespace misc;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	TransformComponent* transformComp = getComponent<TransformComponent>();
	if (transformComp != nullptr)
	{
		SpriteComponent* spriteComp = getComponent<SpriteComponent>();
		if (spriteComp != nullptr)
		{
			graphics::Sprite* spriteToUpdate = spriteComp->getSprite();

			spriteToUpdate->setPosition(transformComp->getPosition());
			spriteToUpdate->setRotation(transformComp->getRotation());
		}
	}
}

void GameObject::addComponent(Component* component)
{
	_components.insert(std::make_pair(&typeid(*component), component));
}