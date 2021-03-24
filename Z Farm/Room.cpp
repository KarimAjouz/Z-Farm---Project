#include "Room.h"

Room::Room(ZEngine::GameDataRef data, b2World* worldRef) :
	_data(data),
	_worldRef(worldRef)
{
	BuildLevel();
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

void Room::BuildLevel()
{
	_tiles.clear();
	for (int y = 0; y < _map.size(); y++)
	{
		for (int x = 0; x < _map[y].size(); x++)
		{
			_tiles.push_back(GenTiles(_map[y][x], x, y));
		}
	}
}

Tile Room::GenTiles(sf::Vector2i uv, int x, int y)
{
	bool collision = true;

	if (uv.y * 32 >= 160)
		collision = false;
	Tile tile = Tile(_data, _worldRef, "Tiles", TILE_PATH, collision, sf::Vector2f((x * 64) + 32, (y * 64) + 32), sf::IntRect(uv.x * 32, uv.y * 32, 32, 32));
	return tile;
}

/// <summary>
/// Removes the tile at the grid location (x, y)
/// </summary>
/// <param name="x"> The x location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="y"> The y location on the level grid (NOTE: NOT SCREEN SPACE) </param>
void Room::RemoveTile(int x, int y)
{
	_tiles.at(x + (15 * y)).RemovePhysics();
	_tiles.at(x + (15 * y)) = Tile(_data, _worldRef, "Tiles", TILE_PATH, false, sf::Vector2f((x * 64) + 32, (y * 64) + 32), sf::IntRect(352, 256, 32, 32));
	_map[y][x] = sf::Vector2i(352/32, 256/32);
}


/// <summary>
/// Adds a tile with specific UV coords at a location.
/// </summary>
/// <param name="x"> The x location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="y"> The y location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="xUV"> The x UV coords of the texture we are drawing. </param>
/// <param name="yUV"> The y UV coords of the texture we are drawing. </param>
void Room::AddTile(int x, int y, int xUV, int yUV)
{
	bool collision = true;

	if (yUV >= 160)
		collision = false;

	_tiles.at(x + (15 * y)) = Tile(_data, _worldRef, "Tiles", TILE_PATH, collision, sf::Vector2f((x * 64) + 32, (y * 64) + 32), sf::IntRect(xUV, yUV, 32, 32));
	_map[y][x] = sf::Vector2i(xUV / 32, yUV / 32);
}
