#include "Paddle.h"

Paddle::Paddle(float position_x, float position_y, u32 color, float frictionPaddle, float influenceFactorPaddle) : GameArtefact(position_x, position_y, color)
{
	this->friction = frictionPaddle;
	this->influenceFactor = influenceFactorPaddle;
	addTag("paddle");
}
