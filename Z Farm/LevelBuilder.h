#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class LevelBuilder
{
public:
	LevelBuilder(ZEngine::GameDataRef data);
	~LevelBuilder();

	void Update(float dT);
	void Draw();
private:
	int _scrollSelector = 0;
	ZEngine::GameDataRef _data;

	sf::IntRect _texRect = sf::IntRect(0, 0, 32, 32);

	sf::Sprite _curSelectedTexture;
	sf::RectangleShape _curTextureOutline;

	sf::RectangleShape _hoveredTile;


	std::vector<std::vector<sf::Vector2i>> _curMap;
};
