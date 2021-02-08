#include "Zombie.h"

#include "Utilities.h"


/// <summary>
/// Constructs a zombie.
/// </summary>
/// <param name="texPath"> Filepath for the zombie texture. </param>
/// <param name="pos"> Position to spawn the zombie at. </param>
/// <param name="playerRef"> Pointer to the player object. </param>
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

void Zombie::Draw()
{
	_data->window.draw(sprite);
}

/// <summary>
/// Moves the zombie towards the player, also handles any knockback movement.
/// </summary>
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

/// <summary>
/// Nudges the zombie so that it doesn't collide with other entities.
/// </summary>
/// <param name="colMovement"></param>
void Zombie::CollideWithEntity(sf::Vector2f colMovement)
{
	sf::Vector2f nPos = sprite.getPosition() + colMovement;
	sprite.setPosition(nPos);
}

/// <summary>
/// Damages the zombie.
/// </summary>
/// <param name="dam"></param>
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

/// <summary>
/// Adds knockback force to the zombie.
/// </summary>
/// <param name="amt"></param>
void Zombie::AugmentKnockback(float amt)
{
	sf::Vector2f temp = sprite.getPosition() - _playerRef->GetPosition();
	temp = ZEngine::Utilities::NormaliseVector(temp);

	temp = temp * amt * 3.0f;

	_knockbackAmt += temp;
}