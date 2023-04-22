#include "EquipmentState.h"
#include "Attack.h"

EquipmentState::~EquipmentState()
{
}

void EquipmentState::Enter(Player& InPlayer)
{
	PlayerState::Enter(InPlayer);
	m_EquipmentType = EEquipmentType::ET_None;
}

void EquipmentState::Exit(Player& InPlayer)
{
}

void EquipmentState::Update(float dT, Player& InPlayer)
{
}

PlayerState* EquipmentState::HandleInput(Player& InPlayer, sf::Event* InputEvent)
{
	return nullptr;
}
//
//Attack* EquipmentState::GetCurrentSequenceItem()
//{
//	return nullptr;
//}
//
