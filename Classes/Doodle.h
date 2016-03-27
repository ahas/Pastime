#ifndef __DOODLE_H__
#define __DOODLE_H__

#include "cocos2d.h"

class Doodle : public cocos2d::Sprite
{
public:
	Doodle() {}
	~Doodle() {}

	int getLine() const { return _line; }
	void setLine(int line) { _line = line; }

private:
	int _line;
};

#endif