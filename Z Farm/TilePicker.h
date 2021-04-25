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

	struct SelectorItem
	{
		sf::RectangleShape rect;
		sf::Texture* texture;
		int type;
	};

	State state = State::shipTiles;

	SelectorItem GetSelectorItem();
private:

	sf::Sprite _selector;
	ZEngine::GameDataRef _data;

	sf::RectangleShape _hoveredTile;
	sf::RectangleShape _selectorWindow;
	sf::RectangleShape _activeTile;

	std::vector<SelectorItem> _obstacleList;
	std::vector<SelectorItem> _unitList;

	void UpdateState();
	// Agent* InstantiateAgent();
	// Obstacle* InstantiateObstacle();

	void InitEntities();
	void RepositionWindows();
};

