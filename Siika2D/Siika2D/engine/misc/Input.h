#pragma once
#include "..\..\native_app_glue\android_native_app_glue.h"
#include "android\sensor.h"
#include "..\core\ErrorHandler.h"
#include <algorithm>
#include <glm.hpp>
#include <gtx\vector_angle.hpp>
#include <vector>
#include <map>



namespace core
{
	class Siika2D;
	class LooperManager;
}

enum SENSOR_ID
{
	ACCELEROMETER = 10,
	GYROSCOPE = 20
}; 


namespace misc
{
	struct Finger
	{

		/**
			Current press location
		*/
		glm::vec2 _positionCurrent = glm::vec2(0.f, 0.f);

		/**
			Location where the last touch event started
		*/
		glm::vec2 _positionStart = glm::vec2(0.f, 0.f);

		/**
			Location where the touch event ended
		*/
		glm::vec2 _positionEnd = glm::vec2(0.f, 0.f);

	};

	struct Stick
	{
		glm::vec2 _pointingVector = glm::vec2(0.f, 0.f);
		float _rotation = 0;
	};


	/**
		Singleton class that handles all the input coming from the device
							Used from Siika2D-class
	*/
	class Input
	{

	friend class core::Siika2D;

	public:

		static Input* getInstance(android_app *app);
		virtual ~Input();

		/**
			Sets the sensor active
		*/
		void enableSensor(SENSOR_ID sensorId);

		/**
			Sets the approx. tickrate/second for the accelerometer
		*/
		void setTickRate(float ticksPerSecond, SENSOR_ID sensorId);

		/**
			Stops accelerometer processing
		*/
		void accelerometerDisable();

		std::vector<int> getDownKeys()
		{
			return _keysDown;
		}
		/**
			Is the screen being pressed?
		*/
		int touchPositionsActive()
		{
			return _fingersDown;
		}

		int sticksActive()
		{
			return _sticksActive;
		}

		Finger touchPosition(int finger)
		{
			return _fingers[finger];
		}

		Stick stick(int stick)
		{
			return _sticks[stick];
		}

		ASensorVector* sensorData(SENSOR_ID sensor)
		{
			if (sensor == ACCELEROMETER)
				return _accelerometerData;
			else if (sensor == GYROSCOPE)
				return _gyroscopeData;
		}
		glm::vec2 getReleaseVec(void)
		{

			return _releaseVec;
			_fingerUp = false;
		}
		bool _fingerUp;
	protected:

		/**
			Given sensor's data
		*/
		void processSensor(SENSOR_ID sensor);

		void updateSensor(SENSOR_ID sensor);

		//void processGyroscope();

		void initializeGyroscope(android_app *app);

		void initializeSensor(android_app *app, SENSOR_ID sensorId);
		/**
			Sets processInput to read Android -device's input-data
		*/
		void initializeInput(android_app *app);
		/**
			Processes the device's latest data
		*/
		static int processInput(android_app *app, AInputEvent *event);
		/**
			Processes key-input
		*/
		void processKey(AInputEvent *event);
		/**
			Processes motion-input
		*/
		void processMotion(AInputEvent *event, int source);

		void processTouchscreen(AInputEvent *event);

		void processStickOrDpad(AInputEvent *event);


		Input(android_app* app);
		Input(const Input& input);
		Input& operator=(const Input& input);
		static Input* _instance;


		/**
			Is the screen being pressed
		*/
		bool _touchingScreen = false;

		/**
			Analog keys currently pressed
		*/
		std::vector<int>_keysDown;

		std::map<SENSOR_ID, float>_tickRates;

		Finger _fingers[8];
		Stick _sticks[4];

		int _fingersDown = 0;
		int _sticksActive = 0;

		bool _accelerometerEnabled = false;

		android_app *_app;

		ASensorEventQueue* _sensorEventQueue;
		ASensorManager* _sensorManager;
		const ASensor* _accelerometerSensor;
		const ASensor* _gyroscopeSensor;
		ASensorVector *_accelerometerData;
		ASensorVector *_gyroscopeData;
		glm::vec2 _releaseVec;
	
	};

}