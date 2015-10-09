#include "PhysicsComponent.h"
using namespace misc;

void PhysicsComponent::init()
{
	_bDef.type = b2_dynamicBody;
	_bDef.position.Set(_position.x, _position.y);
	_shape.SetAsBox(_size.x, _size.y);

	_body = core::Siika2D::UI()->_boxWorld->CreateBody(&_bDef);
	//_world->CreateBody();
	_fixtureDef.shape = &_shape;
	_fixtureDef.density = _density;
	_fixtureDef.friction = _friction;
	_fixtureDef.restitution = _restitution;
	_body->CreateFixture(&_fixtureDef);

};