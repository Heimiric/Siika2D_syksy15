#pragma once
#include <GLES\gl.h>
#include <GLES2\gl2.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>
#include "Shader.h"

namespace graphics
{
	enum CAMERA_MOVEMENT{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Camera
	{
	public:
		void initialize(Shader *shader);
		void moveCamera(CAMERA_MOVEMENT move);
		void setCameraPosition(glm::vec2 _position);
		void useProjection(Shader* shader);

		/**
		Constructor takes vec2 object
		*/
		Camera(glm::vec2 window);
		~Camera();

	private:
		glm::vec2 _displaySize;
		glm::vec2 _origin;
		glm::vec3 _position;
		float rotation;
		glm::mat4 _windowProjection, _viewProjection, _worldProjection;
		GLchar * _windowString = "window";
		GLchar * _viewString = "view";
		GLchar * _worldString = "world";
		GLint _windowLocation, _viewLocation, _worldLocation;
	};
}


