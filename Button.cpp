#include "Button.h"

Button::Button(float position_x, float position_y, u32 color, Vector2D halfSizes, std::string text) : GameArtefact(position_x, position_y, color)
{
	this->halfSizes = halfSizes;
	this->text = text;
}

int Button::getActionInteger()
{
	return action;
}
Vector2D Button::getHalfSizes()
{
	return this->halfSizes;
}
std::string Button::getText() {
	return text;
}
