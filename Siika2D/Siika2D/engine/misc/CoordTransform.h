#pragma once
#include "glm.hpp"
#include "Box2D\Box2D.h"
namespace misc
{
	class CoordTransform
	{
		/**
		Class for doing various coordinate transformations between user, device and box2d coordinates.
		*/
	public:
		CoordTransform() :_deviceDimensions(glm::vec2(1280,760)),_userDimensions(glm::vec2(2000,2000)),_pixelsPerMeter(100){};
		CoordTransform(glm::vec2 deviceDimensions, glm::vec2 userDimensions) :_deviceDimensions(deviceDimensions), _userDimensions(_userDimensions),_pixelsPerMeter(100){};
		~CoordTransform(){};
		void setDeviceDimensions(glm::vec2 dimToSet){ _deviceDimensions = dimToSet; }
		void setUserDimensions(glm::vec2 dimToSet){ _userDimensions = dimToSet; }
		void setBox2dRatio(int pixelsToMeter){ _pixelsPerMeter = pixelsToMeter; }
		/**
			Transforms user coordinates to device coordinates
			*/
		//deviceCoordinate = userCoordinate / userDimensions * deviceDimensions
		glm::vec2 userToDevice(glm::vec2 coordToTransform)
		{
			return coordToTransform / _userDimensions * _deviceDimensions;
		}
		/**
			Transforms device coordinates to user coordinates
			*/
		//userCoordinate = deviceCoordinate / deviceDimensions * userDimensions
		glm::vec2 deviceToUser(glm::vec2 coordToTransform)
		{
			return coordToTransform / _deviceDimensions * _userDimensions;
		}

		/**
		Transforms pixels to box2d meters
		*/
		//pixels = pixels/pixelsPerMeter 
		glm::vec2 pixelsToBox2d(glm::vec2 coordToTransform)
		{
			return coordToTransform /= _pixelsPerMeter;
		}
		/**
		Transforms box2d meters to Pixels
		*/
		//pixels = meters * pixelsPerMeter 
		glm::vec2 Box2dToPixels(glm::vec2 coordToTransform)
		{
			return coordToTransform *= _pixelsPerMeter;
		}
		b2Vec2 Box2dToPixels(b2Vec2 coordToTransform)
		{
			return b2Vec2(coordToTransform.x * _pixelsPerMeter, coordToTransform.y * _pixelsPerMeter);
		}
	private:
		glm::vec2 _deviceDimensions;
		glm::vec2 _userDimensions;
		int _pixelsPerMeter;
	};
}