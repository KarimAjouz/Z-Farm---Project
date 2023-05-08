#pragma once
#include "EquipmentState.h"

class SwordState
	:
	public EquipmentState
{
public:
	virtual ~SwordState() override;
	virtual void Enter(Player& InPlayer) override;
	virtual void Exit(Player& InPlayer) override;

	virtual void Update(float dT, Player& InPlayer) override;
	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InputEvent) override;
	virtual void FlipEquipment() override;
};
