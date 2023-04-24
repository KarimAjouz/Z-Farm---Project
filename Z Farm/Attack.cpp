#include "Attack.h"
#include "Player.h";
#include "GameObject.h";
#include "PhysicsComponent.h";

Attack::Attack(ZEngine::GameDataRef InData, b2World* InWorldRef, sf::IntRect InHitbox, Player& InPlayer, std::string InAttackAnimName, float InDamageFrameTime)
	:
	GameObject::GameObject(InData, sf::Vector2f(), InWorldRef),
	m_HitboxComponent(new PhysicsComponent(m_Data, m_WorldRef)),
	m_AttackAnimationName(InAttackAnimName),
	m_HitboxRect(InHitbox),
	m_DamageFrameTime(InDamageFrameTime)
{
	//m_HitboxComponent->MakeAsBoxBody(
	//	sf::Vector2f(m_HitboxRect.left, m_HitboxRect.top),
	//	InHitbox,
	//	reinterpret_cast<PhysicsComponent*>(InPlayer.GetPhysicsComponent()),
	//	true,
	//	true,
	//	EEntityCategory::DAMAGE,
	//	EEntityCategory::OBSTACLES
	//	| EEntityCategory::AGENTS
	//);

	//m_HitboxComponent->SetBodyUserData(this, ECollisionTag::CT_PlayerSword);
}

Attack::~Attack()
{
	m_HitboxComponent->~PhysicsComponent();
}

void Attack::FlipFixture()
{
	//b2Vec2 newFixturePos = m_HitboxComponent->GetBody()->GetFixtureList()->GetAABB(0).GetCenter();
	//newFixturePos *= -1;
	//m_HitboxRect.left *= -1;
	//m_PlayerBody->DestroyFixture(m_Hitbox);
	//InitPhysics();
}

void Attack::AddContactObject(ZEngine::GameObject* InObject)
{
	m_ContactObjects.push_back(InObject);
}

void Attack::RemoveContactObject(ZEngine::GameObject* InObject)
{
	for (int i = 0; i < m_ContactObjects.size(); i++)
	{
		if (InObject == m_ContactObjects.at(i))
		{
			m_ContactObjects.erase(m_ContactObjects.begin() + i);
		}
	}
}
//
//void Attack::InitPhysics()
//{
//	b2FixtureDef myFixtureDef = b2FixtureDef();
//	b2PolygonShape attackShape;
//
//	//Prepare the attack hitbox
//	myFixtureDef.filter.categoryBits = EEntityCategory::DAMAGE;
//	myFixtureDef.filter.maskBits = EEntityCategory::OBSTACLES | EEntityCategory::AGENTS;
//
//	//add right stab sensor 
//	attackShape.SetAsBox(m_HitboxRect.width / SCALE, m_HitboxRect.height / SCALE, b2Vec2(m_HitboxRect.left / SCALE, m_HitboxRect.top / SCALE), 0);
//	myFixtureDef.isSensor = true;
//	myFixtureDef.shape = &attackShape;
//	m_Hitbox = m_PlayerBody->CreateFixture(&myFixtureDef);
//
//
//
//	m_Hitbox->GetUserData().pointer = static_cast<int>(ECollisionTag::CT_PlayerSword);
//}

void Attack::CommitDamage(sf::Vector2f InDamageSourcePos)
{
	for (ZEngine::GameObject* obj : m_ContactObjects)
	{
		obj->Hit(InDamageSourcePos);
	}
}

void Attack::HandleContactBegin(PhysicsUserData* InCollidingFixture, ECollisionTag InMyCollidedFixture)
{
}

void Attack::HandleContactEnd(PhysicsUserData* InCollidingFixture, ECollisionTag InMyCollidedFixture)
{
}