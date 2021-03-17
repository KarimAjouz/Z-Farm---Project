#pragma once

#include "Agent.h"
#include "Player.h"
#include "Game.h"
#include "ResourceBar.h"

#include "Animation.h"

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

	void MarkForDeath();
	bool IsMarked();

	void CollideWithEntity(sf::Vector2f colMovement);

	float damage;

	void AugmentKnockback(float amt);

private:
	enum State
	{
		walking,
		attackWindUp,
		attack,
		attackReset,
		takingDamage,
		dying
	};
	
	State _state = walking;


	void Move(float dT);
	void UpdateState();
	void UpdateAnimations();

	Player* _playerRef;
	ZEngine::GameDataRef _data;

	sf::RectangleShape r = sf::RectangleShape(sf::Vector2f(20, 30));
	sf::IntRect _attackZone = sf::IntRect(0, 0, 20, 30);

	float _health;
	float _maxHealth;
	bool _kill = false;
	bool _isFlipped;

	ZEngine::ResourceBar _healthBar;

	float _speed = 30.0f;

	sf::Vector2f _knockbackAmt;

	ZEngine::Animation* _curAnim;

	ZEngine::Animation _walk;
	ZEngine::Animation _attackWindUp;
	ZEngine::Animation _attackReset;
	ZEngine::Animation _attack;
	ZEngine::Animation _takingDamage;
	ZEngine::Animation _dying;

	void FlipSprite();


};

