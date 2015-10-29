
#include "../engine/core/Siika2D.h"
#include "../engine/audio/Audio.h"
#include "../engine/misc/timer.h"
#include "../engine/misc/GameObject.h"
#include <Box2D/Box2D.h>
//Handle to siika2d userinterface
core::Siika2D *siika = core::Siika2D::UI();
std::vector<graphics::Sprite*>spriteVector;
graphics::Sprite * sheetSprite;
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
bool moved = false;
//Definitions for projectile creation and update functions
void createProjectile(glm::vec2 flightVector, glm::vec2 startPos);
void updateProjectiles();
//Demostration gameobjects
misc::GameObject go;
misc::GameObject *groundGo;
std::vector<misc::GameObject*> projectiles;
//Pointer to coordinate transformation class
misc::CoordTransform * trnsf;
//Enum used to identify game object types
enum objs{ whitefish, ground, bullet };
//Creates and initialises collision listener
colListener collisionListener;

//These are called when program goes to pause and resums
//Can be used for example pausing music and soudeffects
void siika_onPause(){};
void siika_onResume(){};
void doStuff()
{
	//Gets the keys that are held down on the device and prints their id's to logcat
	std::vector<int> keys = siika->_input->getDownKeys();
	for (int i = 0; i < keys.size(); i++)
	{
		s2d_info("%i", keys[i]);
	}


	//Gets all positions where user is holding finger down on the touchscreen
	for (int i = 0; i < siika->_input->touchPositionsActive(); i++)
	{
		position = siika->_input->touchPosition(i)._positionCurrent + siika->_camera->getPosition();
		//Plays sound when user touches screen
		scream->play();
	}
	//Gets swipe vector from screen once finger is no longer touching
	if (siika->_input->fingerUp())
	{
		//Gets the position of the go gameobject
		glm::vec2 sPosition = go.getComponent<misc::TransformComponent>()->getPosition();
		//Transforms the position to user coordinates and passes it to projectile creation function
		createProjectile(siika->_input->getReleaseVec(), trnsf->deviceToUser(sPosition));
	}

	//Changes the sheet sprite for a sprite every 2 seconds
	if (timer.getElapsedTime(TIME::SECONDS) > 2)
	{
		sheetSprite->step();
	}
	//Gets all the sticks that are active on the device
	for (int i = 0; i < siika->_input->sticksActive(); i++)
	{
		orientation = siika->_input->stick(i)._rotation;
	}

	//Gets all collisions for the given gameobject
	//prints "Tormays" into logcat for each collision and sets a force pushing the object
	std::vector<misc::GameObject*> *cols = nullptr;
	if (cols = collisionListener.getCollisionsFor(&go))
	{
		if (!cols->empty())
		{
			//go.getComponent<misc::PhysicsComponent>()->applyForce(glm::vec2(100, 30));
			cols->clear();
			s2d_info("Tormays");
		}
	}
	//Gets the position of the go gameobject (in device coordinates)
	glm::vec2 goPosition = go.getComponent<misc::TransformComponent>()->getPosition();
	//Sets camera center position to the go gameobjects position, 
	siika->_camera->setCameraPosition(goPosition - glm::vec2(640, 360));

	//Gets keys that are held down on the device and moves the camera when certain keys are pressed
	//Works on shield ids are for Y,X,B and A keys
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
	//Steps the physics world in Box2D
	//After this calling GameObject->update() will update physics for the game objects
	siika->_boxWorld->Step(1.f / 60.f, 6, 2);

	//purpose is to move ground with the gameobject: still incomplete
	if ((((int)goPosition.x % 1280) < 100))
	{
		if (!moved)
		{
			moved = true;
			//groundObj.getComponent<misc::TransformComponent>()->setPosition(glm::vec2(goPosition.x, -700));
			//groundGo->getComponent<misc::PhysicsComponent>()->setPosition(glm::vec2(goPosition.x / 100, -7.f));
			//GameObjecdt.move updates all existing components
			//groundGo->move(trnsf->deviceToUser(glm::vec2(goPosition.x, 700)));
		}
	}
	else
		moved = false;

	//Demostrates the use of coordinate conversion class
	//Gets the coordinate from gameobjects physicscomponent and then transfroms it to usercoordinates
	b2Vec2 siikaPos;
	siikaPos = go.getComponent<misc::PhysicsComponent>()->_body->GetPosition();
	glm::vec2 positionInPixels = trnsf->Box2dToPixels(glm::vec2(siikaPos.x, siikaPos.y));

	//Sets the color for the text
	teksti->setColor(graphics::Color(0, green, blue, 255));
	blue += 2;
	green += 2;
	if (blue > 254)
		blue = 0;
	if (green > 252)
		green = 0;
	pos = pos + 0.01;
	if (pos > 1.0f)
		pos = -1.0;

	//Moves the sprites to a line
	for (int i = 0; i < spriteVector.size(); i++)
		spriteVector[i]->setPosition(glm::vec2(position.x + i * 300, position.y));
	//Sets sprite rotation, gets rotatoin from sticks (float orientation)
	for (int i = 0; i < spriteVector.size(); i++)
	{
		spriteVector[i]->setRotation(orientation);
	}
	//resets timer
	if (timer.getElapsedTime(TIME::SECONDS) > 2)
		timer.reset();
	//Clears graphicsContext must be called before draw
	siika->_graphicsContext->clear();
	//Updates gameobjects this updates all componets including physics (box2d)
	go.update();
	groundGo->update();
	updateProjectiles();
	//Draws sprites
	siika->_spriteManager->drawSprites();
	//Draws texts
	siika->_textManager->drawTexts();
	//Swap buffers must be called after draws are done
	siika->_graphicsContext->swap();
}

void siika_init()
{
	//Gets a pointer to the pre-initialized coordinate transformation class
	trnsf = siika->transfCrds();
	//Sets collision listener to be used
	siika->_boxWorld->SetContactListener(&collisionListener);
	timer.start();
	//Creates the background picture (sprite)
	bg = siika->_textureManager->createTexture("testi_Siika2D_background.png");
	siika->_spriteManager->createSprite(glm::vec2(640, 360), glm::vec2(1280, 720), glm::vec2(640, 360), bg, glm::vec2(0, 0), glm::vec2(1.0, 1.0));
	//Created before transform class in siika core is initialized, need to pass it here
	go.setTransform(trnsf);
	//Gets the texture for gameobject go
	tex = siika->_textureManager->createTexture("testi_siika.png");
	//Creates and sets all components to gameobject go
	misc::SpriteComponent* sprtComp = new misc::SpriteComponent(siika->_spriteManager->createSprite(glm::vec2(640, 100), glm::vec2(256, 128), glm::vec2(168, 63), tex, glm::vec2(0, 0), glm::vec2(1.0, 1.0)));
	misc::TransformComponent* transComp = new misc::TransformComponent();
//	misc::PhysicsComponent* physicsComp = new misc::PhysicsComponent(glm::vec2(6.4, 0), glm::vec2(0.64, 0.36), 1, 1, 0.5);
	misc::PhysicsComponent* physicsComp = new misc::PhysicsComponent(glm::vec2(10, 10), glm::vec2(0.64, 0.36), 1, 1, 0.5);

	transComp->setPosition(glm::vec2(640, 100));
	go.addComponent(transComp);
	go.addComponent(sprtComp);
	go.addComponent(physicsComp);
	go.move(glm::vec2(1000, 1000));
	go.setId(whitefish);

	//Creates groundtexture
	graphics::Texture * gTex = siika->_textureManager->createTexture("groundtx.png");
	//Creates ground gameobject and set all components
	//Constuctor used here creates transfrom, sprite and physics components and sets them
	//Coordinantes and sizes given must be in usercoordinates these can be changed in siika->transfCrds()
	//All Components created this way can still be accessed with GameObject.getComponent<misc::componentType>()
	groundGo = new misc::GameObject(glm::vec2(0, 640), gTex, glm::vec2(2000, 100), glm::vec2(0, 0));
	groundGo->setId(ground);
	//Gets the physics component of the gameobject and sets its gravityscale to 0 (Is not affected by gravity)
	groundGo->getComponent<misc::PhysicsComponent>()->setGravityScale(0);

	//Creates 4 sprites
	for (int i = 0; i < 4; i++)
	{
		spriteVector.push_back(siika->_spriteManager->createSprite(glm::vec2(100, 100), glm::vec2(256, 128), glm::vec2(168, 63), tex, glm::vec2(0, 0), glm::vec2(1.0, 1.0)));
	}
	//Creates a sprite that uses spritesheets
	sheet = siika->_textureManager->createTexture("testi_tekstuuri.png");
	//Texture coordinates are given as 0.5 0.5 this means that the sheet is 2x2 in size
	sheetSprite = siika->_spriteManager->createSprite(glm::vec2(100, 200), glm::vec2(64, 64), glm::vec2(32, 32), sheet, glm::vec2(0, 0), glm::vec2(0.5, 0.5));

	//Creates effect audio and sets it to 10 simultaneous plays
	scream = siika->_audioManager->createAudio("wilhelm_scream.ogg");
	scream->setMaxPlayerCount(10);
	//Creates a background audio sets it to loop and to play
	music = siika->_audioManager->createAudio("siika.ogg");
	music->setLooping(true);
	music->play();

	//Creates text, sets the font and text string
	teksti = siika->_textManager->createText();
	teksti->setFont("arial.ttf");
	teksti->setText("SIIKA2D");
	teksti->setPosition(-1.0, 0.75);
	teksti->setFontSize(128);

	pos = 0;
	blue = 1;
	green = 128;

	//Sets the move speed for camera when calling camera->moveCamera();
	siika->_camera->setSpeed(8);
	//Sets the background color for the screen
	siika->_graphicsContext->setClearColor(graphics::Color(38, 178, 170, 255));
}

void siika_main()
{
	doStuff();
}

void createProjectile(glm::vec2 flightVector, glm::vec2 startPos)
{
	startPos.y = -startPos.y;
	//Uses wrong coordinates will be updated later
	misc::GameObject * sbullet = new misc::GameObject(startPos, sheet, glm::vec2(64, 64), glm::vec2(32, 32));
	projectiles.push_back(sbullet);
	misc::GameObject * newProj = projectiles[projectiles.size() - 1];
	/*projectiles.push_back(new misc::GameObject());
	misc::SpriteComponent* projsprtComp = new misc::SpriteComponent(siika->_spriteManager->createSprite(startPos, glm::vec2(64, 64), glm::vec2(32, 32), sheet, glm::vec2(0, 0), glm::vec2(0.5, 0.5)));
	misc::TransformComponent* projtransComp = new misc::TransformComponent();
	misc::PhysicsComponent* projphysicsComp = new misc::PhysicsComponent(0.01f*startPos, glm::vec2(0.64, 0.64), 1, 1, 0.5);
	projtransComp->setPosition(startPos);
	

	//projsprtComp->setZ(10);

	newProj->addComponent(projtransComp);
	newProj->addComponent(projsprtComp);
	newProj->addComponent(projphysicsComp);
	*/
	newProj->move(startPos);
	newProj->getComponent<misc::SpriteComponent>()->setZ(10);
	newProj->getComponent<misc::PhysicsComponent>()->applyForce(flightVector);
	newProj->setId(bullet);
}
void updateProjectiles()
{

	std::vector<misc::GameObject*> *pVec;
	for (misc::GameObject * proj : projectiles)
	{

		if (pVec = collisionListener.getCollisionsFor(proj))
		{
			for (misc::GameObject * p : *pVec)
			{
				if (p->getId() == bullet)
				{
					//Need to do proper clear for colliding objects and for objects too far out
					//delete p;
					scream->play();
				}
			}

		}
		proj->update();
	}
}