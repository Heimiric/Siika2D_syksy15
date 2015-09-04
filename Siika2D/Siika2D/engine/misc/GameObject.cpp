#include "GameObject.h"

GameObject::GameObject(graphics::Sprite* sprite)
{
	_sprite = sprite;
}


GameObject::~GameObject()
{

}


glm::vec2 GameObject::getPosition()
{
	return *_sprite->getPosition();
}


void GameObject::move(GLfloat x, GLfloat y)
{
	glm::vec2 tempPos = *_sprite->getPosition();
	_sprite->setPosition(glm::vec2(tempPos.x + x, tempPos.y + y));
}


void GameObject::move(glm::vec2 moveVec)
{
	glm::vec2 tempPos = *_sprite->getPosition();
	_sprite->setPosition(tempPos+moveVec);
}


/*void GameObject::rotate(GLfloat rotation)
{
	_sprite->setRotation(_sprite->getRotation() + rotation);
}*/