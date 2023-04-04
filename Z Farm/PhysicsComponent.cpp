#include "PhysicsComponent.h"

#include <iostream>

PhysicsComponent::PhysicsComponent(ZEngine::GameDataRef InData, b2World* InWorldRef) :
	ObjectComponent(InData),
	m_WorldRef(InWorldRef),
	m_PhysicsBody(nullptr)
{
	if (!m_WorldRef)
	{
		std::cout << "ERROR: PhysicsComponent::PhysicsComponent() --> InWorldRef is invalid!" << std::endl;
	}

	Init();
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Init()
{
	ObjectComponent::Init();
	InitPhysics();
}

void PhysicsComponent::Update(float dT)
{
}

void PhysicsComponent::InitPhysics()
{
}
