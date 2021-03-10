#pragma once

#include "Agent.h"
#include "Player.h"
#include "Game.h"
#include "ResourceBar.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Zombie : public Agent
{
public:
	Zombie(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, Player* playerRef);
	~Zombie();

	void Init();
	void Update(float dT);
	void Draw();

	void DamageZombie(float dam);

	sf::Sprite sprite;

	void MarkForDeath(bool mark);
	bool IsMarked();

	void CollideWithEntity(sf::Vector2f colMovement);

	float damage;

	void AugmentKnockback(float amt);

private:
	void Move(float dT);

	Player* _playerRef;
	ZEngine::GameDataRef _data;

	float _health;
	float _maxHealth;
	bool _kill = false;

	ZEngine::ResourceBar _healthBar;

	float _speed = 30.0f;

	sf::Vector2f _knockbackAmt;

};

