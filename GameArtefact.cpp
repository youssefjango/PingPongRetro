#include "GameArtefact.h"

GameArtefact::GameArtefact(float position_x, float position_y, u32 color)
{
	this->position.x = position_x;
	this->position.y = position_y;
	this->color = color;
}

GameArtefact::GameArtefact(float position_x, float position_y)
{
	this->position.x = position_x;
	this->position.y = position_y;
}

void GameArtefact::addTag(std::string tag)
{
	auto b = this->tags.insert(tag);
}

bool GameArtefact::removeTag(std::string tag)
{
	return this->tags.erase(tag);
}

void GameArtefact::UpdatePosition(float dt)
{

}

void GameArtefact::setPosition(float position_x, float position_y)
{
	this->position.x = position_x;
	this->position.y = position_y;
}

void GameArtefact::setSpeed(float speed_x, float speed_y)
{
	this->speed.x = speed_x;
	this->speed.y = speed_y;
}

void GameArtefact::setAcceleration(float acceleration_x, float acceleration_y)
{
	this->acceleration.x = acceleration_x;
	this->acceleration.y = acceleration_y;
}

Vector2D GameArtefact::getPosition()
{
	return position;
}

Vector2D GameArtefact::getSpeed()
{
	return speed;
}

Vector2D GameArtefact::getAcceleration()
{
	return acceleration;
}

u32 GameArtefact::getColor()
{
	return color;
}
