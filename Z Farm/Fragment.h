#pragma once
#include "Prop.h"

class Fragment : public Prop
{
public:
	Fragment(ZEngine::GameDataRef data, b2World* worldRef, sf::IntRect texRect, sf::Vector2f pos, sf::Vector2f forceDir);
	~Fragment();

	void Update(float dT);
	void Draw();

private:
	b2World* _worldRef;
	ZEngine::GameDataRef _data;

	void InitPhysics();
};

