#include "GameplayScene.h"
#include "Notebook.h"
#include "Controllers.h"
#include "Player.h"
#include "Gates.h"
#include "Switch.h"

USING_NS_CC;

Gameplay::Gameplay()
{

}

Gameplay::Gameplay(const char* filename)
: Gameplay()
{
	initWithFile(filename);
	initUseKeyListener();

	scheduleUpdate();
}

Gameplay::~Gameplay()
{

}

void Gameplay::update(float dt)
{
	Rect noteBox = _notebook->getBoundingBox();
	Rect playerBox = _player->getBoundingBox();
	Rect limitBox = Rect(playerBox.size.width * 0.5, 0,
		noteBox.size.width - playerBox.size.width * 0.5, 0);

	if (_player->getPositionX() < limitBox.origin.x)
		_player->setPositionX(limitBox.origin.x);
	else if (_player->getPositionX() > limitBox.size.width)
		_player->setPositionX(limitBox.size.width);
}

Scene* Gameplay::createScene(const char* filename)
{
	Scene* scene = Scene::create();
	Gameplay* gameplay = new Gameplay(filename);
	scene->addChild(gameplay);

	return scene;
}

bool Gameplay::initWithFile(const char* filename)
{
	cocos2d::Color4B bgColor = cocos2d::Color4B(255, 255, 232, 255);
	if (!LayerColor::initWithColor(bgColor))
		return false;

	initNotebook(filename);
	initControllers();

	_keyController->setControlTarget(_player);

	return true;
}

void Gameplay::initNotebook(const char* filename)
{
	_notebook = new Notebook();
	_notebook->loadPage(filename);
	_notebook->setAnchorPoint(Vec2(0.5, 0.5));
	_player = _notebook->getPlayer();

	Size center = this->getContentSize() * 0.5;
	_notebook->setPositionX(center.width);
	_notebook->setPositionY(center.height);
	this->addChild(_notebook);
}

void Gameplay::initControllers()
{
	_keyController = new KeyController(this);
	_keyController->setSpeedXY(Vec2(5, 5));
	this->addChild(_keyController);
}

void Gameplay::initUseKeyListener()
{
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
			useUsableObject();
	};

	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = [&](Touch* touch, Event* event) {
		useUsableObject();
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);
}

void Gameplay::useUsableObject()
{
	Gate* usableGate = _notebook->getUsableGate();
	Switch* usableSwitch = _notebook->getUsableSwitch();

	if (usableGate != nullptr)
	{
		Gate* linkedGate = usableGate->getLinkedGate();
		_player->setPositionY(linkedGate->getPositionY());
		_player->setLine(linkedGate->getLine());
	}

	if (usableSwitch != nullptr)
	{
		std::vector<Wall*> linkedWalls = usableSwitch->getLinkedWalls();
		for (Wall* wall : linkedWalls)
		{
			wall->setVisible(!wall->isVisible());
		}
	}
}