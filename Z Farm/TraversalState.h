#pragma once

#include "PlayerState.h"

class TraversalState
	:
	public PlayerState
{
public:

	virtual ~TraversalState();

	//virtual void Update(float dT, Player& InPlayer) override;

	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InputEvent) override;

	virtual void Update(float dT, Player& InPlayer) override;

	virtual void Enter(Player& InPlayer) override;
	virtual void Exit(Player& InPlayer) override;
};

