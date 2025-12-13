#include "Ball.h"

Ball::Ball(float position_x, float position_y, u32 color, float radius) : GameArtefact(position_x,position_y, color)
{
	this->radius = radius;
}

float Ball::getRadius()
{
	return radius;
}

void Ball::setRadius(float radius)
{
	this->radius = radius;
}
