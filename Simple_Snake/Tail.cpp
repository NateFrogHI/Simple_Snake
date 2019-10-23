#include "Tail.h"



Tail::Tail(Direction dir, Point newCenter, float newHeight, float newWidth) : GameObject(newCenter, newHeight, newWidth)
{
	moveDir = dir;
}

Tail::Tail(Direction dir, float x, float y, float newHeight, float newWidth) : GameObject(Point(x, y), newHeight, newWidth)
{
	moveDir = dir;
}

float Tail::shrink(float speed)
{
	float remainder = -1.0f;
	float x = 0.0f, y = 0.0f;
	switch (moveDir)
	{
	case UP:
		if (height > speed)
		{
			height -= speed;
			center.y += (speed / 2);
		}
		else
		{
			remainder = speed - height;
		}
		break;
	case DOWN:
		if (height > speed)
		{
			height -= speed;
			center.y -= (speed / 2);
		}
		else
		{
			remainder = speed - height;
		}
		break;
	case LEFT:
		if (width > speed)
		{
			width -= speed;
			center.x -= (speed / 2);
		}
		else
		{
			remainder = speed - width;
		}
		break;
	case RIGHT:
		if (width > speed)
		{
			width -= speed;
			center.x += (speed / 2);
		}
		else
		{
			remainder = speed - width;
		}
		break;
	}
	return remainder;
}


Tail::~Tail()
{
}