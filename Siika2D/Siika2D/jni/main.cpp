
#include "..\engine\core\Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/core/MemoryManager.h"
core::Siika2D *siika = core::Siika2D::UI();

std::vector<graphics::Sprite*>spriteVector;
std::vector<audio::Audio*>audioVector;
glm::vec2 position;
graphics::Texture * tex, *bg;
graphics::Text * teksti;
audio::Audio * scream, *music;
misc::Timer timer;
float pos;
uint blue;
uint green;
float orientation;

void doStuff()
{	
	std::vector<int> keys = siika->_input->getDownKeys();
	
	for (int i = 0; i < keys.size(); i++)
	{
		s2d_info("%i",keys[i]);
	}

	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		position = siika->_input->touchPosition(i)._positionCurrent;
		scream->play();
	}

	for (int i = 0; i < siika->_input->sticksActive(); i++)
	{
		orientation = siika->_input->stick(i)._rotation;
	}
	
	green += 2;

	std::vector<GLint> downKeys = siika->_input->getDownKeys();
	for (int i = 0; i < downKeys.size(); i++)
	{
		if (downKeys[i] == 100)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::UP);
		if (downKeys[i] == 96)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::DOWN);
		if (downKeys[i] == 97)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::RIGHT);
		if (downKeys[i] == 99)
				siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::LEFT);
		if (downKeys[i] == 107)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::RESET);

	}
	teksti->setColor(graphics::Color(0, green, blue, 255));

	blue += 2;
	if(blue > 254)
		blue = 0;
	if(green > 252)
		green = 0;
	pos = pos + 0.01;
	if(pos > 1.0f)
		pos = -1.0;

	for (int i = 0; i < spriteVector.size();i++)
		spriteVector[i]->setPosition(glm::vec2(position.x+i*300, position.y));

	for (int i = 0; i < spriteVector.size(); i++)
	{
		spriteVector[i]->setRotation(orientation);
		if (timer.getElapsedTime(TIME::SECONDS) > 2)
		{
			spriteVector[i]->step();
			
		}
	}
	if (timer.getElapsedTime(TIME::SECONDS) > 2)
		timer.reset();
	siika->_graphicsContext->clear(); // EBIN XD
	siika->_spriteManager->drawSprites();
	siika->_textManager->drawTexts();
	siika->_graphicsContext->swap();
	//core::MemoryManager::getInstance().getCount();
}

void siika_init()
{
	timer.start();
	
	bg = siika->_textureManager->createTexture("testi_Siika2D_background.png");

	siika->_spriteManager->createSprite(glm::vec2(640, 360), glm::vec2(1280, 720), glm::vec2(640, 360), bg, glm::vec2(0, 0), glm::vec2(1.0, 1.0));

	tex = siika->_textureManager->createTexture("testi_siika.png");
	for (int i = 0; i < 4; i++)
	{
		spriteVector.push_back(siika->_spriteManager->createSprite(glm::vec2(100, 100), glm::vec2(256, 128), glm::vec2(168, 63), tex, glm::vec2(0, 0), glm::vec2(1.0, 1.0)));
	}

	scream = siika->_audioManager->createAudio("wilhelm_scream.ogg");
	scream->setMaxPlayerCount(10);
	music = siika->_audioManager->createAudio("siika.ogg");
	music->setLooping(true);
	teksti = siika->_textManager->createText();
	teksti->setFont("arial.ttf");
	teksti->setText("SIIKA2D");
	teksti->setPosition(-1.0, 0.75);
	teksti->setFontSize(128);

	pos = 0;
	blue = 1;
	green = 128;

	siika->_camera->setSpeed(4);

	siika->_graphicsContext->setClearColor(graphics::Color(38, 178, 170, 255));
	music->play();
}

void siika_main()
{
	doStuff();
}
