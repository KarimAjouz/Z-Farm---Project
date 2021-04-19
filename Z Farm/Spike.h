#pragma once
#include "Obstacle.h"

class Spike : public Obstacle
{
public:
	Spike(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f pos);
	~Spike();

	
	void Update(float dT);
	void Draw();

	b2Body* body;


private:
	ZEngine::GameDataRef _data;

	b2World* _worldRef;

	void InitPhysics();
};

