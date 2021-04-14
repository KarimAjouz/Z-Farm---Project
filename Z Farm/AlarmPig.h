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
private:
	ZEngine::GameDataRef _data;
	b2World* _worldRef;

	enum class State
	{
		idle,
		hit,
		alarmed
	};

	State _state;

	void UpdateAnimations();
	void UpdateState();

	b2Body* _body = nullptr;

	ZEngine::AnimationSystem _animSys;
	


	void DestroyPig();

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos);

	bool CanSeePlayer();

};

