#include "GameObject.h"



GameObject::GameObject(Point newCenter, float newHeight, float newWidth)
{
	center = newCenter;
	height = newHeight;
	width = newWidth;
}

Point GameObject::getCenter()
{
	return center;
}

float GameObject::getHeight()
{
	return height;
}

float GameObject::getWidth()
{
	return width;
}

float GameObject::getLeft()
{
	return center.x - (width / 2);
}

float GameObject::getRight()
{
	return center.x + (width / 2);
}

float GameObject::getTop()
{
	return center.y + (height / 2);
}

float GameObject::getBottom()
{
	return center.y - (height / 2);
}

void GameObject::setCenter(Point newCenter)
{
	center = newCenter;
}

void GameObject::setCenter(float x, float y)
{
	center.x = x;
	center.y = y;
}

void GameObject::setHeight(float newHeight)
{
	height = newHeight;
}

void GameObject::setWidth(float newWidth)
{
	width = newWidth;
}

GameObject::~GameObject()
{
}