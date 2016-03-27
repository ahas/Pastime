#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	Title();
	~Title();

    static cocos2d::Scene* createScene();
    virtual bool init();

	CREATE_FUNC(Title);

private:
	void initTouchListener();

private:
	cocos2d::Sprite* _title;
};

#endif
