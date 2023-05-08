#pragma once
#include "Game.h"
#include "Agent.h"
#include "box2d.h"

class Equippable
{
public:
	Equippable();

	virtual void EquipItem(ZEngine::Agent& InOwningAgent);
	virtual void UnequipItem(ZEngine::Agent& InOwningAgent);

	virtual class EquipmentState* GetEquipmentState();

protected:
};

