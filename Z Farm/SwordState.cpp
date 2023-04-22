#include "SwordState.h"
#include "Player.h"
#include "Attack.h"
#include "AttackState.h"
#include "SwordItem.h"
#include <vector>

SwordState::~SwordState()
{
	delete m_Item;
}

void SwordState::Enter(Player& InPlayer)
{
	m_EquipmentType = EEquipmentType::ET_Sword;
	m_Item = new SwordItem(InPlayer);
}

void SwordState::Exit(Player& InPlayer)
{
}

void SwordState::Update(float dT, Player& InPlayer)
{
}

PlayerState* SwordState::HandleInput(Player& InPlayer, sf::Event* InputEvent)
{
	if (InPlayer.GetTraversalState()->GetTraversalType() == ETraversalType::TT_Attack)
	{
		return EquipmentState::HandleInput(InPlayer, InputEvent);
	}

	switch (InputEvent->type)
	{
	case sf::Event::MouseButtonPressed:
		if (InputEvent->mouseButton.button == sf::Mouse::Left)
		{
			InPlayer.SetTraversalState(new AttackState);
		}
		break;
	default:
		break;
	}
	return EquipmentState::HandleInput(InPlayer, InputEvent);
}

void SwordState::FlipEquipment()
{
	if (m_Item == nullptr)
	{
		return;
	}
	std::vector<Attack*>* attackSeq = m_Item->GetAttackSequence();
	for (std::vector<Attack*>::iterator it = attackSeq->begin(); it != attackSeq->end(); it++)
	{
		Attack* attack = (*it);
		if (attack == nullptr)
			return;

		attack->FlipFixture();
	}
}
