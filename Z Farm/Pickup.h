#pragma once

#include "Game.h"
#include "Player.h"

#include <SFML/Graphics.hpp>


class Pickup
{
public:
	Pickup();
	Pickup(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, sf::Vector2f dir);
	~Pickup();

	sf::Sprite sprite;
	void Update(float dT);
	void Draw();

	int Destroy(bool collected);

	bool IsMarked();


private:
	ZEngine::GameDataRef _data;

	int _value;

	sf::Vector2f _movement;

	bool _markedForDeath;

};

