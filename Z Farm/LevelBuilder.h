#pragma once
#include "Game.h"
#include "Room.h"
#include <SFML/Graphics.hpp>

#include <string>

class LevelBuilder
{
public:
	LevelBuilder(ZEngine::GameDataRef data, Room* roomRef);
	~LevelBuilder();

	void Update(float dT);
	void Draw();

	void Scroll(int dir);

	void AddTile();
	void RemoveTile();
	void ReplaceTile();

	void SaveLevel();
	void LoadLevel();

private:
	int _scrollSelector = 0;
	ZEngine::GameDataRef _data;

	Room* _roomRef;

	sf::IntRect _texRect = sf::IntRect(0, 0, 32, 32);

	sf::Sprite _curSelectedTexture;
	sf::RectangleShape _curTextureOutline;

	sf::RectangleShape _hoveredTile;


	std::vector<std::vector<sf::Vector2i>> _curMap;

	bool CheckForLevel(std::string levelName);

};
