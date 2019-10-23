#pragma once

#include "Point.h"

class GameObject
{
protected:
	Point center;
	float height;
	float width;
public:
	GameObject(Point newCenter, float newHeight, float newWidth);
	Point getCenter();
	float getHeight();
	float getWidth();
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	void setCenter(Point newCenter);
	void setCenter(float x, float y);
	void setHeight(float newHeight);
	void setWidth(float newWidth);
	~GameObject();
};