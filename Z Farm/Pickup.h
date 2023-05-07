#pragma once

#include "Game.h"
#include "Player.h"

#include <SFML/Graphics.hpp>


class Pickup
	:
	public ZEngine::GameObject
{
public:
	Pickup(ZEngine::GameDataRef InData, sf::Vector2f InPosition, class b2World* InWorldRef);
	~Pickup();

	virtual void Update(float dT) override;

	void Collect(ZEngine::Agent* InCollectingAgent);

protected:
	class PhysicsComponent* m_PhysicsComponent;

};

