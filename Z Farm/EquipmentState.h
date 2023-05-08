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

	EquipmentState();
	virtual ~EquipmentState() override;
	virtual void Enter(Player& InPlayer) override;
	virtual void Exit(Player& InPlayer) override;


	virtual void Update(float dT, Player& InPlayer) override;
	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InputEvent) override;

	virtual EEquipmentType GetEquipmentType() { return m_EquipmentType; }
	virtual void FlipEquipment() {};


protected:
	EEquipmentType m_EquipmentType = EEquipmentType::ET_None;

	Equippable* m_Item = nullptr;

};

