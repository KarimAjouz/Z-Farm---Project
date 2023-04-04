#pragma once

#include "TraversalState.h"

class InAirState
	:
	public TraversalState
{
public:
	virtual ~InAirState();
	virtual void Update(float dT, Player& InPlayer) override;

	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InEvent) override;
};

