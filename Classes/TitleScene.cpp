#include "TitleScene.h"
#include "GameplayScene.h"

USING_NS_CC;

Title::Title()
{

}

Title::~Title()
{
}

Scene* Title::createScene()
{
    auto scene = Scene::create();
	auto layer = Title::create();
    scene->addChild(layer);

    return scene;
}

bool Title::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	_title = Sprite::create("title.png");
	_title->setAnchorPoint(Vec2(0, 0));
	this->addChild(_title);

	initTouchListener();
    
    return true;
}

void Title::initTouchListener()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event) {
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		_director->replaceScene(Gameplay::createScene("notebook/sample.page"));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}