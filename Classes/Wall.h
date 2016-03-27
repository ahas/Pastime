#ifndef __WALL_H__
#define __WALL_H__

#include "Doodle.h"

enum class WallColor
{
	Black,
	Red,
	Green,
	Blue
};

class Wall : public Doodle
{
public:
	Wall(WallColor wallColor);
	~Wall();

	WallColor wallColor() const { return _wallColor; }

private:
	WallColor _wallColor;
};

#endif