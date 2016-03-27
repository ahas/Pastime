#include "Controllers.h"

ControllerBase::ControllerBase()
: _pressedCount(0)
, _target(nullptr)
{
}

ControllerBase::~ControllerBase()
{

}

void ControllerBase::update(float dt)
{
	if (!_target)
		return;

	cocos2d::Vec2 pos = _target->getPosition();
	pos += _velocity;
	_target->setPosition(pos);
}

void ControllerBase::setControlTarget(cocos2d::Node* target)
{
	_target = target;
	this->schedule(schedule_selector(ControllerBase::update));
}

void ControllerBase::setSpeedXY(cocos2d::Vec2 speed)
{
	_speed = speed;
}