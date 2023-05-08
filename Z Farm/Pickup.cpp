#include "Pickup.h"

#include "PhysicsComponent.h"

//Pickup::Pickup(int val, std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, sf::Vector2f dir) :
//	_data(data),
//	_value(val),
//	_movement(dir),
//	_markedForDeath(false)
//{
//	_data->assetManager.LoadTexture("Pickup", texPath);
//	sprite.setTexture(_data->assetManager.GetTexture("Pickup"));
//	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
//	sprite.setPosition(pos);
//}

Pickup::Pickup(ZEngine::GameDataRef InData, sf::Vector2f InPosition, b2World* InWorldRef)
	:
	ZEngine::GameObject(InData, InPosition, InWorldRef)
{
}

Pickup::~Pickup()
{
	ZEngine::GameObject::~GameObject();
}

void Pickup::Update(float dT)
{

}

void Pickup::Collect(ZEngine::Agent* InCollectingAgent)
{
}
