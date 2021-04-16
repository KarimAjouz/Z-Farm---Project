#pragma once

#include "Room.h"

class Level
{
public:
	Level(ZEngine::GameDataRef data, b2World* worldRef);
	~Level();


	void Init(ZEngine::GameDataRef _data, b2World* worldRef);
	void Update(float dT);
	void Draw();

	void ClearUnitPhysics();

	void SpikeAgents();

	std::vector<Room> rooms;
	Room* activeRoom = nullptr;
private:

	ZEngine::GameDataRef _data;
	b2World* _worldRef;
};

