#ifndef __LINE_H__
#define __LINE_H__

#include "cocos2d.h"

enum class LineType
{
	TOP,
	MIDDLE,
	BOTTOM
};

class Line : public cocos2d::Sprite
{
public:
	Line(LineType type);
	~Line();
	
	bool init(LineType type);
};

#endif