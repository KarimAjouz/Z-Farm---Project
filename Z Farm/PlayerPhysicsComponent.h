#pragma once
#include "PhysicsComponent.h"


class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	PlayerPhysicsComponent(ZEngine::GameDataRef InData, b2World* InWorldRef);
	PlayerPhysicsComponent(ZEngine::GameDataRef InData, b2World* InWorldRef, class Player* InPlayer);
	
	~PlayerPhysicsComponent();

	virtual void Update(float dT) override;

	virtual void InitPhysics() override;
	bool Jump();
	void Move();

private:

	class Player* m_Player;

	sf::IntRect m_CollisionBox = sf::IntRect(25, 16, 18, 12);
};

