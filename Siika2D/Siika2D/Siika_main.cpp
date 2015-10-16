#include "engine/core/Siika2D.h"

/**
	Function where the user can initialize what they need before the main loop begins
*/
void extern siika_init();
/**
	Function where the user can update the game when the app is running, aka main loop
*/
void extern siika_main();
/**
	Function where the user can do what they need to do on android pause
*/
void extern siika_onPause();
/**
	Function where the user can do what they need to do on android resume
*/
void extern siika_onResume();

#pragma once
namespace core
{
	class AndroidInterface
	{
	public:
		AndroidInterface(android_app *app)
		{
			_siika = core::Siika2D::UI();
			_siika->initialize(app);
			_state = &_siika->_currentState;
		}
	
		~AndroidInterface()
		{}

		void processAndroidCmds(android_app* app)
		{
			_siika->run(app);
		}

		core::Siika2D *_siika;
		core::SIIKA_STATE* _state;
	};
}

void android_main(android_app* app)
{
	core::AndroidInterface AIF(app);

	bool initDone = false;

	while (!app->destroyRequested)
	{
		if (app->activityState != APP_CMD_STOP && AIF._siika->getFlags().APP_SURFACEREADY == true)
		{
			if (!initDone)
			{
				siika_init();
				initDone = true;
				*AIF._state = core::CLEAR;
			}

			if (AIF._siika->getFlags().APP_RESUME && AIF._siika->getFlags().APP_FOCUS)
				siika_main();

			if (*AIF._state == core::PAUSED)
			{
				siika_onPause();
				*AIF._state = core::CLEAR;
			}
			else if (*AIF._state == core::RESUMED)
			{
				siika_onResume();
				*AIF._state = core::CLEAR;
			}
		}

		AIF.processAndroidCmds(app);
	}
}
	