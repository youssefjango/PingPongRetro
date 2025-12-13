#pragma once
#include "GameArtefact.h"
class Ball : public GameArtefact
{
private:
	float radius;
public:
	Ball(float position_x, float position_y, u32 color, float radius);
	float getRadius();
	void setRadius(float radius);
};

