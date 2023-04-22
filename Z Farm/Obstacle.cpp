#include "Obstacle.h"

#include "PhysicsComponent.h"


Obstacle::Obstacle(ZEngine::GameDataRef InData, sf::Vector2f InPosition, b2World* InWorldRef)
	:
	GameObject::GameObject(InData, InPosition, InWorldRef),
	m_PhysicsComponent(new PhysicsComponent(InData, InWorldRef))
{
}

Obstacle::~Obstacle()
{

}

void Obstacle::Draw()
{
	GameObject::Draw();
}

void Obstacle::Hit()
{
}

void Obstacle::InitPhysics(sf::IntRect collisionBox, bool collider, bool isDynamic, b2World* world)
{
	
}