#pragma once
#include "Pickup.h"

class SwordPickup : Pickup 
{
public:
	SwordPickup(ZEngine::GameDataRef InData, sf::Vector2f InPosition, class b2World* InWorldRef, float InRotation);
	~SwordPickup();



private:
	
};

