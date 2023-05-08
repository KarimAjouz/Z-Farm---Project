#pragma once

#include "Animation.h"
#include "box2d.h"
#include "GameObject.h"
#include "Agent.h"

class PhysicsComponent;
struct PhysicsUserData;
enum ECollisionTag;

class Attack
	:
	public ZEngine::GameObject
{
public:
	Attack(ZEngine::GameDataRef InData, b2World* InWorldRef, sf::IntRect InHitboxRect, ZEngine::Agent& InOwningObject, std::string InAttackAnimName, float InDamageFrameTime);
	~Attack();

	std::string GetAnimation() { return m_AttackAnimationName; }

	void InitHitbox();

	void FlipFixture();
	float GetDamageFrameTime() { return m_DamageFrameTime; }

	void CommitDamage(sf::Vector2f InDamageSourcePos);

	virtual void HandleContactBegin(PhysicsUserData* InCollidingFixture, ECollisionTag InMyCollidedFixture) override;
	virtual void HandleContactEnd(PhysicsUserData* InCollidingFixture, ECollisionTag InMyCollidedFixture) override;

private:
	std::string m_AttackAnimationName;
	PhysicsComponent* m_HitboxComponent = nullptr;
	float m_DamageFrameTime;

	sf::IntRect m_HitboxRect;

	std::vector<ZEngine::GameObject*> m_ContactObjects;

	ZEngine::Agent* m_Owner;

	void AddContactObject(ZEngine::GameObject* InObject);
	void RemoveContactObject(ZEngine::GameObject* InObject);
};
