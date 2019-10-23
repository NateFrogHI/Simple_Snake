#ifndef POINT_H
#define POINT_H

struct Point
{
public:
	float x;
	float y;

	Point() { x = 0.0f; y = 0.0f; }
	Point(float newX, float newY) { x = newX; y = newY; }
};

#endif