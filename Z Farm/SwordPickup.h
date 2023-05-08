#pragma once
#include "Pickup.h"
#include "Agent.h"

class SwordPickup : Pickup 
{
public:
	SwordPickup(ZEngine::GameDataRef InData, sf::Vector2f InPosition, class b2World* InWorldRef, float InRotation);
	~SwordPickup();



protected:

	virtual void Collect(ZEngine::Agent* InInteractingAgent) override;
};

