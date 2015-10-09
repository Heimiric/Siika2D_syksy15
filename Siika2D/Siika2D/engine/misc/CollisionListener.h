#pragma once
#include <Box2D\Box2D.h>
#include <map>
#include "GameObject.h"
namespace misc
{

	class collisionListener :public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact)
		{
			void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
			/*misc::GameObject * obj1 = static_cast<misc::GameObject*>(bodyUserData);

			bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
			misc::GameObject * obj2 = static_cast<misc::GameObject*>(bodyUserData);
			addCollision(obj1, obj2);
			addCollision(obj2, obj1);
			*/
			
		}
		/**
		Gets collisions for specified objects
		If no collisions are found returns nullptr
		*/
		/*std::vector<GameObject*>* getCollisionsFor(GameObject * obj)
		{ 
			if (_collisions.find(obj) != _collisions.end)
				return &_collisions.find(obj)->second;
			else
				return nullptr;
		}*/
		//void EndContact(b2Contact* contact){}

	private:
		//std::map<GameObject*, std::vector<GameObject*>> _collisions;
		/*
		void addCollision(GameObject* obj1, GameObject* obj2)
		{
			if (_collisions.find(obj1) == _collisions.end)
			{
				_collisions.insert(std::pair < GameObject*, std::vector<GameObject*>(obj1, std::vector<GameObject*>(obj2));
			}
			else
				_collisions.find(obj1)->second.push_back(obj2);
		}
		*/
	};
}