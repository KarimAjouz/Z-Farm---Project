#include "JumpingState.h"
#include "Player.h"
#include "PlayerPhysicsComponent.h"

#include "FallingState.h"

JumpingState::~JumpingState()
{
}

void JumpingState::Update(float dT, Player& InPlayer)
{
	InAirState::Update(dT, InPlayer);

	if (m_JumpboostTimer > 0.0f)
	{
		AddJumpForceToPlayer(InPlayer);
		m_JumpboostTimer -= dT;
	}

	float yVel = InPlayer.GetPhysicsComponent()->GetVelocity().y;
	if (yVel < 7.0f)
	{
		InPlayer.GetPhysicsComponent()->GetBody()->SetGravityScale(3.0f);
	}
	if (yVel < 0.0f)
	{
		InPlayer.SetTraversalState(new FallingState);
	}
}

PlayerState* JumpingState::HandleInput(Player& InPlayer, sf::Event* InEvent)
{
	switch (InEvent->type)
	{
	case sf::Event::EventType::KeyReleased:
		switch (InEvent->key.code)
		{
		case sf::Keyboard::Space:
			m_JumpboostTimer = 0.0f;
			break;
		}
		break;
	}

	return nullptr;
}

void JumpingState::Enter(Player& InPlayer)
{
	InAirState::Enter(InPlayer);
	AddJumpForceToPlayer(InPlayer);
	m_TraversalType = ETraversalType::TT_Jump;

	m_StateName = "TT_Jumping";
	m_JumpboostTimer = m_JumpboostTimeMax;
}

void JumpingState::AddJumpForceToPlayer(Player& InPlayer)
{
	InPlayer.GetPhysicsComponent()->Jump();
}