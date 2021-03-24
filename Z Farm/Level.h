#pragma once

#include "Room.h"
class Level
{
public:
	Level();
	~Level();

	void Update(float dT);
	void Draw();

private:
	std::vector<Room> _rooms;
};

