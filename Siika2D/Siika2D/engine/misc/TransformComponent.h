#pragma once

#include "Component.h"
#include <glm.hpp>

namespace misc
{
	/**
		Component class for adding transform functionality to GameObject.
	*/
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		~TransformComponent();

		/**
			Move position by adding the vector given as parameter to the current position.
		*/
		void move(glm::vec2 move);

		/**
			Adds given rotation to the current orientation of the transform.
			Takes float as parameter.
		*/
		void rotate(float rotation);

		/**
			Sets the position of the transform.
			Takes glm::vec2 as parameter.
		*/
		void setPosition(glm::vec2 position);

		/**
			Sets the orientation of the transform.
			Takes float as parameter.
		*/
		void setRotation(float angle);

		/**
			Gets the current position of the transform.
			Returns glm::vec2.
		*/
		glm::vec2 getPosition();

		/**
		Gets the current orientation of the transform.
		Returns float.
		*/
		float getRotation();

	private:
		glm::vec2 _position;
		float _rotationAngle;
	};
}