#include "Fruit.h"



Fruit::Fruit(int newPoints,  Point newCenter, float newHeight, float newWidth) : GameObject(newCenter, newHeight, newWidth)
{
	points = newPoints;
}

Fruit::Fruit(int newPoints, float x, float y, float newHeight, float newWidth) : GameObject(Point(x, y), newHeight, newWidth)
{
	points = newPoints;
}

int Fruit::getPoints()
{
	return points;
}

void Fruit::move()
{
}


Fruit::~Fruit()
{
}