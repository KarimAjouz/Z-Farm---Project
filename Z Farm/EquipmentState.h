#pragma once

#include "PlayerState.h"

enum class EEquipmentType
{
	ET_None,
	ET_Sword,
	ET_Gun,
	Count
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
private:
	EEquipmentType m_EquipmentType;
};

