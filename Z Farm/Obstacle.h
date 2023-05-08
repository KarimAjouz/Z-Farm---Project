#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "box2d.h"
#include "GameObject.h"

class Obstacle
	:
	public ZEngine::GameObject
{
public:
	Obstacle(ZEngine::GameDataRef InData, sf::Vector2f InPosition, b2World* InWorldRef);
	~Obstacle();

	virtual void Update(float dT) = 0;
	virtual void Draw() override;

	virtual void Hit() override;
	virtual void Hit(sf::Vector2f playerPos) = 0;

	enum class Type
	{
		spike,
		box
	};

	Type type = Type::spike;

	virtual void InitPhysics() = 0;

	void InitPhysics(sf::IntRect collisionBox, bool collider, bool isDynamic, b2World* world);

protected:
	class PhysicsComponent* m_PhysicsComponent;
};
