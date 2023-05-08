#pragma once

#include "PlayerState.h"

enum ETraversalType
{
	TT_Idle,
	TT_Run,
	TT_Jump,
	TT_Fall,
	TT_Land,
	TT_Attack,
	TT_Count
};

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

	ETraversalType GetTraversalType() { return m_TraversalType; }
protected:
	ETraversalType m_TraversalType = ETraversalType::TT_Idle;
};
