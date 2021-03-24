#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::Update(float dT)
{
	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i].Update(dT);
	}
}

void Level::Draw()
{
	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i].Draw();
	}
}
