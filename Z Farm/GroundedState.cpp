#include "GroundedState.h"
#include "Player.h"
#include "JumpingState.h"
#include "LandingState.h"
#include "AttackState.h"
#include "EquipmentState.h"
#include "PlayerPhysicsComponent.h"

GroundedState::~GroundedState()
{
}

void GroundedState::Update(float dT, Player& InPlayer)
{
    TraversalState::Update(dT, InPlayer);


}

PlayerState* GroundedState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{

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
        break;
    case sf::Event::EventType::MouseButtonPressed:
        if (InEvent->mouseButton.button == sf::Mouse::Button::Left)
        {
            if(InPlayer.GetEquipmentState()->GetEquipmentType() == EEquipmentType::ET_Sword)
                return new AttackState;
        }
        break;
    default:
        break;
    }

	return TraversalState::HandleInput(InPlayer, InEvent);
}

void GroundedState::Enter(Player& InPlayer)
{
    TraversalState::Enter(InPlayer);
}

void GroundedState::Exit(Player& InPlayer)
{
}
