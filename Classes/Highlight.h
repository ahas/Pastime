#ifndef __HIGHLIGHT_H__
#define __HIGHLIGHT_H__

#include "Doodle.h"
#include "ui/UIScale9Sprite.h"

class Highlight : public cocos2d::ui::Scale9Sprite
{
public:
	Highlight();
	~Highlight();

	void setLine(int line) { _line = line; }

private:
	int _line;
};

#endif