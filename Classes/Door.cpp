#include "Gates.h"

Door::Door()
{
	cocos2d::Sprite::initWithFile("bg_door.png");

	_frame = cocos2d::Sprite::create("frame_door.png");
	_frame->setAnchorPoint(cocos2d::Vec2(0, 0));
	this->addChild(_frame);
}

Door::~Door()
{

}