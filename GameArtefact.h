#pragma once
#include <unordered_set>
#include <string>
#include "Utility.cpp"

class GameArtefact
{
protected:
	Vector2D position;
	Vector2D speed;
	Vector2D acceleration;
	std::unordered_set<std::string> tags;
	const float speedLimit = 600.0f;
	u32 color;
public:
	GameArtefact(float position_x, float position_y, u32 color);
	GameArtefact(float position_x, float position_y);
	void addTag(std::string tag);
	bool removeTag(std::string tag);
	void UpdatePosition(float dt);
	void setPosition(float position_x, float position_y);
	void setSpeed(float speed_x, float speed_y);
	void setAcceleration(float acceleration_x, float acceleration_y);
	Vector2D getPosition();
	Vector2D getSpeed();
	Vector2D getAcceleration();
	u32 getColor();

};

