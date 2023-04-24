#pragma once
#include "Obstacle.h"
#include "Fragment.h"

class Box : public Obstacle
{
public:
	Box(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos);
	~Box();

	void Update(float dT);
	virtual void Draw() override;

	void Shatter(sf::Vector2f InDamageSourcePos);

	void Hit() override;
	void Hit(sf::Vector2f InDamageSourcePos) override;

private:
	ZEngine::GameDataRef _data;

	void InitPhysics();

	bool _shattered = false;

	std::vector<Fragment> m_Fragments;
};

