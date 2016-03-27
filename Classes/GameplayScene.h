#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"

class Notebook;
class KeyController;
class Player;
class Gameplay : public cocos2d::LayerColor
{
public:
	Gameplay();
	Gameplay(const char* filename);
	~Gameplay();

	virtual void update(float dt) override;
	static cocos2d::Scene* createScene(const char* filename);
	bool initWithFile(const char* filename);
	void initNotebook(const char* filename);
	void initControllers();
	void initUseKeyListener();
	void useUsableObject();

	CREATE_FUNC(Gameplay)

private:
	Notebook* _notebook;
	KeyController* _keyController;
	Player* _player;
};

#endif