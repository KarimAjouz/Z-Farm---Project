#pragma once
#include "InAirState.h"
class FallingState :
	public InAirState
{
public:
	virtual ~FallingState();
	virtual void Update(float dT, Player& InPlayer) override;

	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InEvent) override;
	virtual void Enter(Player& InPlayer) override;
};
