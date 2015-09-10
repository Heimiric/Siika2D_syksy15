
#include "..\engine\core\Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/core/MemoryManager.h"
core::Siika2D *siika = core::Siika2D::UI();

bool stuffDone = false;
std::vector<graphics::Sprite*>spriteVector;
std::vector<audio::Audio*>audioVector;
glm::vec2 position;
graphics::Texture * tex;
graphics::Text * teksti;
audio::Audio * scream;
misc::Timer timer;
float pos = 0;
uint blue = 1;
uint green = 128;
float orientation;
void doStuff()
{
	if(!stuffDone)
	{
		timer.start();
		tex = siika->_textureManager->createTexture("tekstuuri.png");
		siika->_shaderManager->useDefaultShader(true, true);
		//siika->_shaderManager->useShader(true, true);
		for (int i = 0; i < 50; i++)
		{
			spriteVector.push_back(siika->_spriteManager->createSprite(glm::vec2(100, 100), glm::vec2(64, 64), glm::vec2(32,32), tex, glm::vec2(0, 0), glm::vec2(1.0, 1.0)));
		}
		scream = siika->_audioManager->createAudio("wilhelm_scream.ogg");
		scream->setMaxPlayerCount(10);
		teksti = siika->_textManager->createText();
		teksti->setFont("arial.ttf");
		teksti->setText("hello siika");
		teksti->setPosition(0, 0.5);
		teksti->setFontSize(72);
		stuffDone = true;
	}
	
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
		if(orientation > 0)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::UP);
		else
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::DOWN);

	}
	
	green += 2;
	for (int i = 0; i < spriteVector.size(); i++)
		spriteVector[i]->setColor(graphics::Color(0, green-i*10, blue-i*10, 255));


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
		spriteVector[i]->setPosition(glm::vec2(position.x+i, position.y+i*2));

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

void siika_main()
{
	doStuff();

}
