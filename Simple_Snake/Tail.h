#pragma once

#include "GameObject.h"
#include "Direction.h"

class Tail: public GameObject
{
private:
	Direction moveDir;
public:
	Tail(Direction dir, Point newCenter, float newHeight, float newWidth);
	Tail(Direction dir, float x, float y, float newHeight, float newWidth);
	float shrink(float speed);
	~Tail();
};