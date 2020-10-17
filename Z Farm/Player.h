#pragma once
#include "Agent.h"
#include "Game.h"
#include "Gun.h"

#include <SFML/Graphics.hpp>

class Player : public Agent
{
public:
	Player(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data);
	~Player();

	void Init();
	void Update(float dT);
	void Draw(float dT);

	sf::Vector2f GetPosition();

	Gun gun;

	sf::Sprite sprite;

private:
	void Move(float dT);

	ZEngine::GameDataRef _data;
	float _speed = 100.0f;

};

