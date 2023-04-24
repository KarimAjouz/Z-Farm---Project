#include "SwordItem.h"
#include "Attack.h"
#include "PlayerPhysicsComponent.h"
#include "Player.h"

#include <iostream>

SwordItem::SwordItem(Player& InPlayer)
{
	EquipItem(InPlayer);
}

SwordItem::~SwordItem()
{
}

void SwordItem::EquipItem(Player& InPlayer)
{
	GenerateAttacks(InPlayer);
}

void SwordItem::UnequipItem()
{
	for (Attack* attack : m_AtackSequence)
	{
		delete attack;
	}
	m_AtackSequence.clear();
}

void SwordItem::GenerateAttacks(Player& InPlayer)
{
	if (!m_AtackSequence.empty())
	{
		std::cout << "Warning: SwordItem::GenerateAttacks --> GenerateAttacks called while m_AttackSequence is populated!" << std::endl;
		return;
	}

	sf::Vector2f playerPosition = InPlayer.GetSprite()->getPosition();
	m_AtackSequence.push_back(new Attack(InPlayer.GetData(), InPlayer.GetWorldRef(), sf::IntRect(50, 8, 14, 6), InPlayer, "PlayerStab", 0.1f));
	m_AtackSequence.push_back(new Attack(InPlayer.GetData(), InPlayer.GetWorldRef(), sf::IntRect(46, -16, 10, 20), InPlayer, "PlayerUpSlash", 0.1f));
	m_AtackSequence.push_back(new Attack(InPlayer.GetData(), InPlayer.GetWorldRef(), sf::IntRect(47, 20, 9, 18), InPlayer, "PlayerDownSlash", 0.1f));
}
