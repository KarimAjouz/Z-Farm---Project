#pragma once
#include "Agent.h"
#include "Game.h"
#include "Gun.h"
#include "SaveDataManager.h"
#include "Timer.h"
#include "AnimationSystem.h"
#include "Level.h"
#include "Timer.h"

#include <box2d.h>

#include <SFML/Graphics.hpp>

class Player : public Agent
{
public:
	Player(sf::Vector2f pos, ZEngine::GameDataRef data, BalanceSheet* b, b2World* worldRef, sf::Vector2f* viewTargetRef, Level* levelRef);
	~Player();

	void Update(float dT);
	void Draw();


	int footContacts = 0;

	void SetView();

	void Hit();
	void EquipSword();

	void Stab();
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

	bool _swordActive = false;

	b2World* _worldRef;
	sf::Vector2i _wasd = sf::Vector2i();
	float _desiredVelocity = 0;
	

	ZEngine::Timer _stabDelay;

	int forceMult = 5;
	State _state;
	ZEngine::GameDataRef _data;
	
	ZEngine::AnimationSystem _animSystem = ZEngine::AnimationSystem(&sprite, _data);
	sf::IntRect _colBox = sf::IntRect(25, 16, 18, 12);

	sf::RectangleShape _lStab = sf::RectangleShape(sf::Vector2f(24, 12));
	sf::RectangleShape _rStab = sf::RectangleShape(sf::Vector2f(24, 12));


	sf::Vector2f* _viewTargetRef;
	Level* _levelRef;

	b2Body* _playerBody = nullptr;
	b2Fixture* _footFixture = nullptr;
	int _jumpTimeout = 0;
	bool _jumping = false;

	void HandleInputs();
	void UpdatePhysics();
	
	void UpdateState();
	void UpdateAnimations(float dT);

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos);

	void TestStab();


};

