#include "LandingState.h"
#include "MovingState.h"
#include "IdleState.h"
#include "Player.h"

PlayerState* LandingState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
	return GroundedState::HandleInput(InPlayer, InEvent);
}

void LandingState::Update(float dT, Player& InPlayer)
{
	GroundedState::Update(dT, InPlayer);
	if (InPlayer.GetAnimationComponent()->Complete())
	{
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

void LandingState::Enter(Player& InPlayer)
{
	GroundedState::Enter(InPlayer);
	m_TraversalType = ETraversalType::TT_Land;
	m_StateName = "TT_Landing";
}

void LandingState::Exit(Player& InPlayer)
{
}
