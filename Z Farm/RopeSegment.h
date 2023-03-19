#pragma once

#include "Obstacle.h"

class RopeSegment : public Obstacle
{
public:
	RopeSegment(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos);
	~RopeSegment();

	void Update(float dT);
	void Draw();

	void Hit() {};
	void Hit(sf::Vector2f playerPos) {};

private:
	ZEngine::GameDataRef _data;

	void InitPhysics();


};

