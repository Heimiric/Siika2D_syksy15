#include "engine/core/Siika2D.h"
#include "engine/misc/Input.h"
#include "engine/graphics/Buffer.h"

void extern siika_main();
void extern siika_init();

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
		}
	
		~AndroidInterface()
		{}

		void processAndroidCmds(android_app* app)
		{
			_siika->run(app);
		}

		core::Siika2D *_siika;
		
	};
}

void android_main(android_app* app)
{
	core::AndroidInterface AIF(app);

	bool initDone = false;

	while (!app->destroyRequested)
	{
		if (app->activityState != APP_CMD_STOP && AIF._siika->drawReady() == true)
		{
			if (!initDone)
			{
				siika_init();
				initDone = true;
			}

			siika_main();
		}


		AIF.processAndroidCmds(app);
	}
}
	