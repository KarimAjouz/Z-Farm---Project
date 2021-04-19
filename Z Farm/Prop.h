#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <box2d.h>

class Prop
{
public:
	Prop();
	~Prop();

	virtual void Update(float dT) = 0;
	virtual void Draw() = 0;
	
	sf::Sprite sprite;

	void InitPhysics(sf::IntRect collisionBox, b2World* worldRef);

	b2Body* body = nullptr;
	b2World* worldRef;
};

