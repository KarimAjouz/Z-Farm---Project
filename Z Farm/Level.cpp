#include "Level.h"

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
