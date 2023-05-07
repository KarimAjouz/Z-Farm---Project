#include "SwordPickup.h"
#include "Definitions.h"
#include "GameObject.h"

#include <iostream>


SwordPickup::SwordPickup(ZEngine::GameDataRef InData, sf::Vector2f InPosition, b2World* InWorldRef, float InRotation)
	:
	Pickup(InData, InPosition, InWorldRef)
{
}

SwordPickup::~SwordPickup()
{
}