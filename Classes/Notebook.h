#ifndef __NOTEBOOK_H__
#define __NOTEBOOK_H__

#include "cocos2d.h"

namespace tinyxml2
{
	class XMLElement;
}

class Wall;
class Gate;
class Switch;
class Highlight;
class Player;
class Notebook : public cocos2d::Node
{
public:
	Notebook();
	Notebook(std::string filename);
	~Notebook();

	void loadPage(std::string filename);
	void createLines(int num);
	Player* getPlayer() const { return _player; }
	Switch* getUsableSwitch() const { return _usableSwitch; }
	Gate* getUsableGate() const { return _usableGate; }

	virtual void update(float dt);

private:
	std::vector<int> getLineValues(std::string lines);
	void addGates(tinyxml2::XMLElement* element, Gate* gateA, Gate* gateB);
	void addWall(tinyxml2::XMLElement* element);
	void addSwitch(tinyxml2::XMLElement* element);
	void addHighlight(tinyxml2::XMLElement* element);
	void addEraser(tinyxml2::XMLElement* element);
	void addPlayer(tinyxml2::XMLElement* element);

private:
	std::vector<Switch*> _switches;
	std::vector<Gate*> _gates;
	std::vector<Wall*> _walls;
	std::vector<Highlight*> _highlights;
	std::map<std::string, std::vector<Wall*>> _wallMap;
	int _lineHeight;
	Player* _player;
	cocos2d::Sprite *_glowSwitch, *_glowGate;
	Switch* _usableSwitch;
	Gate* _usableGate;
};

#endif