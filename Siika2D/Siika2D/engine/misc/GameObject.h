#pragma once

#include <typeinfo>
#include <map>
#include <unordered_map>
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "CoordTransform.h"
#include "../core/Siika2D.h"
namespace misc
{
	/**
		Component based GameObject.
		Made up from different components that determine what functionality the GameObject has.
	*/
	class GameObject
	{
	public:
		GameObject();
		//Creates a gameobject with transfrom, physics and sprite components
		GameObject(glm::vec2 position, graphics::Texture * spriteTexture, glm::vec2 spriteSize, glm::vec2 spriteOrigin);
		~GameObject();

		/**
			Updates components in GameObject.
			Checks if there are components added that need updating and updates them with the relevant info from other components, 
			for example SpriteComponent is updated with info from the TransformComponent.
		*/
		void update();

		/**
			Adds a component to the GameObject.
			Takes a pointer to the component as a parameter.
		*/
		void addComponent(Component* component);

		/**
			Gets a component of given type if one exists within the GameObject.
			Returns a pointer to the found component or a null pointer if component of the given type was not found.
			Example of use: GameObject.getComponent<SpriteComponent>();
		*/
		template<typename T>
		T* getComponent()
		{
			ComponentMap::const_iterator it = _components.find(&typeid(T));
			if (it != _components.end())
				return static_cast<T*>(it->second);
			return nullptr;
		}

		/**
			Removes a component of given type if one exists within the GameObject.
			Example of use: GameObject.removeComponent<SpriteComponent>();
		*/
		template<typename T>
		void removeComponent()
		{
			ComponentMap::const_iterator it = _components.find(&typeid(T));
			if (it != _components.end())
			{
				delete it->second;
				_components.erase(it);
			}
		}
		void setTransform(CoordTransform * tran){ transf = tran; }
		/**
		Moves all components that require moving
		Coordinates are given in user coordinates
		*/
		void move(glm::vec2 moveTo);
		int getId(){ return _id; }
		int setId(int id){ _id = id; }
		bool operator ==(const bool &b)
		{
			if (b == _id)
				return true;
			return false;
		}
		bool operator !=(const bool &b)
		{
			if (b != _id)
				return true;
			return false;
		}

	private:
		using ComponentMap = std::map < const std::type_info*, Component* > ;
		//using ComponentMap = std::unordered_map < const std::type_info*, Component* > ;
		ComponentMap _components;
		CoordTransform * transf;

		int _id;
	};
}