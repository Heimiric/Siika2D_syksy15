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
	CoordTransform transf;
	TransformComponent* transformComp = getComponent<TransformComponent>();
	if (transformComp != nullptr)
	{
		PhysicsComponent* physicsComp = getComponent<PhysicsComponent>();
		if (physicsComp != nullptr)
		{
			b2Vec2 pos = physicsComp->_body->GetPosition();
			pos = transf.Box2dToPixels(pos);
			transformComp->setPosition(glm::vec2(pos.x, -pos.y));
			//transformComp->setPosition(glm::vec2(pos.x * 100, -pos.y * 100));
		}
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
	if (typeid(*component) == typeid(PhysicsComponent))
		((PhysicsComponent*)component)->_body->SetUserData(this);
	_components.insert(std::make_pair(&typeid(*component), component));
}