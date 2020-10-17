#pragma once

#include "Agent.h"
#include "Game.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Zombie : public Agent
{
public:
	Zombie(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, Player* playerRef);
	~Zombie();

	void Init();
	void Update(float dT);
	void Draw(float dT);

	void DamageZombie(float dam);


	sf::Sprite sprite;


	void MarkForDeath(bool mark);
	bool IsMarked();

private:
	void Move(float dT);
	void AugmentKnockback(float amt);

	ZEngine::GameDataRef _data;

	Player* _playerRef;

	float _health;
	bool _kill = false;

	float _speed = 30.0f;

	sf::Vector2f _knockbackAmt;

};

