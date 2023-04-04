#pragma once

#include "ObjectComponent.h"
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
	def,
	player,
	playerFoot,
	level,
	tile,
	ground,
	enemy,
	enemyFoot,
	background,
	room,
	playerSword,
	spike,
	prop,
	box,
	interactable
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

	sf::Vector2f GetVelocity() { return sf::Vector2f(m_PhysicsBody->GetLinearVelocity().x * 30, -m_PhysicsBody->GetLinearVelocity().y * 30); };

	b2Body* GetBody() { return m_PhysicsBody; };

protected:

	b2World* m_WorldRef;
	b2Body* m_PhysicsBody;


	// Methods

};

