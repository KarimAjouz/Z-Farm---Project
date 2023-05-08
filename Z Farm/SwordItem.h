#pragma once
#include "Equippable.h"
#include "Agent.h"

#include <vector>

class SwordItem :
	public Equippable
{
public:
	SwordItem();
	~SwordItem();

	virtual void EquipItem(ZEngine::Agent& InOwningAgent) override;
	virtual void UnequipItem(ZEngine::Agent& InOwningAgent) override;

	void GenerateAttacks(ZEngine::Agent& InOwningAgent);
	std::vector<class Attack*>* GetAttackSequence() { return &m_AtackSequence; }

private:
	std::vector<class Attack*> m_AtackSequence;
};
