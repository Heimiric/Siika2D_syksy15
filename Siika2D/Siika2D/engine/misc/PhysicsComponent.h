#pragma once
#include "Component.h"
#include "../graphics/Sprite.h"
#include "Box2D\Box2D.h"
#include "glm.hpp"
#include "../core/Siika2D.h"

namespace misc
{
	class PhysicsComponent:public Component
	{
	public:
		PhysicsComponent(glm::vec2 position, glm::vec2 size, float density = 1.0, float restitution = 0.5, float friction = 0) :_position(position), _size(size), _density(density), _friction(friction), _restitution(restitution)
		{
			init();
		};
		PhysicsComponent() :_size(1, 1), _position(0, 0), _density(1.0), _friction(0), _restitution(0.5)
		{ 
			init(); 
		};
		~PhysicsComponent(){};
		void setDensity(float density){_density = density;}
		void setRestitution(float restitution){ _restitution = restitution; }
		void setFriction(float friction){ _friction = friction; }
		void setSize(glm::vec2 size){ _size = size; }
		void setPosition(glm::vec2 position){ _position = position; }
		const glm::vec2 getPosition(){ return _position; }
		const glm::vec2 getSize(){ return _size; }

		//Box2d Components
		b2PolygonShape _shape;
		b2Body * _body;
		b2BodyDef _bDef;
		b2FixtureDef _fixtureDef;
		
	private:
		void init();
		glm::vec2 _size, _position;
		float _density;
		float _restitution;
		float _friction;
		
		
	};
}