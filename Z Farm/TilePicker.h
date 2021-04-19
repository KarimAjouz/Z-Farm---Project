#pragma once
#include "Tile.h"
#include "Agent.h"
#include "Obstacle.h"

class TilePicker
{
public:

	TilePicker(ZEngine::GameDataRef data);
	~TilePicker();

	void Update(float dT);
	void Draw();


	sf::IntRect GetTileRect();

	void Activate();
	bool active;

	enum class State
	{
		shipTiles,
		units,
		obstacles,
		props
	};

	State state = State::shipTiles;

private:

	sf::Sprite _selector;
	ZEngine::GameDataRef _data;

	sf::RectangleShape _hoveredTile;
	sf::RectangleShape _selectorWindow;
	sf::RectangleShape _activeTile;

	void UpdateState();
	// Agent* InstantiateAgent();
	// Obstacle* InstantiateObstacle();

};

