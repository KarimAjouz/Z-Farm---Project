#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "box2d.h"

class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	virtual void Update(float dT) = 0;
	virtual void Draw() = 0;

	virtual void Hit() = 0;
	virtual void Hit(sf::Vector2f playerPos) = 0;

	enum class Type
	{
		spike
	};

	Type type = Type::spike;

	sf::Sprite sprite;
	sf::RectangleShape hitbox;

	b2Body* body = nullptr;

	virtual void InitPhysics() = 0;

	b2World* worldRef = nullptr;

	void InitPhysics(sf::IntRect collisionBox, bool collider, bool isDynamic, b2World* world);
private:
};

