#pragma once
#include "GroundedState.h"
class MovingState :
	public GroundedState
{
public:
	virtual ~MovingState();
	virtual void Update(float dT, Player& InPlayer) override;
	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InEvent) override;

	virtual void Enter(Player& InPlayer) override;
	//virtual void Exit(Player& InPlayer) override;
};
