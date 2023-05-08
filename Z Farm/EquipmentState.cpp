#include "EquipmentState.h"
#include "Attack.h"
#include "Player.h"
#include "EquipmentComponent.h"


EquipmentState::EquipmentState()
{
}

EquipmentState::~EquipmentState()
{
}

void EquipmentState::Enter(Player& InPlayer)
{
	PlayerState::Enter(InPlayer);
	m_EquipmentType = EEquipmentType::ET_None;

	m_Item = dynamic_cast<Equippable*>(InPlayer.GetEquipmentComponent()->GetEquippedItem());

	if (m_Item == nullptr)
	{
		std::cout << "WARNING: SwordState::Enter --> m_Item is Invalid!" << std::endl;
		return;
	}
}

void EquipmentState::Exit(Player& InPlayer)
{
}

void EquipmentState::Update(float dT, Player& InPlayer)
{
}

PlayerState* EquipmentState::HandleInput(Player& InPlayer, sf::Event* InputEvent)
{
	switch (InputEvent->type)
	{
	case sf::Event::MouseWheelScrolled:
		if (InputEvent->mouseWheelScroll.delta > 0)
		{
			InPlayer.GetEquipmentComponent()->EquipNext(InPlayer);
		}
		else
		{
			InPlayer.GetEquipmentComponent()->EquipPrevious(InPlayer);
		}
		break;
	default:
		break;
	}

	return nullptr;
}