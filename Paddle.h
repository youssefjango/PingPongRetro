#pragma once
#include "GameArtefact.h"
class Paddle : public GameArtefact
{
private:
	//float player_VerticalLevel; now we will use position.y
	//float speed; can be accessed in speed
	Vector2D halfSizes = {2.5f,12.0f};
	float friction = 10.0f;
	//float player_HorizontalPosition = -80.0f;  now we will use position.x
	float influenceFactor = 1.0f;
public:
	Paddle(float position_x, float position_y, u32 color, float frictionPaddle, float influenceFactorPaddle);
	void setFriction(float friction);
	void setHalfSizes(float half_x, float half_y);
	void setAcceleration(float Yacceleration);
	void setSpeed(float Yspeed);
	void setInfluenceFactor(float influence);
	float getFriction();
	Vector2D getHalfSizes();
	float getInfluenceFactor();
	
};

