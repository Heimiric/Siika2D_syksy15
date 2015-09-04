#pragma once

#include "../graphics/SpriteManager.h"

class GameObject
{
public:
	GameObject(graphics::Sprite* sprite);
	~GameObject();

	glm::vec2 getPosition();

	void move(GLfloat x, GLfloat y);
	void move(glm::vec2 moveVec);
	//void rotate(GLfloat rotation);
	
private:
	graphics::Sprite* _sprite;
};