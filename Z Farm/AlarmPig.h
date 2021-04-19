#pragma once

#include "Agent.h"
#include "AnimationSystem.h"


class AlarmPig : public Agent
{
public:
	AlarmPig(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f pos);
	~AlarmPig();

	void Update(float dT);
	void Draw();

	void Hit();
	void Hit(sf::Vector2f playerPos);
private:
	ZEngine::GameDataRef _data;

	enum class State
	{
		idle,
		hit,
		alarmed
	};

	State _state;

	void UpdateAnimations();
	void UpdateState();


	ZEngine::AnimationSystem _animSys;
	
	sf::RectangleShape line = sf::RectangleShape(sf::Vector2f(150.0f, 5.0f));


	void DestroyPig();

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos);

	bool CanSeePlayer();

};

