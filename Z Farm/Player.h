#pragma once
#include "Agent.h"
#include "Game.h"
#include "Gun.h"
#include "SaveDataManager.h"
#include "Timer.h"

#include <SFML/Graphics.hpp>

class Player : public Agent
{
public:
	Player(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, SaveDataManager::SaveData saveData, BalanceSheet* b);
	~Player();

	void Update(float dT);
	void Draw();

	bool TakeDamage(float dam, sf::Vector2f zombiePosition);
	void Respawn();

	sf::Vector2f GetPosition();

	Gun gun;

	sf::Sprite sprite;
	float health;
	bool dead;

private:
	void Move(float dT);

	void AugmentKnockback(sf::Vector2f zombiePosition);

	sf::Vector2f _knockbackAmt;

	ZEngine::GameDataRef _data;
	float _speed = 100.0f;
	
	ZEngine::Timer damageTimer;

};

