#include "FallingState.h"
#include "Player.h"
#include "LandingState.h"
#include "MovingState.h"
#include "PlayerPhysicsComponent.h"

FallingState::~FallingState()
{
}

void FallingState::Update(float dT, Player& InPlayer)
{
	InAirState::Update(dT, InPlayer);

	if (InPlayer.footContacts > 0)
	{
		InPlayer.GetPhysicsComponent()->GetBody()->SetGravityScale(1.0f);
		InPlayer.SetTraversalState(new LandingState);
	}
}

PlayerState* FallingState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
	return nullptr;
}

void FallingState::Enter(Player& InPlayer)
{
	//AddJumpForceToPlayer(InPlayer);
	m_TraversalType = ETraversalType::TT_Fall;
	m_StateName = "TT_Falling";
}