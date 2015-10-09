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

void PhysicsComponent::applyForce(b2Vec2 _force, bool wake)
{
	_body->ApplyForce(_force,_body->GetWorldCenter(), wake);
}

void PhysicsComponent::applyLinearForce(b2Vec2 _force, bool wake)
{
	_body->ApplyLinearImpulse(_force, _body->GetWorldCenter(), wake);
}

void PhysicsComponent::applyTorgue(float32 torgue, bool wake)
{
	_body->ApplyTorque(torgue, wake);
}

void PhysicsComponent::applyAngularTorgue(float32 torgue, bool wake)
{
	_body->ApplyAngularImpulse(torgue, wake);
}