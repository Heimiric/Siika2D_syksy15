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

void Camera::moveCamera(CAMERA_MOVEMENT move)
{
	switch (move)
	{
	case UP:
		_position.y += -_step;
		break;
	
	case DOWN:
		_position.y += _step;
		break;
		
	case LEFT:
		_position.x += _step;
		break;

	case RIGHT:
		_position.x += -_step;
		break;
	case RESET:
		_position.x = 0;
		_position.y = 0;
		break;
	default:
		break;
	}
}

void Camera::setCameraPosition(glm::vec2 position)
{
	_position.x = position.x;
	_position.y = position.y;
}

void Camera::useProjection(GLint windowLocation)
{
	_windowProjection = glm::ortho(0.0f + _position.x, _displaySize.x + _position.x, _displaySize.y + _position.y, 0.0f + _position.y, -1.0f, 1.0f);
	glUniformMatrix4fv(windowLocation, 1, GL_FALSE, reinterpret_cast<const float*>(&_windowProjection));
}


