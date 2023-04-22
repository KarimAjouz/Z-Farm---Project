#include "Attack.h"
#include "Player.h";
#include "GameObject.h";
#include "PlayerPhysicsComponent.h";

Attack::Attack(sf::IntRect InHitbox, Player& InPlayer, std::string InAttackAnimName, float InDamageFrameTime)
	:
	m_PlayerBody(InPlayer.GetPhysicsComponent()->GetBody()),
	m_AttackAnimationName(InAttackAnimName),
	m_HitboxRect(InHitbox),
	m_DamageFrameTime(InDamageFrameTime)
{
	InitPhysics();
}

Attack::~Attack()
{
	m_PlayerBody->DestroyFixture(m_Hitbox);
}

void Attack::FlipFixture()
{
	b2Vec2 newFixturePos = m_Hitbox->GetAABB(0).GetCenter();
	newFixturePos *= -1;
	m_HitboxRect.left *= -1;
	m_PlayerBody->DestroyFixture(m_Hitbox);
	InitPhysics();
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

void Attack::InitPhysics()
{
	b2FixtureDef myFixtureDef = b2FixtureDef();
	b2PolygonShape attackShape;

	//Prepare the attack hitbox
	myFixtureDef.filter.categoryBits = EEntityCategory::DAMAGE;
	myFixtureDef.filter.maskBits = EEntityCategory::OBSTACLES | EEntityCategory::AGENTS;

	//add right stab sensor 
	attackShape.SetAsBox(m_HitboxRect.width / SCALE, m_HitboxRect.height / SCALE, b2Vec2(m_HitboxRect.left / SCALE, m_HitboxRect.top / SCALE), 0);
	myFixtureDef.isSensor = true;
	myFixtureDef.shape = &attackShape;
	m_Hitbox = m_PlayerBody->CreateFixture(&myFixtureDef);
	m_Hitbox->GetUserData().pointer = static_cast<int>(ECollisionTag::playerSword);
}

void Attack::CommitDamage()
{
	for (ZEngine::GameObject* obj : m_ContactObjects)
	{
		obj->Hit();
	}
}

