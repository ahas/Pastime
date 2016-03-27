#include "Wall.h"

static const std::string _wallFileNames[] =
{
	"wall.png",
	"wall_red.png",
	"wall_green.png",
	"wall_blue.png"
};

Wall::Wall(WallColor wallColor)
{
	_wallColor = wallColor;
	cocos2d::Sprite::initWithFile(_wallFileNames[(int)wallColor]);
}

Wall::~Wall()
{

}