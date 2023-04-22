#pragma once
#include "Equippable.h"
#include <vector>

class SwordItem :
    public Equippable
{
public:
    SwordItem(class Player& InPlayer);
    ~SwordItem();

    void EquipItem(Player& InPlayer);
    void UnequipItem();

    void GenerateAttacks(class Player& InPlayer);
    std::vector<class Attack*>* GetAttackSequence() { return &m_AtackSequence; }

private:
    std::vector<class Attack*> m_AtackSequence;
};

