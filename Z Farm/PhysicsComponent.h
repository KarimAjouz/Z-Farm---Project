#pragma once

#include "ObjectComponent.h"
#include "GameObject.h"
#include "box2d.h"
#include <SFML/Graphics.hpp>

const float SCALE = 30.f;

enum EEntityCategory
{
	LEVEL = 0x0001,
	AGENTS = 0x0002,
	DAMAGE = 0x0004,
	OBSTACLES = 0x0008,
	PROPS = 0x0010,
	INTERACTOR = 0x020,
	INTERACTABLE = 0x040,
};

enum ECollisionTag
{
	CT_DEFAULT,
	CT_Player,
	CT_PlayerFoot,
	CT_Level,
	CT_Tile,
	CT_Ground,
	CT_Enemy,
	CT_EnemyFoot,
	CT_Background,
	CT_Room,
	CT_PlayerSword,
	CT_Spike,
	CT_Prop,
	CT_Box,
	CT_Interactable
};

class PhysicsUserData
{
public:
	PhysicsUserData() = default;
	PhysicsUserData(ZEngine::GameObject* InObjectPointer, ECollisionTag InCollisionTag)
		:
		ObjectPointer(InObjectPointer),
		CollisionTag(InCollisionTag)
	{
		bIsValid = true;
	};

	ZEngine::GameObject* ObjectPointer = nullptr;
	ECollisionTag CollisionTag = ECollisionTag::CT_DEFAULT;
	bool bIsValid = false;
};


class PhysicsComponent :
	public ZEngine::ObjectComponent
{
public:
	PhysicsComponent(ZEngine::GameDataRef InData, b2World* InWorldRef);
	~PhysicsComponent();

	virtual void Init() override;

	virtual void Update(float dT) override;

	virtual void InitPhysics();
	virtual void SetBodyUserData(ZEngine::GameObject* InGameObject, ECollisionTag InCollisionTag);

	void MakeAsBoxBody(sf::Vector2f InPos, sf::IntRect InCollisionBox, PhysicsComponent* InAttachedObject, bool InIsDynamic, bool InIsSensor, uint16 InPhysicsCategory, uint16 InCollidingCategories);

	sf::Vector2f GetVelocity() { return sf::Vector2f(m_PhysicsBody->GetLinearVelocity().x * 30, -m_PhysicsBody->GetLinearVelocity().y * 30); };

	b2Body* GetBody() { return m_PhysicsBody; };



protected:

	b2World* m_WorldRef;
	b2Body* m_PhysicsBody;
	PhysicsUserData* m_UserData;

	// Methods

};

