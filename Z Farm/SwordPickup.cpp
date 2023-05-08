#include "SwordPickup.h"
#include "Definitions.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Agent.h"
#include "EquipmentComponent.h"
#include "SwordItem.h"

#include <iostream>

SwordPickup::SwordPickup(ZEngine::GameDataRef InData, sf::Vector2f InPosition, b2World* InWorldRef, float InRotation)
	:
	Pickup(InData, InPosition, InWorldRef)
{
	m_Data->assetManager.LoadTexture("Sword", SWORD_ITEM);
	m_Sprite = sf::Sprite();
	m_Sprite.setTexture(m_Data->assetManager.GetTexture("Sword"));
	m_Sprite.setOrigin(3.5f, 10.5f);
	m_Sprite.setPosition(InPosition);
	m_Sprite.setRotation(InRotation);
	m_Sprite.setScale(2.0f, 2.0f);

	m_Hitbox.setPosition(m_Sprite.getPosition());
	m_Hitbox.setSize(sf::Vector2f(7, 11) * m_Sprite.getScale().x);
	m_Hitbox.setOrigin(3.5f, 10.5f);
	m_Hitbox.setScale(m_Sprite.getScale());

	m_Type = Pickup::Type::PT_Equipment;

	m_PhysicsComponent->MakeAsBoxBody(
		InPosition,
		sf::IntRect(0, 0, m_Hitbox.getSize().x, m_Hitbox.getSize().y),
		nullptr,
		false,
		true,
		EEntityCategory::INTERACTABLE,
		EEntityCategory::INTERACTOR
	);

	m_PhysicsComponent->SetBodyUserData(this, ECollisionTag::CT_Interactable);
}

SwordPickup::~SwordPickup()
{
}

void SwordPickup::Collect(ZEngine::Agent* InInteractingAgent)
{
	SwordItem* newSword = new SwordItem();

	EquipmentComponent* EquipmentComponent = InInteractingAgent->GetEquipmentComponent();

	if (EquipmentComponent == nullptr)
	{
		std::cout << "WARNING: SwordPickup::Collect --> InteractingAgent has no EquipmentComponent!" << std::endl;
		return;
	}

	if (EquipmentComponent->AddEquipment(newSword))
	{
		return;
	}

	delete newSword;
}