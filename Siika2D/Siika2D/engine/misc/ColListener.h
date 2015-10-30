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
	/**
		Class for collision checking all gameobjects.
		To check if a gameobject is colliding call getCollisionsFor(*GameObject to check) 
		returned vector contains all collisions for the given GameObject or nullptr if no collisions are found.
		When collisions have been handled the user needs to clear them from the vector.
	*/

	std::vector<misc::GameObject*>* getCollisionsFor(misc::GameObject * obj)
	{
		if (_collisions.find(obj) != _collisions.end())
		{
			if (_collisions.find(obj)->second.size() == 0)
				return nullptr;
			return &_collisions.find(obj)->second;
		}
		else
			return nullptr;
	}
	std::map<misc::GameObject*, std::vector<misc::GameObject*>>* getAllCollisions(){ return &_collisions; }
	colListener(){};
	~colListener(){};
private:

	void BeginContact(b2Contact* contact)
	{
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		misc::GameObject * obj1 = static_cast<misc::GameObject*>(bodyUserData);

		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		misc::GameObject * obj2 = static_cast<misc::GameObject*>(bodyUserData);
		addCollision(obj1, obj2);
		addCollision(obj2, obj1);
	};
	//Implement if needed
	//void EndContact(b2Contact* contact){}
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