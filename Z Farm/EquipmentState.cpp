#include "EquipmentState.h"

void EquipmentState::Enter(Player& InPlayer)
{
	PlayerState::Enter(InPlayer);
	m_EquipmentType = EEquipmentType::ET_None;
}

