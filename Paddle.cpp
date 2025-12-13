#include "Paddle.h"

Paddle::Paddle(float position_x, float position_y, u32 color, float frictionPaddle, float influenceFactorPaddle) : GameArtefact(position_x, position_y, color)
{
	this->friction = frictionPaddle;
	this->influenceFactor = influenceFactorPaddle;
	addTag("paddle");
}

void Paddle::setFriction(float friction)
{
	this->friction = friction;
}

void Paddle::setHalfSizes(float half_x, float half_y)
{
	this->halfSizes.x = half_x;
	this->halfSizes.y = half_y;
}


void Paddle::setAcceleration(float Yacceleration)
{
	GameArtefact::setAcceleration(acceleration.x, Yacceleration);
}

void Paddle::setSpeed(float Yspeed)
{
	GameArtefact::setSpeed(acceleration.x, Yspeed);
}

void Paddle::setInfluenceFactor(float influence)
{
	this->influenceFactor = influence;
}

float Paddle::getFriction()
{
	return this->friction;
}

Vector2D Paddle::getHalfSizes()
{
	return this->halfSizes;
}

float Paddle::getInfluenceFactor()
{
	return this->influenceFactor;
}
