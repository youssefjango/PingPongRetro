#pragma once
#include "GameArtefact.h"
class Paddle : public GameArtefact
{
private:
	//float player_VerticalLevel; now we will use position.y
	//float speed; can be accessed in speed
	float player_halfSizeY = 12.0f, player_halfSizeX = 2.5f;
	float friction = 10.0f;
	//float player_HorizontalPosition = -80.0f;  now we will use position.x
	float influenceFactor = 1.0f;
public:
	Paddle(float position_x, float position_y, u32 color, float frictionPaddle, float influenceFactorPaddle);
};

