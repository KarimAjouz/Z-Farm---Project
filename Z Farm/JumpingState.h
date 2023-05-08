#pragma once

#include "InAirState.h"

class JumpingState
	:
	public InAirState
{
public:
	virtual ~JumpingState();
	virtual void Update(float dT, Player& InPlayer) override;
	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InEvent) override;

	virtual void Enter(Player& InPlayer) override;
	//virtual void Exit(Player& InPlayer) override;

private:
	const float m_JumpboostTimeMax = 0.25f;
	float m_JumpboostTimer = 0.0f;

	void AddJumpForceToPlayer(Player& InPlayer);
};
