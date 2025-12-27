#include "Paddle.h"
#include <time.h>

Paddle::Paddle(float position_x, float position_y, u32 color, float frictionPaddle, float influenceFactorPaddle, float increaseHitFactor) : GameArtefact(position_x, position_y, color)
{
	this->friction = frictionPaddle;
	this->influenceFactor = influenceFactorPaddle;
	this->increaseHitFactor = (increaseHitFactor >= 1.0f) ? increaseHitFactor : 1;
	this->upControl = UNDEFINED;
	this->downControl = UNDEFINED;
	addTag("paddle");
	//for random implementation
	srand(time(0));
}

void Paddle::setBrain()
{
	int random = std::rand() % 6;
	brain = random == 0 ? Hardcore
		: random == 1 ? Difficult
		: random == 2 || random == 3 ? Medium
		: Easy;
}

void Paddle::setControls(Controls up, Controls down)
{
	this->upControl = up;
	this->downControl = down;
}

Controls Paddle::getUpControls()
{
	return this->upControl;
}

Controls Paddle::getDownControls()
{
	return this->downControl;
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

float Paddle::getIncreaseHitFactor()
{
	return this->increaseHitFactor;
}

void Paddle::setIncreaseHitFactor(float increaseHitFactor)
{
	this->increaseHitFactor = increaseHitFactor;
}

float Paddle::getScore()
{
	return this->score;
}

void Paddle::incrementScore()
{
	this->score++;
}

void Paddle::respondToEnvirnment(Ball* ball)
{
	switch (brain) {
	case Easy:
		acceleration.y = (ball->getSpeed().x * position.x > 0) ? 100.0f * (ball->getPosition().y - position.y) : 0.0f;
		break;
	case Medium:
		acceleration.y = 500.0f * (ball->getPosition().y - position.y);
		break;
	case Difficult:
		(ball->getPosition().y > position.y) ? acceleration.y += 1400 
			: (ball->getPosition().y < position.y) ? acceleration.y -= 1400 : acceleration.y = 0;
		break;
	case Hardcore:
		position.y = ball->getPosition().y;
		break;
	}
	if (abs(position.y - ball->getPosition().y) <= 1e-10) {
		acceleration.y = 10000.0f * (((double)rand()) / RAND_MAX);
	}
}


