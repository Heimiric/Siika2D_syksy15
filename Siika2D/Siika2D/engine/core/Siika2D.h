#pragma once

#include "../../native_app_glue/android_native_app_glue.h" //TODO: includeen projektiin siististi tämän jossain vaiheessa
#include "ResourceManager.h"
#include "../graphics/ShaderManager.h"
#include "../graphics/TextManager.h"
#include "../graphics/TextureManager.h"
#include "../graphics/SpriteManager.h"
#include "../graphics/GraphicsContext.h"
#include "../audio/AudioManager.h"
#include "../graphics/Camera.h"
#include "Box2D\Box2D.h"
#include <android/sensor.h>
#include "../misc/Input.h"
#include "../misc/CoordTransform.h"
//#include "../misc/ColListener.h"
//#include "..\core\MemoryManager.h"

namespace core
{
	/**
		enum for tracking app events
	*/
	enum SIIKA_STATE{
		NOT_SET = -1,
		CLEAR,
		PAUSED,
		RESUMED
	};
	/**
		Struct for tracking the app lifecycle stage
	*/
	struct SIIKA_FLAGS{
		bool APP_RESUME;
		bool APP_FOCUS;
		bool APP_SURFACEREADY;
	};

	struct saved_state {
		float angle;
		int32_t x;
		int32_t y;
	};

	/**
		Singleton User interface used for the engine's subsystems.
		To be used everywhere engine's subsystems are needed
	*/
	class Siika2D
	{
		friend class AndroidInterface;
		friend class SceneManager;
	public:


		/**
			Pointter to the UI
			*/
		static Siika2D* UI();

		saved_state* _savedState;

		/**
			Tells what the stage of the app is
		*/
		const SIIKA_FLAGS getFlags()
		{
			return _siikaFlags;
		}
		b2World* getB2World(){ return _boxWorld; }
		misc::Input *_input;
		graphics::ShaderManager *_shaderManager;
		graphics::SpriteManager *_spriteManager;
		graphics::TextureManager *_textureManager;
		graphics::TextManager *_textManager;
		graphics::GraphicsContext *_graphicsContext;
		graphics::Camera *_camera;
		audio::AudioManager* _audioManager;
		b2World * _boxWorld;
		misc::CoordTransform* transfCrds(){return _coordTransf;}
		std::string * readTxtFile(std::string name);
		/**
		Opens a file for writing user needs to close it with fclose(file)
		*/
		FILE * openFileForWrite(std::string name);
		FILE * openFileForRead(std::string name);
	protected:
		virtual ~Siika2D();
		Siika2D();
		Siika2D(const Siika2D& s2d);
		Siika2D& operator=(const Siika2D& s2d);
		static Siika2D* _instance;

		SIIKA_FLAGS _siikaFlags;
		SIIKA_STATE _currentState;

		misc::CoordTransform * _coordTransf;
	
		graphics::BufferManager *_bufferManager;
		core::ResourceManager _resourceManager;

		android_app *_application;
		//std::vector<int> _appCommandList;

		static void processCommands(android_app* app, int32_t command);

		/**
			Create a Graphics class if ran the first time.
			Else initializes wiped Graphics context to a new display.
		*/
		void initializeGraphics();

		/**
			Creates instance of the Input -class, so that it won't explode
		*/
		void initializeInput();

		void terminateInput();
		/**
			Wipes the graphics context only.
		*/
		void terminateGraphics();
		void terminate();
		
		/**
			Saves the application to the system memory,
			when the user decides to switch away from the application.
		*/
		void saveState(android_app *app);

		/**
			Gets the saved application if there is one.
		*/
		void loadState(android_app *app);

		void run(android_app* app);

		/**
			Initializes siika, this should only happen in Siika_main.cpp
		*/
		void initialize(android_app *app);

	};
}
