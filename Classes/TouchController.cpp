#include "Controllers.h"

TouchController::TouchController(cocos2d::Node* node)
: ControllerBase()
{
	auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(TouchController::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(TouchController::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(TouchController::onTouchesEnded, this);

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

TouchController::~TouchController()
{

}

void TouchController::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
}

void TouchController::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{

}

void TouchController::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{

}