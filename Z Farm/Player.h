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


	bool grounded = false;

private:
	enum class State
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

	b2World* _worldRef;
	sf::Vector2i _wasd = sf::Vector2i();
	float _desiredVelocity = 0;

	int forceMult = 5;
	State _state;
	ZEngine::GameDataRef _data;
	
	ZEngine::AnimationSystem _animSystem = ZEngine::AnimationSystem(&sprite, _data);
	sf::IntRect _colBox = sf::IntRect(25, 16, 12, 22);

	sf::RectangleShape debugRect = sf::RectangleShape();
	sf::RectangleShape footDebugShape = sf::RectangleShape();


	b2Body* _playerBody = nullptr;
	b2Fixture* _footFixture = nullptr;
	bool _jumping = false;

	void HandleInputs();
	void UpdatePhysics();
	
	void UpdateState();
	void UpdateAnimations(float dT);

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos, b2World* worldRef);


};

