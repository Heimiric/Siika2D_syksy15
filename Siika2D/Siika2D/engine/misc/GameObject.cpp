#include "GameObject.h"

using namespace misc;

GameObject::GameObject(unsigned int id)
{
	_id = id;
}


GameObject::~GameObject()
{
}

void GameObject::addComponent(Component* component)
{
	_components.insert(std::make_pair(&typeid(*component), component));
}