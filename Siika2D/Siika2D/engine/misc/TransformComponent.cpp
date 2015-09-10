#include "TransformComponent.h"

using namespace misc;

TransformComponent::TransformComponent()
{
	_position = glm::vec2(0.f, 0.f);
	_rotationAngle = 0.f;
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::move(glm::vec2 move)
{
	_position += move;
}

void TransformComponent::rotate(float rotation)
{
	_rotationAngle += rotation;
}

void TransformComponent::setPosition(glm::vec2 position)
{
	_position = position;
}

void TransformComponent::setRotation(float angle)
{
	_rotationAngle = angle;
}

glm::vec2 TransformComponent::getPosition()
{
	return _position;
}

float TransformComponent::getRotation()
{
	return _rotationAngle;
}