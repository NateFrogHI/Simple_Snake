#pragma once

#include "GameObject.h"

class Wall: public GameObject
{
public:
	Wall(Point newCenter, float newHeight, float newWidth);
	Wall(float x, float y, float newHeight, float newWidth);
	~Wall();
};