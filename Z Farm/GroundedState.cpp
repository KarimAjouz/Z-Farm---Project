#include "GroundedState.h"
#include "Player.h"
#include "JumpingState.h"
#include "PlayerPhysicsComponent.h"

GroundedState::~GroundedState()
{
}

void GroundedState::Update(float dT, Player& InPlayer)
{
    TraversalState::Update(dT, InPlayer);

    if (
        InPlayer.GetPhysicsComponent()->GetVelocity().x > 0.0f && InPlayer.isFlipped ||
        InPlayer.GetPhysicsComponent()->GetVelocity().x < 0.0f && !InPlayer.isFlipped
       )
    {
        InPlayer.FlipSprite();
    }


}

PlayerState* GroundedState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
    sf::Vector2f newInputAxis = InPlayer.GetInputAxis();

    switch (InEvent->type)
    {
    
    default:
        break;
    }

    switch (InEvent->type)
    {
    case sf::Event::EventType::KeyPressed:
        switch (InEvent->key.code)
        {
        case sf::Keyboard::Space:
            if (InPlayer.Jump())
            {
                return new JumpingState;
            }
            break;
        default:
            break;
        }
    }

	return TraversalState::HandleInput(InPlayer, InEvent);
}

void GroundedState::Enter(Player& InPlayer)
{
    TraversalState::Enter(InPlayer);
    if (!InPlayer.GetPhysicsComponent())
    {
        return;
    }

    if (InPlayer.GetPhysicsComponent()->GetVelocity().y < 0.0f)
    {
        m_isLanding = true;
        InPlayer.GetAnimationComponent()->SetAnimation("PlayerLand");
        InPlayer.GetAnimationComponent()->Play();
    }
}

void GroundedState::Exit(Player& InPlayer)
{
}
