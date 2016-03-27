#ifndef __GATES_H__
#define __GATES_H__

#include "Doodle.h"

class Gate : public Doodle
{
public:
	Gate() {}
	~Gate() {}

	Gate* getLinkedGate() const { return _linkedGate; }
	void linkGate(Gate* gate) { _linkedGate = gate; }

private:
	Gate* _linkedGate;
};

class Door : public Gate
{
public:
	Door();
	~Door();

private:
	cocos2d::Sprite* _frame;
};

class Stairs : public Gate
{
public:
	Stairs();
	~Stairs();

private:
	Stairs* _linkedStairs;
};

#endif