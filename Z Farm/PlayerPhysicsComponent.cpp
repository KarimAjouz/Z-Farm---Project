#include "PlayerPhysicsComponent.h"
#include "Player.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(ZEngine::GameDataRef InData, b2World* InWorldRef)
	:
	PhysicsComponent(InData, InWorldRef),
	m_Player(nullptr)
{
}

PlayerPhysicsComponent::PlayerPhysicsComponent(ZEngine::GameDataRef InData, b2World* InWorldRef, Player* InPlayer)
	:
	PlayerPhysicsComponent(InData, InWorldRef)
{
	m_Player = InPlayer;
	InitPhysics();
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::Update(float dT)
{
	m_Player->GetSprite()->setPosition(m_PhysicsBody->GetPosition().x * SCALE, m_PhysicsBody->GetPosition().y * SCALE);

	b2Vec2 vel = m_PhysicsBody->GetLinearVelocity();
	float desiredVelocity = 0.0f;
	float xInput = m_Player->GetInputAxis().x;

	if (xInput == 0.0f)
	{
		desiredVelocity = vel.x * 0.95f;

		float velChange = desiredVelocity - vel.x;
		float impulse = m_PhysicsBody->GetMass() * velChange; //disregard time factor

		m_PhysicsBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_PhysicsBody->GetWorldCenter(), true);
	}

}

void PlayerPhysicsComponent::InitPhysics()
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(m_Player->GetSprite()->getPosition().x / SCALE, m_Player->GetSprite()->getPosition().y / SCALE);
	bodyDef.type = b2_dynamicBody;
	m_PhysicsBody = m_WorldRef->CreateBody(&bodyDef);
	m_PhysicsBody->SetFixedRotation(true);

	b2PolygonShape polygonShape;
	//polygonShape.SetAsBox(_colBox.width / SCALE, _colBox.height / SCALE);
	b2CircleShape circleShape;
	circleShape.m_radius = m_CollisionBox.width / SCALE;
	circleShape.m_p = b2Vec2(0, m_CollisionBox.height / 2 / SCALE);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;

	myFixtureDef.restitution = 0.1f;
	myFixtureDef.shape = &circleShape;

	myFixtureDef.filter.categoryBits = EEntityCategory::AGENTS;
	myFixtureDef.filter.maskBits = EEntityCategory::LEVEL | EEntityCategory::OBSTACLES | EEntityCategory::AGENTS | EEntityCategory::DAMAGE;

	b2Fixture* playerFixture = m_PhysicsBody->CreateFixture(&myFixtureDef);
	playerFixture->GetUserData().pointer = static_cast<int>(ECollisionTag::player);


	//add foot sensor fixture
	polygonShape.SetAsBox(10 / SCALE, 10 / SCALE, b2Vec2(0, (static_cast<float>(m_CollisionBox.height) * abs(m_Player->GetSprite()->getScale().y)) / SCALE), 0);
	myFixtureDef.isSensor = true;
	myFixtureDef.shape = &polygonShape;

	myFixtureDef.filter.categoryBits = EEntityCategory::INTERACTOR;
	myFixtureDef.filter.maskBits = EEntityCategory::LEVEL | EEntityCategory::INTERACTABLE | EEntityCategory::OBSTACLES;

	b2Fixture* footSensorFixture = m_PhysicsBody->CreateFixture(&myFixtureDef);
	footSensorFixture->GetUserData().pointer = static_cast<int>(ECollisionTag::playerFoot);
}

bool PlayerPhysicsComponent::Jump()
{
	float impulse = m_PhysicsBody->GetMass() * 8.0f;
	m_PhysicsBody->SetLinearVelocity(b2Vec2(m_PhysicsBody->GetLinearVelocity().x, 0.0f));
	m_PhysicsBody->ApplyLinearImpulse(b2Vec2(0, -impulse), m_PhysicsBody->GetWorldCenter(), true);
	return true;
}

void PlayerPhysicsComponent::Move()
{
	b2Vec2 vel = m_PhysicsBody->GetLinearVelocity();
	float desiredVelocity = 0.0f;

	float xInput = m_Player->GetInputAxis().x;

	if (xInput > 0.0f)
	{
		desiredVelocity = b2Min(vel.x + (0.3f * xInput), 5.0f * xInput);
	}
	else if (xInput < 0.0f)
	{
		desiredVelocity = b2Max(vel.x + (0.3f * xInput), 5.0f * xInput);
	}

	float velChange = desiredVelocity - vel.x;
	float impulse = m_PhysicsBody->GetMass() * velChange; //disregard time factor

	m_PhysicsBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_PhysicsBody->GetWorldCenter(), true);
}
