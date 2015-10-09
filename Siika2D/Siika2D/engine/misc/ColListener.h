#pragma once
#include "GameObject.h"
#include <Box2D\Box2D.h>
#include <map>
namespace misc
{
	class GameObject;
}
class colListener:public b2ContactListener
{
public:
	colListener(){};
	~colListener(){};
	void BeginContact(b2Contact* contact)
	{
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		misc::GameObject * obj1 = static_cast<misc::GameObject*>(bodyUserData);

		bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		misc::GameObject * obj2 = static_cast<misc::GameObject*>(bodyUserData);
		addCollision(obj1, obj2);
		addCollision(obj2, obj1);
	};
	void EndContact(b2Contact* contact){}

	std::vector<misc::GameObject*>* getCollisionsFor(misc::GameObject * obj)
	{
		if (_collisions.find(obj) != _collisions.end())
			return &_collisions.find(obj)->second;
		else
			return nullptr;
	}
private:
	std::map<misc::GameObject*, std::vector<misc::GameObject*>> _collisions;
	void addCollision(misc::GameObject* obj1, misc::GameObject* obj2)
	{
		if (_collisions.find(obj1) == _collisions.end())
		{
			std::vector<misc::GameObject*> vec;
			vec.push_back(obj2);
			_collisions.insert(std::make_pair(obj1, vec));
		}
		else
			_collisions.find(obj1)->second.push_back(obj2);
	}
};