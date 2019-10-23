#pragma once

#include <list>
#include "GameObject.h"
#include "Tail.h"
#include "Wall.h"
#include "Fruit.h"
#include "Direction.h"
#include "Point.h"


class Snake: public GameObject
{
private:
	Direction prevDir;
	Direction currDir;
	std::list<Tail> tails;
	bool checkCollision(GameObject obj);
	int points;

public:
	Snake(Direction newDirection, Point newCenter, float newHeight, float newWidth);
	Snake(Direction newDirection, float x, float y, float newHeight, float newWidth);
	void addPoints(int gained);
	void move(float speed);
	bool checkWallCollisions(std::list<Wall> walls);
	bool checkFruitCollisions(Fruit fruit);
	void setDirection(Direction newDirection);
	std::list<Tail> getTails();
	void addTail();
	~Snake();
};