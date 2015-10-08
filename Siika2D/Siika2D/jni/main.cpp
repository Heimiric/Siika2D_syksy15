
#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/misc/GameObject.h"
#include <Box2D/Box2D.h>

core::Siika2D *siika = core::Siika2D::UI();

std::vector<graphics::Sprite*>spriteVector;
graphics::Sprite * sheetSprite;
misc::GameObject go;
std::vector<audio::Audio*>audioVector;
glm::vec2 position;
graphics::Texture * tex, *bg, *sheet;
graphics::Text * teksti;
audio::Audio * scream, *music;
misc::Timer timer;
float pos;
uint blue;
uint green;
float orientation;

//b2World boxWorld(b2Vec2(0.f, -5.f));
b2BodyDef siikaBodyDef;
b2Body* siikaBody;
b2Body* groundBody;

void doStuff()
{
	std::vector<int> keys = siika->_input->getDownKeys();

	for (int i = 0; i < keys.size(); i++)
	{
		s2d_info("%i", keys[i]);
	}


	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		position = siika->_input->touchPosition(i)._positionCurrent;
		scream->play();
	}

	if (timer.getElapsedTime(TIME::SECONDS) > 2)
	{
		sheetSprite->step();
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
		{
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::UP);
			go.getComponent<misc::TransformComponent>()->move(glm::vec2(0, -40));
		}
		if (downKeys[i] == 96)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::DOWN);
		if (downKeys[i] == 97)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::RIGHT);
		if (downKeys[i] == 99)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::LEFT);
		if (downKeys[i] == 107)
			siika->_camera->moveCamera(graphics::CAMERA_MOVEMENT::RESET);

	}

	siika->_boxWorld->Step(1.f/60.f, 6, 2);
	b2Vec2 siikaPos;
	siikaPos = go.getComponent<misc::PhysicsComponent>()->_body->GetPosition();
	//go.update();
	//siika->_boxWorld = &boxWorld;

	//boxWorld.Step(1.f / 60.f, 6, 2);
	//siikaPos = siikaBody->GetPosition();
	//float32 siikaAngle = siikaBody->GetAngle();
	//go.getComponent<misc::TransformComponent>()->setRotation(siikaAngle);

	//siikaPos = go.getComponent<misc::PhysicsComponent>()->_body->GetPosition();
	//go.getComponent<misc::TransformComponent>()->setPosition(glm::vec2(siikaPos.x * 100, -siikaPos.y * 100));
	
	teksti->setColor(graphics::Color(0, green, blue, 255));

	blue += 2;
	if (blue > 254)
		blue = 0;
	if (green > 252)
		green = 0;
	pos = pos + 0.01;
	if (pos > 1.0f)
		pos = -1.0;

	for (int i = 0; i < spriteVector.size(); i++)
		spriteVector[i]->setPosition(glm::vec2(position.x + i * 300, position.y));

	for (int i = 0; i < spriteVector.size(); i++)
	{
		spriteVector[i]->setRotation(orientation);
	}
	if (timer.getElapsedTime(TIME::SECONDS) > 2)
		timer.reset();
	siika->_graphicsContext->clear(); // EBIN XD
	go.update();
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
	sheet = siika->_textureManager->createTexture("testi_tekstuuri.png");

	tex = siika->_textureManager->createTexture("testi_siika.png");

	misc::SpriteComponent* sprtComp = new misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(100, 100), glm::vec2(256, 128), glm::vec2(168, 63), tex, glm::vec2(0, 0), glm::vec2(1.0, 1.0)));
	misc::TransformComponent* transComp = new misc::TransformComponent();
	misc::PhysicsComponent* physicsComp = new misc::PhysicsComponent(glm::vec2(6.4, 0), glm::vec2(2.5, 1.2), 1, 1, 0.5);
	transComp->setPosition(glm::vec2(640, 100));

	go.addComponent(transComp);
	go.addComponent(sprtComp);
	go.addComponent(physicsComp);

	for (int i = 0; i < 4; i++)
	{
		spriteVector.push_back(siika->_spriteManager->createSprite(glm::vec2(100, 100), glm::vec2(256, 128), glm::vec2(168, 63), tex, glm::vec2(0, 0), glm::vec2(1.0, 1.0)));
	}

	sheetSprite = siika->_spriteManager->createSprite(glm::vec2(100, 200), glm::vec2(64, 64), glm::vec2(32, 32), sheet, glm::vec2(0, 0), glm::vec2(0.5, 0.5));

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

	siika->_camera->setSpeed(8);

	siika->_graphicsContext->setClearColor(graphics::Color(38, 178, 170, 255));
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 2.0f, b2Vec2(0.f, -2.f), 0.f);

	groundBody = siika->_boxWorld->CreateBody(&groundBodyDef);
	//groundBody = boxWorld.CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundBox, 0.0f);

	/*/Old physics
	siikaBodyDef.type = b2_dynamicBody;
	siikaBodyDef.position.Set(6.4, 0.f);
	siikaBody = boxWorld.CreateBody(&siikaBodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(2.5f, 1.2f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 1.0f;

	siikaBody->CreateFixture(&fixtureDef);
	*/
	music->play();
}

void siika_main()
{
	doStuff();
}
