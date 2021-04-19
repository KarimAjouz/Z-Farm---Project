#pragma once
#include "Obstacle.h"
#include "Fragment.h"

class Box : public Obstacle
{
public:
	Box(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos);
	~Box();

	void Update(float dT);
	void Draw();

	void Shatter();

	void Hit();

private:
	ZEngine::GameDataRef _data;

	void InitPhysics();

	bool _shattered = false;

	std::vector<Fragment> _fragments;
};

