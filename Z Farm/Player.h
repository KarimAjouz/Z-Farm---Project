#pragma once
#include "Agent.h"
#include "Game.h"
#include "Gun.h"
#include "SaveDataManager.h"
#include "Timer.h"
#include "Animation.h"

#include <SFML/Graphics.hpp>

class Player : public Agent
{
public:
	Player(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, SaveDataManager::SaveData saveData, BalanceSheet* b, std::vector<Bullet*>* bullets);
	~Player();

	void Update(float dT);
	void Draw();

	bool TakeDamage(float dam, sf::Vector2f zombiePosition);
	void Respawn();

	void Attack();

	sf::Vector2f GetPosition();

	Gun gun;

	sf::Sprite sprite;
	float health;
	bool dead;

private:
	enum State
	{
		idle,
		walking,
		takingDamage,
		attackWindUp,
		attacking,
		dashing,
		dying
	};

	State _state = idle;

	void Move(float dT);
	ZEngine::GameDataRef _data;
	
	ZEngine::ResourceBar _healthBar;
	void AugmentKnockback(sf::Vector2f zombiePosition);

	sf::Vector2f _knockbackAmt;

	bool _isFlipped = false;

	float _speed = 100.0f;

	sf::Vector2f _attackLocation = sf::Vector2f(162, 76);
	
	ZEngine::Timer damageTimer;

	ZEngine::Animation* _curAnim;

	ZEngine::Animation _idleAnim;
	ZEngine::Animation _walkAnim;
	ZEngine::Animation _hitAnim;
	ZEngine::Animation _windUpAnim;
	ZEngine::Animation _attackAnim;
	ZEngine::Animation _dashAnim;
	ZEngine::Animation _dyingAnim;

	void UpdateState();
	void UpdateAnimations();

	void FlipSprite();

};

