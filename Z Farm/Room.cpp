#include "Room.h"

Room::Room(ZEngine::GameDataRef data, b2World* worldRef)
{
	for (int y = 0; y < _map.size(); y++)
	{
		for (int x = 0; x < _map[y].size(); x++)
		{
			_tiles.push_back(GenTile(_map[y][x], data, worldRef, x, y));
		}
	}
}

Room::~Room()
{
}

void Room::Update(float dT)
{
}

void Room::Draw()
{
	for (int i = 0; i < _tiles.size(); i++)
		_tiles.at(i).Draw();
}

Tile Room::GenTile(char c, ZEngine::GameDataRef data, b2World* worldRef, int x, int y)
{
	Tile t = Tile(data, worldRef, "BoatBG", TILE_PATH, false, sf::Vector2f(64 * x, 64 * y), sf::IntRect(64, 256, 32, 32));

	switch (c)
	{
		case 'E':
			t = Tile(data, worldRef, "BoatBG", TILE_PATH, false, sf::Vector2f((64 * x) + 32, (64 * y) + 32), sf::IntRect(64, 256, 32, 32));
			break;
		case 'F':
			t = Tile(data, worldRef, "BoatFloor", TILE_PATH, true, sf::Vector2f((64 * x) + 32, (64 * y) + 32), sf::IntRect(64, 32, 32, 32));
			break;
		default:
			t = Tile(data, worldRef, "BoatBG", TILE_PATH, false, sf::Vector2f((64 * x) + 32, (64 * y) + 32), sf::IntRect(64, 256, 32, 32));
			break;

	}
	return t;
}
