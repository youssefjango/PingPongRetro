#pragma once
#include <unordered_set>
#include <string>
#include "Utility.cpp"

class GameArtefact
{
	struct Vector2D {
		float x, y;
	};
private:
	
	Vector2D position;
	Vector2D speed;
	Vector2D acceleration;
	std::unordered_set<std::string> tags;
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
};

