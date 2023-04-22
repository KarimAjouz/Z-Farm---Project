#include "AttackState.h"
#include "MovingState.h"
#include "IdleState.h"
#include "Player.h"
#include "Attack.h"
#include "EquipmentState.h"
#include "SwordItem.h"
#include "PlayerAnimationComponent.h"



void AttackState::Update(float dT, Player& InPlayer)
{
	if (InPlayer.GetAnimationComponent()->Complete())
	{
		m_SequenceIndex++;
		if (m_SequenceIndex < m_AttackSequence->size() && m_bIsNextAttackQueued)
		{
			InPlayer.GetAnimationComponent()->SetAnimation(m_AttackSequence->at(m_SequenceIndex)->GetAnimation());
			InPlayer.GetAnimationComponent()->Play();
			m_bIsNextAttackQueued = false;
		}
		else
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
	else
	{
		Attack* CurAttack = m_AttackSequence->at(m_SequenceIndex);

		if (m_RunningTime > CurAttack->GetDamageFrameTime())
		{
			CurAttack->CommitDamage();
		}
		m_RunningTime += dT;
	}


}

PlayerState* AttackState::HandleInput(Player& InPlayer, sf::Event* InputEvent)
{
	switch (InputEvent->type)
	{
	case sf::Event::MouseButtonPressed:
		if (InputEvent->mouseButton.button == sf::Mouse::Left)
		{
			m_bIsNextAttackQueued = true;
		}
		break;
	default:
		break;
	}
	return nullptr;
}

Attack* AttackState::GetCurrentSequenceItem()
{
	if(m_AttackSequence->size() > m_SequenceIndex)
		return m_AttackSequence->at(m_SequenceIndex); 

	return nullptr;
}

AttackState::~AttackState()
{
}

void AttackState::Enter(Player& InPlayer)
{
	TraversalState::Enter(InPlayer);
	m_TraversalType = ETraversalType::TT_Attack;
	m_StateName = "PS_Attack";
	m_SequenceIndex = 0;
	m_AttackSequence = InPlayer.GetEquipmentState()->GetItem()->GetAttackSequence();

	if (m_AttackSequence->size() == 0)
	{
		std::cout << "WARNING: AttackState::Enter --> m_AttackSequence has no members." << std::endl;
		return;
	}

	InPlayer.GetAnimationComponent()->SetAnimation(m_AttackSequence->at(m_SequenceIndex)->GetAnimation());
	InPlayer.GetAnimationComponent()->Play();
}

void AttackState::Exit(Player& InPlayer)
{
}
