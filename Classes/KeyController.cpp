#include "Controllers.h"

KeyController::KeyController(cocos2d::Node* node)
: ControllerBase()
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(KeyController::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(KeyController::onKeyReleased, this);

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

KeyController::~KeyController()
{

}

void KeyController::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		_pressedCount++;
		_velocity.x = _speed.x * -1;
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		_pressedCount++;
		_velocity.x = _speed.x;
	}
}

void KeyController::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW
		|| keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		_pressedCount--;

		if (_pressedCount > 0)
		{
			if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
				_velocity.x = _speed.x;
			else
				_velocity.x = _speed.x * -1;
		}
		else
			_velocity.x = 0;
	}
}