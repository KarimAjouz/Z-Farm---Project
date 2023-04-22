#pragma once

#include "PlayerState.h"
#include "SwordItem.h"

enum EEquipmentType
{
	ET_None,
	ET_Sword,
	ET_Gun,
	ET_Count
};

class EquipmentState 
	: 
	public PlayerState
{
public:

	virtual ~EquipmentState() override;
	virtual void Enter(Player& InPlayer) override;
	virtual void Exit(Player& InPlayer) override;


	virtual void Update(float dT, Player& InPlayer) override;
	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InputEvent) override;

	virtual EEquipmentType GetEquipmentType() { return m_EquipmentType; }
	virtual void FlipEquipment() {};

	SwordItem* GetItem() { return m_Item; };

protected:
	EEquipmentType m_EquipmentType = EEquipmentType::ET_None;

	SwordItem* m_Item = nullptr;

};

