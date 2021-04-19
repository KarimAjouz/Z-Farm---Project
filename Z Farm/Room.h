#pragma once
#include "Tile.h"
#include "Agent.h"
#include "Spike.h"

class Room
{
public:
	Room(ZEngine::GameDataRef data, b2World* worldRef);
	Room(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f offset);
	~Room();

	void Update(float dT);
	void Draw();

	Tile GenTiles(sf::Vector2i t, int x, int y);

	void RemoveTile(int x, int y);
	void AddTile(int x, int y, int xUV, int yUV);
	std::vector<std::vector<sf::Vector2i>> GetMap() { return _map; }
	void SetMap(std::vector < std::vector < sf::Vector2i >> m) { _map = m; }

	sf::Vector2f roomOffset = sf::Vector2f(0, 0);
	sf::RectangleShape roomShape;

	std::vector<Tile> tiles;

	void BuildLevel();



	std::vector<Agent*> agents = std::vector<Agent*>();
	std::vector<Obstacle*> obstacles = std::vector<Obstacle*>();
private:

	ZEngine::GameDataRef _data;
	b2World* _worldRef;



	sf::Vector2i floorTile = sf::Vector2i(1, 0);
	sf::Vector2i emptyTile = sf::Vector2i(1, 6);

	std::vector < std::vector < sf::Vector2i >> _map =
	{
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
		{emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile, emptyTile},
	};

	void BuildPhyics();

	void SetView();

	void RemoveDeadEntities();
};

