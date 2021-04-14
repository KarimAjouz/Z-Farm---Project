#include "SwordPickup.h"
#include "Definitions.h"

#include <iostream>

SwordPickup::SwordPickup(ZEngine::GameDataRef data, b2World* worldRef, Player* playerRef) :
	_data(data),
	_worldRef(worldRef),
	_playerRef(playerRef)
{
	_data->assetManager.LoadTexture("Sword", SWORD_ITEM);
	sprite = sf::Sprite();
	sprite.setTexture(_data->assetManager.GetTexture("Sword"));
	sprite.setPosition(500.0f, 500.0f);
	sprite.setOrigin(3.5f, 10.5f);
	sprite.setScale(2.0f, 2.0f);
}

SwordPickup::~SwordPickup()
{
}

void SwordPickup::Update(float dT)
{
	if (!_collected)
	{
		Hover(dT);
		TestCollision();
	}
}

void SwordPickup::Draw()
{
	if (!_collected)
		_data->window.draw(sprite);
}


void SwordPickup::Hover(float dT)
{
	_t += dT;
	_hoverOffset = std::sinf(_t * _hoverMultiplier) * _hoverAmount;
	_spinOffset = std::sinf(_t * _spinMultiplier);

	sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + _hoverOffset);
	sprite.setScale(2.0f * _spinOffset, sprite.getScale().y);
}

void SwordPickup::InitPhysics()
{
}

void SwordPickup::TestCollision()
{
	if (sprite.getGlobalBounds().intersects(_playerRef->sprite.getGlobalBounds()))
	{
		_playerRef->EquipSword();
		_collected = true;
	}
}