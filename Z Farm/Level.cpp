#include "Level.h"
#include "AlarmPig.h"

Level::Level()
{
}

Level::Level(ZEngine::GameDataRef data, b2World* worldRef) :
	_data(data),
	_worldRef(worldRef)
{
	rooms.push_back(Room(data, worldRef, sf::Vector2f(0.0f, 0.0f)));

	for (int i = 0; i < rooms.size(); i++)
	{
		rooms[i].BuildLevel();
	}

}

Level::~Level()
{
}

void Level::Init(ZEngine::GameDataRef data, b2World* worldRef)
{
	_data = data;
	_worldRef = worldRef;
	rooms.push_back(Room(data, worldRef, sf::Vector2f(0.0f, 0.0f)));

	for (int i = 0; i < rooms.size(); i++)
	{
		rooms[i].BuildLevel();
	}


	activeRoom = &rooms[0];
	activeRoom->agents.push_back(new AlarmPig(_data, _worldRef, sf::Vector2f(600.0f, 500.0f)));
}

void Level::Update(float dT)
{
	for (int i = 0; i < rooms.size(); i++)
	{
		rooms[i].Update(dT);
	}
}

void Level::Draw()
{
	for (int i = 0; i < rooms.size(); i++)
	{
		rooms[i].Draw();
	}
}
