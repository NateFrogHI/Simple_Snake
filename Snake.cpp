#include "Snake.h"


Snake::Snake()
{
	numOfJoints = 2;
	headDir = RIGHT;
	tailDir = RIGHT;
	head = new SnakeJoint();
	tail = new SnakeJoint();
	head->prev = nullptr;
	head->next = tail;
	tail->prev = head;
	tail->next = 0;
	current = head;
}

void Snake::setPoint(Point headPoint, Point tailPoint)
{
	head->location = headPoint;
	tail->location = tailPoint;
}

bool Snake::dropTurn()
{
	if (numOfJoints > 2)
	{
		tail = tail->prev;
		tail->next->prev = nullptr;
		delete tail->next;
		tail->next = nullptr;
		numOfJoints--;
		return true;
	}
	else
	{
		return false;
	}
}

void Snake::addTurn(Direction dir)
{
	headDir = dir;
	SnakeJoint * newPoint = new SnakeJoint();
	newPoint->prev = head;
	newPoint->next = head->next;
	newPoint->location = head->location;
	head->next->prev = newPoint;
	head->next = newPoint;
	numOfJoints++;
}

// 
void Snake::advCurrent()
{
	current = current->next;
	if (current->next == nullptr)
	{
		currentIsTail = true;
	}
	else
	{
		currentIsTail = false;
	}
}

// 
void Snake::resetCurrent()
{
	current = head;
	currentIsTail = false;
}


Snake::~Snake()
{
}
