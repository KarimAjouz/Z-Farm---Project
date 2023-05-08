#include "InAirState.h"

InAirState::~InAirState()
{
}

void InAirState::Update(float dT, Player& InPlayer)
{
	TraversalState::Update(dT, InPlayer);
}

PlayerState* InAirState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
	return nullptr;
}