#pragma once
#include "Tile.h"
#include "Agent.h"
#include "Spike.h"
#include "Node.h"

class Room
{
public:
	Room(ZEngine::GameDataRef data, b2World* worldRef);
	Room(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f offset);
	~Room();

	void Update(float dT);
	void Draw();

	std::vector<std::vector<RoomTileData>> GenEmptyMap();
	Tile GenTile(sf::Vector2i t, int x, int y, bool collision);

	void RemoveTile(int x, int y);
	void AddTile(int x, int y, int xUV, int yUV, bool col);
	std::vector<std::vector<RoomTileData>> GetMap() { return _map; }
	void SetMap(std::vector < std::vector <RoomTileData >> m) { _map = m; }

	sf::Vector2f roomOffset = sf::Vector2f(0, 0);
	sf::RectangleShape roomShape;

	std::vector<Tile> tiles;

	void BuildLevel();



	std::vector<Agent*> agents = std::vector<Agent*>();
	std::vector<Obstacle*> obstacles = std::vector<Obstacle*>();

	std::vector<Node*> navMap;

	void DrawTiles();
	void DrawAgents();
	void DrawObstacles();

	bool showNav = false;
private:

	ZEngine::GameDataRef _data;
	b2World* _worldRef;

	RoomTileData floorTile = RoomTileData(sf::Vector2i(1, 0), true);
	RoomTileData emptyTile = RoomTileData(sf::Vector2i(1, 1), false);


	std::vector < std::vector < RoomTileData >> _map;

	void BuildPhyics();

	void SetView();

	void RemoveDeadEntities();

	void GenNavMap();
};

