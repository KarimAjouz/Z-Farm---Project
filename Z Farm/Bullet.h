#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class Bullet
{
public:
	Bullet(ZEngine::GameDataRef data, sf::Vector2f pos, sf::Vector2f target, int speed, int dam);
	~Bullet();

	void Update(float dT);
	void Draw();


	sf::Sprite sprite;

	float damage;

	void MarkForDeath();
	bool IsMarked();
	
private:
	sf::Vector2f CalculateDirection(sf::Vector2f pos, sf::Vector2f target);

	void CheckForDeath();
	void Move(float dT);
	
	sf::Vector2f _dir;
	sf::Vector2f _pos;
	float _speed;

	bool _kill = false;

	ZEngine::GameDataRef _data;
};

