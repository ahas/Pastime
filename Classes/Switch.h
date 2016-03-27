#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "Doodle.h"
#include "Wall.h"

class Switch : public Doodle
{
public:
	Switch(WallColor wallColor);
	~Switch();

	std::vector<Wall*> getLinkedWalls() const { return _linkedWalls; }
	void setLinkedWalls(std::vector<Wall*> walls) { _linkedWalls = walls; }

private:
	std::vector<Wall*> _linkedWalls;
};

#endif