#include "MovingState.h"

#include "IdleState.h"
#include "Player.h"
#include "PlayerPhysicsComponent.h"

MovingState::~MovingState()
{
}

void MovingState::Update(float dT, Player& InPlayer)
{
    GroundedState::Update(dT, InPlayer);

    if (InPlayer.GetInputAxis().x == 0.0f)
    {
        InPlayer.SetTraversalState(new IdleState);
    }

    if (
        InPlayer.GetPhysicsComponent()->GetVelocity().x > 0.0f && InPlayer.isFlipped ||
        InPlayer.GetPhysicsComponent()->GetVelocity().x < 0.0f && !InPlayer.isFlipped
        )
    {
        InPlayer.FlipSprite();
    }
}

PlayerState* MovingState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
	return GroundedState::HandleInput(InPlayer, InEvent);
}

void MovingState::Enter(Player& InPlayer)
{
    GroundedState::Enter(InPlayer);
    m_TraversalType = ETraversalType::TT_Run;
    m_StateName = "TT_Moving";

}
