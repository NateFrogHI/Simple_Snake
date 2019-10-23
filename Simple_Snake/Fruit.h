#pragma once

//#include <cstdlib.h>
#include "GameObject.h"

class Fruit: public GameObject
{
private:
	int points;
public:
	Fruit(int newpPoints, Point newCenter, float newHeight, float newWidth);
	Fruit(int newPoints, float x, float y, float newHeight, float newWidth);
	int getPoints();
	void move();
	~Fruit();
};