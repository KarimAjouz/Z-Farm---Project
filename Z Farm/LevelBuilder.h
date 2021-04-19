#pragma once
#include "Game.h"
#include "Level.h"
#include "TilePicker.h"
#include "Player.h"


#include <SFML/Graphics.hpp>

#include <string>

class LevelBuilder
{
public:
	LevelBuilder(ZEngine::GameDataRef data, b2World* worldRef, Level* levelRef, Player* playerRef);
	~LevelBuilder();

	void Update(float dT);
	void Draw();

	void Scroll(int dir);

	void AddTile();
	void RemoveTile();
	void ReplaceTile();

	void SaveLevel();
	void LoadLevel();
	void LoadLevel(std::string name);

	void MouseRelease();


	void OpenSelector();

private:
	int _scrollSelector = 0;
	ZEngine::GameDataRef _data;

	sf::Vector2f _curRoomOffset = sf::Vector2f();
	Level* _levelRef;
	b2World* _worldRef;
	Player* _playerRef;

	sf::IntRect _texRect = sf::IntRect(0, 0, 32, 32);

	sf::Sprite _curSelectedTexture;
	sf::RectangleShape _curTextureOutline;

	sf::RectangleShape _hoveredTile;
	sf::RectangleShape _newRoomSelector;

	std::vector<std::vector<sf::Vector2i>> _curMap;

	TilePicker _tilePicker;

	bool CheckForLevel(std::string levelName);
	bool _inRoom = false;

	void NewRoom();
	void AddUnit();
	void AddObstacle();

	void TestMouseHover();
};
