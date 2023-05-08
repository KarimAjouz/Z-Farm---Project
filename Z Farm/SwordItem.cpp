#include "SwordItem.h"
#include "Attack.h"
#include "PlayerPhysicsComponent.h"
#include "EquipmentComponent.h"
#include "Player.h"
#include "Agent.h"
#include "SwordState.h"

#include <iostream>

SwordItem::SwordItem()
{
}

SwordItem::~SwordItem()
{
}

void SwordItem::EquipItem(ZEngine::Agent& InOwningAgent)
{
	Player& PlayerRef = dynamic_cast<Player&>(InOwningAgent);

	if (PlayerRef.GetEquipmentComponent() != nullptr)
	{
		PlayerRef.SetEquipmentState(new SwordState());
	}

	GenerateAttacks(InOwningAgent);
}

void SwordItem::UnequipItem(ZEngine::Agent& InOwningAgent)
{
	for (Attack* attack : m_AtackSequence)
	{
		delete attack;
	}
	m_AtackSequence.clear();
}

void SwordItem::GenerateAttacks(ZEngine::Agent& InOwningAgent)
{
	if (!m_AtackSequence.empty())
	{
		std::cout << "Warning: SwordItem::GenerateAttacks --> GenerateAttacks called while m_AttackSequence is populated!" << std::endl;
		return;
	}

	sf::Vector2f OwningPosition = InOwningAgent.GetSprite()->getPosition();
	m_AtackSequence.push_back(new Attack(InOwningAgent.GetData(), InOwningAgent.GetWorldRef(), sf::IntRect(50, 8, 14, 6), InOwningAgent, "PlayerStab", 0.1f));
	m_AtackSequence.push_back(new Attack(InOwningAgent.GetData(), InOwningAgent.GetWorldRef(), sf::IntRect(46, -16, 10, 20), InOwningAgent, "PlayerUpSlash", 0.1f));
	m_AtackSequence.push_back(new Attack(InOwningAgent.GetData(), InOwningAgent.GetWorldRef(), sf::IntRect(47, 20, 9, 18), InOwningAgent, "PlayerDownSlash", 0.1f));

	Player& PlayerRef = dynamic_cast<Player&>(InOwningAgent);

	if (PlayerRef.GetEquipmentState() != nullptr && PlayerRef.isFlipped)
	{
		PlayerRef.GetEquipmentState()->FlipEquipment();
	}
}