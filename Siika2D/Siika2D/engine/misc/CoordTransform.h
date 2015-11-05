#pragma once
#include "glm.hpp"
#include "Box2D\Box2D.h"
namespace misc
{
	class CoordTransform
	{
		/**
		Class for doing various coordinate transformations between user, device and box2d coordinates.
		Preinitialized instance can be accessed from core::Siika2D::UI()->->transfCrds()
		Its loaded with devices reported screen dimensions and default values.

		Default values are:
		deviceDimensions: Devices reported dimensions on application load
		
		userDimensions: 2000x2000
		This is arbitary user coordinate system the purpose of this is to have the game work the same on any device regardless of screen resolution and aspect ratio
		It will lead to stretcing of graphics on devices with different aspect ratios.

		pixelsPerMeter: 100
		This means that with default settings the screen is 20x20 meters in size
		Both this and the size of userdimensions affect physics calculations
		*/
	public:

		/**
		Empty contructor will use the following values: deviceDimensions 1280x760, userDimensions 2000x2000, pixelsPerMeter 100
		*/
		CoordTransform() :_deviceDimensions(glm::vec2(1280,760)),_userDimensions(glm::vec2(2000,2000)),_pixelsPerMeter(100){};
		CoordTransform(glm::vec2 deviceDimensions, glm::vec2 userDimensions, int pixelsPerMeter) :_deviceDimensions(deviceDimensions), _userDimensions(userDimensions), _pixelsPerMeter(pixelsPerMeter){};
		~CoordTransform(){};
		/**
			setsDevice dimensions this is automaticly set once the application loads to the devices current dimensions
			might need to be updated if the user rotates the device if game reorientation is needed
		*/
		void setDeviceDimensions(glm::vec2 dimToSet){ _deviceDimensions = dimToSet; }
		/**
			setsUserDimensions how many units is the screen
		*/
		void setUserDimensions(glm::vec2 dimToSet){ _userDimensions = dimToSet; }
		/**
			sets the ratio of userdimensions to box2d meters with default values of 2000x2000 and 100 the screen is 20x20 meters in size
			This affects all physics calculations
		*/
		void setBox2dRatio(int pixelsToMeter){ _pixelsPerMeter = pixelsToMeter; }
		/**
			Transforms user coordinates to device coordinates
		*/
		//deviceCoordinate = userCoordinate / userDimensions * deviceDimensions
		glm::vec2 userToDevice(glm::vec2 coordToTransform)
		{
			glm::vec2 transf = coordToTransform / _userDimensions;
			return  transf * _deviceDimensions;
		}
		/**
			Transforms device coordinates to user coordinates
		*/
		//userCoordinate = deviceCoordinate / deviceDimensions * userDimensions
		glm::vec2 deviceToUser(glm::vec2 coordToTransform)
		{
			glm::vec2 transf = coordToTransform / _deviceDimensions;
			return  transf * _userDimensions;
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
			return glm::vec2(coordToTransform.x * (float)_pixelsPerMeter, coordToTransform.y * (float)_pixelsPerMeter);
		}
		b2Vec2 Box2dToPixels(b2Vec2 coordToTransform)
		{
			return b2Vec2(coordToTransform.x * (float)_pixelsPerMeter, coordToTransform.y * (float)_pixelsPerMeter);
		}
		/**
			Transforms userCoordinates to device and then to Box2d
			This will affect physics in devices with different screen resolution.
			If you do not want this pixelsToBox2d(userCoordinates) should be used instead
		*/
		glm::vec2 userToDToBox2d(glm::vec2 coordToTransform)
		{
			glm::vec2 givenInMeters(coordToTransform.x / _pixelsPerMeter, coordToTransform.y / _pixelsPerMeter);
			return userToDevice(coordToTransform) * givenInMeters / coordToTransform;
		}
		/**
			Transforms to Box2d to user coordinates and then to device coordinates
			This must be done if physics calculations are to be done in usercoordinates
			so that physics will not be dependant on device screen size
		*/
		glm::vec2 box2dToUToDevice(glm::vec2 coordToTransform)
		{
			glm::vec2 retVal = Box2dToPixels(coordToTransform); //In pixels | User
			retVal = userToDevice(coordToTransform); // In device
			//retVal = deviceToUser(coordToTransform);
			return glm::vec2(retVal.x * (float)_pixelsPerMeter, retVal.y * (float)_pixelsPerMeter);
		}
		
	private:
		//How many meters total in usedimensions
		glm::vec2 metersInUser(){return glm::vec2(_userDimensions.x / _pixelsPerMeter, _userDimensions.y / _pixelsPerMeter);}
		glm::vec2 _deviceDimensions;
		glm::vec2 _userDimensions;
		int _pixelsPerMeter;
	};
}