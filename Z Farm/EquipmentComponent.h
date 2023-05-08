#pragma once
#include "ObjectComponent.h"
#include "Agent.h"


class EquipmentComponent :
    public ZEngine::ObjectComponent
{
public:
    EquipmentComponent(ZEngine::GameDataRef InData, int InMaxEquippables);
    ~EquipmentComponent();

    virtual void Init() override;
    virtual void Update(float dT) override;
    virtual void Draw(sf::RenderWindow* InWindow) override;


    bool AddEquipment(class Equippable* InEquippable);

    void EquipNext(ZEngine::Agent& InAgentRef);
    void EquipPrevious(ZEngine::Agent& InAgentRef);

    class Equippable* GetEquippedItem() { return m_Equipment.at(m_EquippedIndex); }

protected:

    std::vector<class Equippable*> m_Equipment;
    int m_EquippedIndex = -1;

    int m_MaxEquippables = 1;


};

