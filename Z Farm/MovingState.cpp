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

    if (m_isLanding && InPlayer.GetAnimationComponent()->Complete())
    {
        InPlayer.GetAnimationComponent()->SetAnimation("PlayerRun");
        InPlayer.GetAnimationComponent()->Play();
        m_isLanding = false;
    }

    if (InPlayer.GetInputAxis().x == 0.0f)
    {
        InPlayer.SetTraversalState(new IdleState);
    }
}

PlayerState* MovingState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
	return GroundedState::HandleInput(InPlayer, InEvent);
}

void MovingState::Enter(Player& InPlayer)
{
    GroundedState::Enter(InPlayer);

    if (!m_isLanding)
    {
        InPlayer.GetAnimationComponent()->SetAnimation("PlayerRun");
        InPlayer.GetAnimationComponent()->Play();
    }
    m_StateName = "PS_Moving";
}
