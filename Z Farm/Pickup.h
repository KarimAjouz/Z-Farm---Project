#pragma once

#include "Game.h"
#include "GameObject.h"
#include "Agent.h"

#include <SFML/Graphics.hpp>

class Pickup
	:
	public ZEngine::GameObject
{
public:
	Pickup(ZEngine::GameDataRef InData, sf::Vector2f InPosition, class b2World* InWorldRef);
	~Pickup();

	enum Type
	{
		PT_Equipment,
		PT_Loot,
		PT_COUNT
	};

	virtual void Update(float dT) override;

protected:
	class PhysicsComponent* m_PhysicsComponent;

	Type m_Type = PT_COUNT;
	virtual void Collect(ZEngine::Agent* InCollectingAgent);
};
