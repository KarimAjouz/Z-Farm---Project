#pragma once
#include "Agent.h"
#include "Game.h"
#include "Gun.h"
#include "SaveDataManager.h"
#include "Timer.h"
#include "AnimationSystem.h"

#include <box2d.h>

#include <SFML/Graphics.hpp>

class Player : public Agent
{
public:
	Player(sf::Vector2f pos, ZEngine::GameDataRef data, BalanceSheet* b, b2World* worldRef);
	~Player();

	void Update(float dT);
	void Draw();

private:
	enum State
	{
		idle,
		running,
		jumping,
		falling,
		windUp,
		attack,
		hit,
		dying
	};

	b2Vec2 _wasd = b2Vec2();
	int forceMult = 5;
	State _state;
	ZEngine::GameDataRef _data;
	
	ZEngine::AnimationSystem _animSystem = ZEngine::AnimationSystem(&sprite, _data);
	sf::IntRect _colBox = sf::IntRect(25, 16, 14, 16);

	b2Body* _playerBody = nullptr;


	void HandleInputs();
	void UpdatePhysics();
	
	void UpdateState();
	void UpdateAnimations(float dT);

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos, b2World* worldRef);


};

