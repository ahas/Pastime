#ifndef __CONTROLLERS_H__
#define __CONTROLLERS_H__

#include "cocos2d.h"

class ControllerBase : public cocos2d::Node
{
public:
	ControllerBase();
	~ControllerBase();

	void setControlTarget(cocos2d::Node* target);

	cocos2d::Vec2 getSpeedXY() const { return _speed; }
	void setSpeedXY(cocos2d::Vec2 speed);

	void update(float dt);

protected:
	cocos2d::Node* _target;
	cocos2d::Vec2 _speed;
	cocos2d::Vec2 _velocity;
	int _pressedCount;
};

class KeyController : public ControllerBase
{
public:
	KeyController(cocos2d::Node* node);
	~KeyController();

private:
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

class TouchController : public ControllerBase
{
public:
	TouchController(cocos2d::Node* node);
	~TouchController();

private:
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

#endif