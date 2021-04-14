#include "Pickup.h"

Pickup::Pickup()
{

}

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

Pickup::~Pickup()
{
}

void Pickup::Update(float dT)
{

}

void Pickup::Draw()
{
	_data->window.draw(sprite);
}

/// <summary>
/// Marks the pickup for death, returns the value if collected.
/// </summary>
/// <param name="collected"></param>
/// <returns></returns>
int Pickup::Destroy(bool collected)
{
	_markedForDeath = true;

	if (collected)
		return _value;
	else
		return 0;
}

bool Pickup::IsMarked()
{
	return _markedForDeath;
}