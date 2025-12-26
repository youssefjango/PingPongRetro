#pragma once
#include "GameArtefact.h"
class Button : public GameArtefact
{
private:
	Vector2D halfSizes;
	std::string text;
	int action; 
public:
	Button(float position_x, float position_y, u32 color, Vector2D halfSizes, std::string text);
	int getActionInteger();
	Vector2D getHalfSizes();
	std::string getText();
};

