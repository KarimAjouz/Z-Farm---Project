#include "InteractableComponent.h"


using namespace ZEngine;
InteractableComponent::InteractableComponent(ZEngine::GameDataRef InData, b2World* InWorldRef)
	:
	PhysicsComponent(InData, InWorldRef),
	m_GameObject(nullptr),
	m_Radius(0.0f)
{
}

InteractableComponent::InteractableComponent(ZEngine::GameDataRef InData, b2World* InWorldRef, GameObject* InGameObject, float InRadius) 
	:
	InteractableComponent(InData, InWorldRef)
{
	m_GameObject = InGameObject;
	m_Radius = InRadius;
}

InteractableComponent::~InteractableComponent()
{
}

void InteractableComponent::Init()
{
	PhysicsComponent::Init();
}

void InteractableComponent::Update(float dT)
{
}

void InteractableComponent::InitPhysics()
{
	if (!m_GameObject)
	{
		return;
	}

	b2BodyDef bodyDefinition = b2BodyDef();
	bodyDefinition.position = b2Vec2(m_GameObject->GetSprite()->getPosition().x / SCALE, m_GameObject->GetSprite()->getPosition().y / SCALE);
	bodyDefinition.type = b2_dynamicBody;
	m_PhysicsBody = m_WorldRef->CreateBody(&bodyDefinition);

	b2CircleShape circleShape;
	circleShape.m_radius = m_Radius / SCALE;

	b2FixtureDef fixtureDefinition = b2FixtureDef();
	fixtureDefinition.isSensor = true;

	fixtureDefinition.filter.categoryBits = EEntityCategory::INTERACTABLE;
	fixtureDefinition.filter.maskBits = EEntityCategory::INTERACTOR;

	b2Fixture* interactableFixture = m_PhysicsBody->CreateFixture(&fixtureDefinition);
	interactableFixture->GetUserData().pointer = static_cast<int>(ECollisionTag::CT_Interactable);

}

void InteractableComponent::Interact()
{
}
