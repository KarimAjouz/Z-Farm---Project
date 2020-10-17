#include "Zombie.h"

#include "Utilities.h"



Zombie::Zombie(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, Player* playerRef) :
	_data(data),
	_health(100.0f),
	_playerRef(playerRef)
{
	_data->assetManager.LoadTexture("Zombie", texPath);
	sprite.setTexture(_data->assetManager.GetTexture("Zombie"));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setPosition(pos);
}


Zombie::~Zombie()
{
}

void Zombie::Init()
{

}

void Zombie::Update(float dT)
{
	Move(dT);
}

void Zombie::Draw(float dT)
{
	_data->window.draw(sprite);
}

void Zombie::Move(float dT)
{
	sf::Vector2f movement = _playerRef->GetPosition() - sprite.getPosition();
	movement = ZEngine::Utilities::NormaliseVector(movement);

	movement = movement + _knockbackAmt;
	movement = movement * dT * _speed;
	movement += sprite.getPosition();
	sprite.setPosition(movement);

	if (ZEngine::Utilities::GetVectorMagnitude(_knockbackAmt) < 1.0f)
		_knockbackAmt = sf::Vector2f(0.0f, 0.0f);
	else
		_knockbackAmt *= 0.6f;
}

void Zombie::DamageZombie(float dam)
{
	_health -= dam;

	AugmentKnockback(dam);

	if (_health <= 0.0f)
		MarkForDeath(true);
}

void Zombie::MarkForDeath(bool mark)
{
	_kill = true;
}

bool Zombie::IsMarked()
{
	return _kill;
}

void Zombie::AugmentKnockback(float amt)
{
	sf::Vector2f temp = sprite.getPosition() - _playerRef->GetPosition();
	temp = ZEngine::Utilities::NormaliseVector(temp);

	temp = temp * amt * 3.0f;

	_knockbackAmt += temp;
}