#include "Camera.h"
using namespace graphics;

Camera::Camera(glm::vec2 window)
{
	_displaySize = window;
	_position = glm::vec3(0, 0, -3);
}

Camera::~Camera()
{

}

void Camera::initialize(Shader* shader)
{

	GLint error;
	error = glGetError();
	s2d_assert(error == 0);
	/**
		Initialize window projection matrix
	*/
	shader->use();
	_windowProjection = glm::ortho(0.0f, _displaySize.x, _displaySize.y, 0.0f, -1.0f, 1.0f);

	_windowLocation = shader->_windowLocation;
	error = glGetError();
	s2d_assert(error == 0);


	/**
		Pass to shaders
	*/
	glUniformMatrix4fv(_windowLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&_windowProjection));
	 
	/**
		Initialize view projection matrix 
	*/

	//_viewProjection = glm::translate(glm::vec3(0,0,-5));
	
	/*glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
								  glm::vec3(0.0f, 0.0f, 10.0f),
								  glm::vec3(0.0f, 1.0f, 0.0f));
	*/
	//_viewLocation = glGetUniformLocation(shader->getProgram(), _viewString);

	//glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&_viewProjection));

	/**
	world translation
	*/
	/*_worldProjection = glm::translate(_worldProjection,glm::vec3(1,1,1));

	_worldLocation = glGetUniformLocation(shader->getProgram(), _worldString);

	glUniformMatrix4fv(_worldLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&_worldProjection));*/

	shader->use(false);
}

void Camera::moveCamera(CAMERA_MOVEMENT move)
{
	switch (move)
	{
	case UP:

		break;
	
	case DOWN:

		break;
		
	case LEFT:

		break;

	case RIGHT:

		break;
	}
}

void Camera::setCameraPosition(glm::vec2 _position)
{

}

void Camera::useProjection(Shader *shader)
{
	shader->use();
	GLint err = glGetError();
	_windowProjection = glm::ortho(0.0f, _displaySize.x, _displaySize.y, 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(shader->_windowLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&_windowProjection));
	err = glGetError();
	int i = 0;
}


