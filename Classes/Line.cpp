#include "Line.h"

Line::Line(LineType type)
{
	init(type);
}

Line::~Line()
{

}

bool Line::init(LineType type)
{


	if (!Sprite::initWithFile(filename))
		return false;

	return true;
}