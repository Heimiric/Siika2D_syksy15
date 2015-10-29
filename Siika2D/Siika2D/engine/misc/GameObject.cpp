#include "GameObject.h"

using namespace misc;

GameObject::GameObject()
{
	transf = core::Siika2D::UI()->transfCrds();
}
GameObject::GameObject(glm::vec2 position, graphics::Texture * spriteTexture, glm::vec2 size, glm::vec2 origin)
{
	transf = core::Siika2D::UI()->transfCrds();
	addComponent(new TransformComponent());
	addComponent(new SpriteComponent(core::Siika2D::UI()->_spriteManager->createSprite
				(transf->userToDevice(position), transf->userToDevice(size), transf->userToDevice(origin), spriteTexture, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f))));
	//addComponent(new PhysicsComponent(transf->userToDToBox2d(-position), transf->pixelsToBox2d(size), 1, 1, 0.5)); //Need to debug this
	addComponent(new PhysicsComponent(transf->pixelsToBox2d(position), transf->pixelsToBox2d(size), 99999, 1, 0.5));
	//addComponent(new PhysicsComponent(glm::vec2(0, -7.0), glm::vec2(12.8, .64), 999999, 1, 0.5));
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	transf = core::Siika2D::UI()->transfCrds();
	TransformComponent* transformComp = getComponent<TransformComponent>();
	if (transformComp != nullptr)
	{
		PhysicsComponent* physicsComp = getComponent<PhysicsComponent>();
		if (physicsComp != nullptr)
		{
			b2Vec2 pos = physicsComp->_body->GetPosition();
			glm::vec2 gPos = transf->box2dToUToDevice(glm::vec2(pos.x, pos.y));
			pos.x = gPos.x;
			pos.y = gPos.y;
			//pos = transf->Box2dToPixels(pos);
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
void GameObject::move(glm::vec2 moveTo)
{
	moveTo.y = -moveTo.y;
	TransformComponent* transformComp = getComponent<TransformComponent>();
	if (transformComp != nullptr)
	{
		transformComp->setPosition(transf->userToDevice(moveTo));
	}

	PhysicsComponent* physicsComp = getComponent<PhysicsComponent>();
	if (physicsComp != nullptr)
	{
		physicsComp->setPosition(transf->pixelsToBox2d(moveTo));
	}

	SpriteComponent* spriteComp = getComponent<SpriteComponent>();
	if (spriteComp != nullptr)
	{
		spriteComp->getSprite()->setPosition(transf->userToDevice(moveTo));
	}
}
void GameObject::addComponent(Component* component)
{
	if (typeid(*component) == typeid(PhysicsComponent))
		((PhysicsComponent*)component)->_body->SetUserData(this);
	_components.insert(std::make_pair(&typeid(*component), component));
}