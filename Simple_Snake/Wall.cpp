#include "Wall.h"



Wall::Wall(Point newCenter, float newHeight, float newWidth) : GameObject(newCenter, newHeight, newWidth)
{
}

Wall::Wall(float x, float y, float newHeight, float newWidth) : GameObject(Point(x, y), newHeight, newWidth)
{
}


Wall::~Wall()
{
}