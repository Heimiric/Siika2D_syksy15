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


		/**
		Applies instant force to physics body, adds to old movement vector
		*/
		void applyForce(glm::vec2 _force, bool wake = true);
		void applyForce(glm::vec2 _force, glm::vec2 _point, bool wake = true);
		/**
		Applies linear force that reaches true velocity after 1 sec, replacing old movement vector
		If you dont want force to affect center of mass, give point in range of 0-1 
		*/
		void applyLinearForce(glm::vec2 _force, bool wake = true);
		void applyLinearForce(glm::vec2 _force, glm::vec2 _point, bool wake = true);
		/**
		Applies instant torgue force to physics body
		*/
		void applyTorgue(float32 torgue, bool wake);
		/**
		Applies linear torgue force to physics body that reaches true velocity after 1 sec
		If you dont want force to affect center of mass, give point in range of 0-1
		*/
		void applyAngularTorgue(float32 torgue, bool wake);

		void setGravityScale(float32 _scale);

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