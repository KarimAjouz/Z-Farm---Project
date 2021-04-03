#pragma once

#include "Room.h"
class Level
{
public:
	Level(ZEngine::GameDataRef data, b2World* worldRef);
	~Level();

	void Update(float dT);
	void Draw();

	std::vector<Room> rooms;
private:

	ZEngine::GameDataRef _data;
	b2World* _worldRef;
};

