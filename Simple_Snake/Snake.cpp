#include "Snake.h"


Snake::Snake(Direction newDirection, Point newCenter, float newHeight, float newWidth) : GameObject(newCenter, newHeight, newWidth)
{
	tails.push_front(new Tail(RIGHT, newCenter.x - newWidth / 2 - 5.0f, newCenter.y, newHeight, 10.0f));
	prevDir = currDir = newDirection;
	points = 0;
}

Snake::Snake(Direction newDirection, float x, float y, float newHeight, float newWidth) : GameObject(Point(x, y), newHeight, newWidth)
{
	prevDir = currDir = newDirection;
	points = 0;
}

void Snake::addPoints(int gained)
{
	points += gained;
}

void Snake::move(float speed)
{
	switch(currDir)
	{
	case LEFT:
		center.x -= speed;
		break;
	case RIGHT:
		center.x += speed;
		break;
	case UP:
		center.y += speed;
		break;
	case DOWN:
		center.y -= speed;
		break;
	case NONE:
		break;
	}
	if (currDir != NONE)
	{
		float tailRollOver = (tails.back).shrink(speed);
		if (tailRollOver != -1.0f)
		{
			tails.pop_back();
			(tails.back).shrink(tailRollOver);
		}
	}
}

bool Snake::checkWallCollisions(std::list<Wall> walls)
{
	for (Wall w : walls)
	{
		if (checkCollision(w)) return true;
	}
	return false;
}

bool Snake::checkFruitCollisions(Fruit fruit)
{
	return checkCollision(fruit);
}

bool Snake::checkCollision(GameObject obj)
{
	if (!(getRight() < obj.getLeft() || getLeft() > obj.getRight() || getTop() < obj.getBottom() || getBottom() > obj.getTop()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Snake::setDirection(Direction newDirection)
{
	currDir = newDirection;
}

std::list<Tail> Snake::getTails()
{
	return tails;
}

void Snake::addTail()
{

}


Snake::~Snake()
{
}