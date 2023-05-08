#include "PhysicsComponent.h"
#include "Agent.h"

#include <iostream>

PhysicsComponent::PhysicsComponent(ZEngine::GameDataRef InData, b2World* InWorldRef) :
	ObjectComponent(InData),
	m_WorldRef(InWorldRef),
	m_PhysicsBody(),
	m_UserData(new PhysicsUserData())
{
	if (!m_WorldRef)
	{
		std::cout << "ERROR: PhysicsComponent::PhysicsComponent() --> InWorldRef is invalid!" << std::endl;
	}

	Init();
}

PhysicsComponent::~PhysicsComponent()
{
	if (!bIsFixture)
		m_WorldRef->DestroyBody(m_PhysicsBody);
	else
		m_PhysicsBody->DestroyFixture(m_PhysicsFixture);

	delete m_UserData;
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

void PhysicsComponent::SetBodyUserData(ZEngine::GameObject* InGameObject, ECollisionTag InCollisionTag)
{
	if (m_UserData)
		delete m_UserData;

	m_UserData = new PhysicsUserData(InGameObject, InCollisionTag);

	m_PhysicsBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(m_UserData);

	for (b2Fixture* fixture = m_PhysicsBody->GetFixtureList(); fixture; fixture = m_PhysicsBody->GetFixtureList()->GetNext())
	{
		fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(m_UserData);
	}
}

void PhysicsComponent::SetFixtureUserData(ZEngine::GameObject* InGameObject, ECollisionTag InCollisionTag)
{
	if (m_UserData)
		delete m_UserData;

	m_UserData = new PhysicsUserData(InGameObject, InCollisionTag);

	m_PhysicsFixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(m_UserData);
}

void PhysicsComponent::MakeAsBoxBody(sf::Vector2f InPos, sf::IntRect InCollisionBox, PhysicsComponent* InAttachedBody, bool InIsDynamic, bool InIsSensor, uint16 InPhysicsCategory, uint16 InCollidingCategories)
{
	bIsFixture = false;

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(InPos.x / SCALE, InPos.y / SCALE);

	if (InIsDynamic)
		bodyDef.type = b2_dynamicBody;
	else if (!InIsDynamic)
		bodyDef.type = b2_staticBody;

	if (InAttachedBody)
	{
		m_PhysicsBody = InAttachedBody->GetBody();
	}
	else
	{
		m_PhysicsBody = m_WorldRef->CreateBody(&bodyDef);
	}

	//Define, set, and add the primary fixture for the spike
	b2PolygonShape fixtureShape;
	fixtureShape.SetAsBox(InCollisionBox.width / SCALE, InCollisionBox.height / SCALE);
	b2FixtureDef myFixtureDef;

	if (InIsSensor)
	{
		myFixtureDef.isSensor = true;
	}
	else
	{
		myFixtureDef.isSensor = false;
	}

	myFixtureDef.density = 1.0f;

	myFixtureDef.filter.categoryBits = InPhysicsCategory;
	myFixtureDef.filter.maskBits = InCollidingCategories;

	myFixtureDef.shape = &fixtureShape;
	b2Fixture* mainFixture = m_PhysicsBody->CreateFixture(&myFixtureDef);

}

void PhysicsComponent::MakeAsBoxFixture(sf::Vector2f InPos, sf::IntRect InCollisionBox, PhysicsComponent* InAttachedBody, bool InIsDynamic, bool InIsSensor, uint16 InPhysicsCategory, uint16 InCollidingCategories)
{
	bIsFixture = true;

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(InPos.x / SCALE, InPos.y / SCALE);

	if (InIsDynamic)
		bodyDef.type = b2_dynamicBody;
	else if (!InIsDynamic)
		bodyDef.type = b2_staticBody;

	if (InAttachedBody)
	{
		m_PhysicsBody = InAttachedBody->GetBody();
	}
	else
	{
		m_PhysicsBody = m_WorldRef->CreateBody(&bodyDef);
	}

	//Define, set, and add the primary fixture for the spike
	b2PolygonShape fixtureShape;
	fixtureShape.SetAsBox(InCollisionBox.width / SCALE, InCollisionBox.height / SCALE, b2Vec2(InPos.x / SCALE, InPos.y / SCALE), 0.0f);
	b2FixtureDef myFixtureDef;

	if (InIsSensor)
	{
		myFixtureDef.isSensor = true;
	}
	else
	{
		myFixtureDef.isSensor = false;
	}

	myFixtureDef.density = 1.0f;

	myFixtureDef.filter.categoryBits = InPhysicsCategory;
	myFixtureDef.filter.maskBits = InCollidingCategories;

	myFixtureDef.shape = &fixtureShape;
	m_PhysicsFixture = m_PhysicsBody->CreateFixture(&myFixtureDef);
}
