#include "Siika2D.h"

using namespace core;

Siika2D* Siika2D::_instance = nullptr;


Siika2D* Siika2D::UI()
{

	if (_instance == nullptr)
	{
		_instance = new Siika2D();
	}
	return _instance;

}


Siika2D::Siika2D()
{
	s2d_info("SIIKA CREATED");
	_input = nullptr;
}

Siika2D::~Siika2D()
{
	//TODO: Release resources

	s2d_info("SIIKA DESTROYED");
	_application = nullptr;
	_instance = nullptr;
	delete _graphicsContext;
	delete _textManager;
	delete _spriteManager;
	delete _textureManager;
	delete _shaderManager;
	delete _textManager;
	delete _audioManager;
}

void Siika2D::initialize(android_app* app)
{
	_drawReady = false;
	app->userData = this;
	app->onAppCmd = this->processCommands;
	_application = app;

	//Loading saved state if there is one
	//getLatestState(app);
	loadState(app);
	_resourceManager.init(_application->activity->assetManager);
}

void Siika2D::terminate()
{
	//delete this;
}

void Siika2D::initializeGraphics()
{
	_graphicsContext = new graphics::GraphicsContext(_application);
	_camera = new graphics::Camera(_graphicsContext->getDisplaySize());
	_shaderManager = new graphics::ShaderManager(&_resourceManager, _graphicsContext->getDisplaySize(),_camera);
	_bufferManager = new graphics::BufferManager();
	_textureManager = new graphics::TextureManager(&_resourceManager);
	_spriteManager = new graphics::SpriteManager(_shaderManager,_bufferManager);
	_textManager = new graphics::TextManager(&_resourceManager, _shaderManager, _graphicsContext->getDisplaySize());
	_audioManager = new audio::AudioManager(&_resourceManager);
	_shaderManager->useShader(true, true);

	_drawReady = true;
}

void Siika2D::initializeInput()
{
	if (_input == nullptr)
		_input = _input->getInstance(_application);
}

void Siika2D::terminateInput()
{
	if (_input->_accelerometerEnabled)
	{
		_input->accelerometerDisable();
	}
}
void Siika2D::terminateGraphics()
{
	_graphicsContext->wipeContext();
	_drawReady = false;
}
void Siika2D::saveState(android_app* app)
{	
	//Creating state to restore from
	//malloc is recommended by native_app_glue
	_savedState = (saved_state*)app->userData;
	app->savedState = malloc(sizeof(_savedState));
	*((saved_state*)app->savedState) = *_savedState;
	app->savedStateSize = sizeof(_savedState);
}

void Siika2D::loadState(android_app* app)
{
	if (app->savedState != nullptr)
		_savedState = (struct saved_state*)app->savedState;
}

void Siika2D::processCommands(android_app* app,int32_t command)
{
	//Getting latest state
	_instance = (Siika2D*)app->userData;

	std::string cmdString = "APP_CMD_";

	switch (command)
	{
	case APP_CMD_START:
		cmdString += "START";
		s2d_info(cmdString.c_str());
		//Application started,
		//initialize siika (get saved_state)
		_instance->initialize(app);
		break;

	case APP_CMD_DESTROY:
		cmdString += "DESTROY";
		s2d_info(cmdString.c_str());
		//delete _instance;
		break;

	case APP_CMD_SAVE_STATE:
		cmdString += "SAVE_STATE";
		s2d_info(cmdString.c_str());
		_instance->saveState(app);
		break;

	case APP_CMD_INIT_WINDOW:
		cmdString += "INIT_WINDOW";
		s2d_info(cmdString.c_str());
		_instance->initializeGraphics();
		break;

	case APP_CMD_GAINED_FOCUS:
		cmdString += "GAINED_FOCUS";
		s2d_info(cmdString.c_str());
		_instance->initializeInput();
		break;

	case APP_CMD_LOST_FOCUS:
		cmdString += "LOST_FOCUS";
		s2d_info(cmdString.c_str());
		//_instance->terminateInput();
		break;

	case APP_CMD_TERM_WINDOW:
		cmdString += "TERM_WINDOW";
		s2d_info(cmdString.c_str());
		_instance->terminateGraphics();
		break;

	case APP_CMD_LOW_MEMORY:
		cmdString += "LOW_MEMORY";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_PAUSE:
		cmdString += "PAUSE";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_STOP:
		cmdString += "STOP";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_CONFIG_CHANGED:
		cmdString += "CONFIG_CHANGED";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_RESUME:
		cmdString += "RESUME";
		s2d_info(cmdString.c_str());
		break;

	case APP_CMD_WINDOW_REDRAW_NEEDED:
		cmdString += "REDRAW_NEEDED";
		s2d_info(cmdString.c_str());
		break;
	}
}

void Siika2D::run(android_app* app)
{
	int id;
	int events;
	android_poll_source* _source;

	while ((id = ALooper_pollAll(0, nullptr, &events, (void**)&_source)) >= 0)
	{
		if (_input != nullptr)
		{
			_input->processSensor(SENSOR_ID(id));
		}

		if (_source != NULL)
		{
			_source->process(app, _source);
		}
	}
}