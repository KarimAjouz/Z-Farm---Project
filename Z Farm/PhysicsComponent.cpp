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
	m_WorldRef->DestroyBody(m_PhysicsBody);
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

void PhysicsComponent::SetBodyUserData(ZEngine::GameObject* InGameObject)
{
	/*BodyUserData data = BodyUserData(InGameObject);
	m_UserData = data;

	m_PhysicsBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(&m_UserData);*/


}

void PhysicsComponent::MakeAsBoxBody(sf::Vector2f InPos, sf::IntRect InCollisionBox, bool InIsDynamic, ZEngine::GameObject* InGameObject)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((InPos.x + InCollisionBox.left) / SCALE, (InPos.y + InCollisionBox.top) / SCALE);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(InGameObject);

	if (InIsDynamic)
		bodyDef.type = b2_dynamicBody;
	else if (!InIsDynamic)
		bodyDef.type = b2_staticBody;

	m_PhysicsBody = m_WorldRef->CreateBody(&bodyDef);

	//Define, set, and add the primary fixture for the spike
	b2PolygonShape fixtureShape;
	fixtureShape.SetAsBox(InCollisionBox.width / SCALE, InCollisionBox.height / SCALE);
	b2FixtureDef myFixtureDef;

	//if (collider)
	//{

	myFixtureDef.density = 1.0f;
	myFixtureDef.isSensor = false;

	myFixtureDef.filter.categoryBits = EEntityCategory::OBSTACLES;
	myFixtureDef.filter.maskBits = 
		  EEntityCategory::LEVEL 
		| EEntityCategory::OBSTACLES 
		| EEntityCategory::AGENTS 
		| EEntityCategory::DAMAGE 
		| EEntityCategory::INTERACTOR;
	

	//}
	//else
	//{
	//	myFixtureDef.isSensor = true;
	//}

	myFixtureDef.shape = &fixtureShape;
	b2Fixture* mainFixture = m_PhysicsBody->CreateFixture(&myFixtureDef);
	mainFixture->GetUserData().pointer = static_cast<int>(ECollisionTag::box);

}
