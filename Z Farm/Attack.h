#pragma once

#include "Animation.h"
#include "box2d.h"
#include "GameObject.h"

class Attack
{
public:
	Attack(sf::IntRect InHitboxRect, class Player& InPlayer, std::string InAttackAnimName, float InDamageFrameTime);
	~Attack();

	std::string GetAnimation() { return m_AttackAnimationName; }

	void FlipFixture();
	float GetDamageFrameTime() { return m_DamageFrameTime; }

	void AddContactObject(ZEngine::GameObject* InObject);
	void RemoveContactObject(ZEngine::GameObject* InObject);
	void CommitDamage();

private:
	std::string m_AttackAnimationName;
	b2Fixture* m_Hitbox = nullptr;
	b2Body* m_PlayerBody;
	float m_DamageFrameTime;

	sf::IntRect m_HitboxRect;

	std::vector<ZEngine::GameObject*> m_ContactObjects;

	void InitPhysics();

};

