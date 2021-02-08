#include "Bullet.h"

#include "Utilities.h"
#include "Definitions.h"


/// <summary>
/// Constructs a bullet with the following parameters:
/// </summary>
/// <param name="data"> Reference to the Game Data. </param>
/// <param name="pos"> Position to spawn the bullet at. </param>
/// <param name="target"> The target location for the bullet to move towards. </param>
/// <param name="speed"> The bullet speed. </param>
/// <param name="dam"> The damage that the bullet will deal. </param>
Bullet::Bullet(ZEngine::GameDataRef data, sf::Vector2f pos, sf::Vector2f target, int speed, int dam) :
	_data(data),
	_speed(speed),
	damage(dam),
	_pos(pos),
	_dir(CalculateDirection(pos, target))
{
	//Loads/sets the texture via the asset manager.
	_data->assetManager.LoadTexture("Bullet", BULLET_FILEPATH);
	sprite.setTexture(_data->assetManager.GetTexture("Bullet"));

	//Sets the center of the bullet to be the origin, then sets the position.
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setPosition(pos);
}


Bullet::~Bullet()
{
}

/// <summary>
/// Calls this function each frame. Handles logic for the bullet.
/// </summary>
/// <param name="dT"> The time between the previous frame and this one. </param>
void Bullet::Update(float dT)
{
	Move(dT);
}

/// <summary>
/// Calls this function after the main update loop. Handles rendering the bullet.
/// </summary>
/// <param name="dT"> The time between the previous frame and this one. </param>
void Bullet::Draw()
{
	_data->window.draw(sprite);
}

/// <summary>
/// Returns the direction that the bullet is moving in as a 2-vector.
/// </summary>
/// <param name="pos"> The position of the bullet. </param>
/// <param name="target"> The position of the target the bullet is moving towards. </param>
/// <returns> The direction of the bullet as a 2-vector. </returns>
sf::Vector2f Bullet::CalculateDirection(sf::Vector2f pos, sf::Vector2f target)
{
	sf::Vector2f vec = target - pos;

	vec = ZEngine::Utilities::NormaliseVector(vec);

	return vec;
}

/// <summary>
/// Moves the bullet in it's direction.
/// </summary>
/// <param name="dT"> The time between the previous frame and this one. </param>
void Bullet::Move(float dT)
{
	_pos += _dir * dT * _speed;
	sprite.setPosition(_pos);
}

/// <summary>
/// Checks to see if the bullet has left the screen area and needs to be destroyed.
/// </summary>
void Bullet::CheckForDeath()
{
	if (sprite.getPosition().x < 0 || sprite.getPosition().x > SCREEN_WIDTH || sprite.getPosition().y < 0 || sprite.getPosition().y > SCREEN_HEIGHT)
		MarkForDeath();
}

/// <summary>
/// Marks the bullet to be destroyed.
/// </summary>
/// <param name="mark"></param>
void Bullet::MarkForDeath()
{
	_kill = true;
}

/// <summary>
/// Returns if the bullet is marked for destruction.
/// </summary>
/// <returns> Whether the bullet needs to be destroyed. </returns>
bool Bullet::IsMarked() 
{
	return _kill;
}