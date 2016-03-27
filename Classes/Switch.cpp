#include "Switch.h"

static const std::string _switchFileNames[] =
{
	"switch_red.png",
	"switch_green.png",
	"switch_blue.png"
};

Switch::Switch(WallColor wallColor)
{
	cocos2d::Sprite::initWithFile(_switchFileNames[(int)wallColor - 1]);
}

Switch::~Switch()
{

}