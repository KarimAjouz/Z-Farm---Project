#include "FallingState.h"
#include "Player.h"
#include "IdleState.h"
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            InPlayer.SetTraversalState(new MovingState);
        }
        else
        {
            InPlayer.SetTraversalState(new IdleState);
        }
    }
}

PlayerState* FallingState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
   
    return nullptr;
}

void FallingState::Enter(Player& InPlayer)
{
    //AddJumpForceToPlayer(InPlayer);
    m_StateName = "PS_Falling";

    InPlayer.GetAnimationComponent()->SetAnimation("PlayerFall");
    InPlayer.GetAnimationComponent()->Play();

}