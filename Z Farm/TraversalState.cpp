#include "TraversalState.h"

#include "Player.h"
#include "PlayerPhysicsComponent.h"

TraversalState::~TraversalState()
{
}

PlayerState* TraversalState::HandleInput(Player& InPlayer, sf::Event* InputEvent)
{
	return nullptr;
}

void TraversalState::Update(float dT, Player& InPlayer)
{
	InPlayer.GetPhysicsComponent()->Move();
}

void TraversalState::Enter(Player& InPlayer)
{
}

void TraversalState::Exit(Player& InPlayer)
{
}
