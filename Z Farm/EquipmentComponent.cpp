#include "EquipmentComponent.h"
#include "Equippable.h"
#include "SwordItem.h"
#include "EquipmentState.h"
#include "Player.h"

#include <iostream>

EquipmentComponent::EquipmentComponent(ZEngine::GameDataRef InData, int InMaxEquippables)
	:
	ObjectComponent(InData),
	m_MaxEquippables(InMaxEquippables)
{
	AddEquipment(new Equippable());
	AddEquipment(new SwordItem());
	m_EquippedIndex = 0;
}

EquipmentComponent::~EquipmentComponent()
{
	for (int i = 0; i < m_Equipment.size(); i++)
	{
		m_Equipment.pop_back();
	}
}

void EquipmentComponent::Init()
{
	ObjectComponent::Init();
}

void EquipmentComponent::Update(float dT)
{
	ObjectComponent::Update(dT);
}

void EquipmentComponent::Draw(sf::RenderWindow* InWindow)
{
	ObjectComponent::Draw(InWindow);
}

bool EquipmentComponent::AddEquipment(Equippable* InEquippable)
{
	if (InEquippable == nullptr)
	{
		std::cout << "EquipmentComponent::AddEquipment --> InEquippable is invalid!" << std::endl;
		return false;
	}
	if (m_Equipment.size() < m_MaxEquippables)
	{
		m_Equipment.push_back(InEquippable);
		return true;
	}
	return false;
}

void EquipmentComponent::EquipNext(ZEngine::Agent& InAgentRef)
{
	if (m_Equipment.size() == 1)
	{
		return;
	}

	Player& PlayerRef = dynamic_cast<Player&>(InAgentRef);

	if (PlayerRef.GetEquipmentComponent() != nullptr)
	{
		m_Equipment.at(m_EquippedIndex)->UnequipItem(InAgentRef);

		m_EquippedIndex++;
		m_EquippedIndex = m_EquippedIndex % m_Equipment.size();

		m_Equipment.at(m_EquippedIndex)->EquipItem(InAgentRef);
	}
}

void EquipmentComponent::EquipPrevious(ZEngine::Agent& InAgentRef)
{
	if (m_Equipment.size() == 1)
	{
		return;
	}

	Player& PlayerRef = dynamic_cast<Player&>(InAgentRef);

	if (PlayerRef.GetEquipmentComponent() != nullptr)
	{
		m_Equipment.at(m_EquippedIndex)->UnequipItem(InAgentRef);
		m_EquippedIndex--;

		if (m_EquippedIndex < 0)
		{
			m_EquippedIndex += m_Equipment.size();
		}
		m_Equipment.at(m_EquippedIndex)->EquipItem(InAgentRef);
	}
}