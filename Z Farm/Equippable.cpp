#include "Equippable.h"
#include "EquipmentState.h"
#include "Player.h"

Equippable::Equippable()
{
}

void Equippable::EquipItem(ZEngine::Agent& InOwningAgent)
{
	Player& PlayerRef = dynamic_cast<Player&>(InOwningAgent);

	if (PlayerRef.GetEquipmentComponent() != nullptr)
	{
		PlayerRef.SetEquipmentState(new EquipmentState());
	}
}

void Equippable::UnequipItem(ZEngine::Agent& InOwningAgent)
{
}


EquipmentState* Equippable::GetEquipmentState()
{
	return new EquipmentState();
}
