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
	void Deactivate();

	sf::Sprite GetCurSelector() { return _curSelector; }

	bool isMouseInPicker();

	bool active;

	enum class State
	{
		collidableTiles,
		backgroundTiles,
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

	State state = State::collidableTiles;

	SelectorItem GetSelectorItem();

	void SetActiveTileSizePos(sf::Vector2f pos, sf::Vector2f size);
private:
	ZEngine::GameDataRef _data;

	sf::RectangleShape _hoveredTile;
	sf::RectangleShape _selectorWindow;
	sf::RectangleShape _activeTile;

	std::vector<sf::Sprite> _backgroundSpritesheetList;
	std::vector<sf::Sprite> _collidablesSpritesheetList;

	sf::Sprite _curSelector;

	std::vector<SelectorItem> _obstacleList;
	std::vector<SelectorItem> _unitList;

	void UpdateState();
	// Agent* InstantiateAgent();
	// Obstacle* InstantiateObstacle();

	void InitEntities();
	void RepositionWindows();
	void UpdateHoveredTilePos(sf::Vector2f mousePos);

	void InitSheet(std::string filepath, bool isCol);
};