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
//#include "..\core\MemoryManager.h"

namespace core
{

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

	public:


		/**
			Pointter to the UI
		*/
		static Siika2D* UI();

		saved_state* _savedState;	

		/**
			Tells when graphics has been initialized
		*/
		bool drawReady()
		{
			return _drawReady;
		}

		misc::Input *_input;
		graphics::ShaderManager *_shaderManager;
		graphics::SpriteManager *_spriteManager;
		graphics::TextureManager *_textureManager;
		graphics::TextManager *_textManager;
		graphics::GraphicsContext *_graphicsContext;
		graphics::Camera *_camera;
		audio::AudioManager* _audioManager;
		b2World * _boxWorld;
	protected:
		virtual ~Siika2D();
		Siika2D();
		Siika2D(const Siika2D& s2d);
		Siika2D& operator=(const Siika2D& s2d);
		static Siika2D* _instance;

	
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
		bool _drawReady;

		void run(android_app* app);

		/**
			Initializes siika, this should only happen in Siika_main.cpp
		*/
		void initialize(android_app *app);

	};
}
