#include "IdleState.h"

#include "Player.h"
#include "MovingState.h"
#include "EquipmentState.h"

IdleState::~IdleState()
{
}

void IdleState::Update(float dT, Player& InPlayer)
{
	GroundedState::Update(dT, InPlayer);

	float InputAxis = InPlayer.GetInputAxis().x;
	if (InputAxis != 0.0f)
	{
		InPlayer.SetTraversalState(new MovingState);
	}
}

PlayerState* IdleState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
	return GroundedState::HandleInput(InPlayer, InEvent);
}

void IdleState::Enter(Player& InPlayer)
{
	GroundedState::Enter(InPlayer);
	m_TraversalType = ETraversalType::TT_Idle;

	m_StateName = "PS_Idle";
}

void IdleState::Exit(Player& InPlayer)
{
}