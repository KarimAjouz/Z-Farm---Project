#include "Bullet.h"

#include "Utilities.h"
#include "Definitions.h"



Bullet::Bullet(ZEngine::GameDataRef data, sf::Vector2f pos, sf::Vector2f target, float speed, float dam) :
	_data(data),
	_speed(speed),
	damage(dam),
	_pos(pos),
	_dir(CalculateDirection(pos, target))
{
	_data->assetManager.LoadTexture("Bullet", BULLET_FILEPATH);
	sprite.setTexture(_data->assetManager.GetTexture("Bullet"));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setPosition(pos);
}


Bullet::~Bullet()
{
}


void Bullet::Update(float dT)
{
	Move(dT);
}

void Bullet::Draw(float dT)
{
	_data->window.draw(sprite);
}

sf::Vector2f Bullet::CalculateDirection(sf::Vector2f pos, sf::Vector2f target)
{
	sf::Vector2f vec = target - pos;

	vec = ZEngine::Utilities::NormaliseVector(vec);

	return vec;
}

void Bullet::Move(float dT)
{
	_pos += _dir * dT * _speed;
	sprite.setPosition(_pos);
}

void Bullet::CheckForDeath()
{
	if (sprite.getPosition().x < 0 || sprite.getPosition().x > SCREEN_WIDTH || sprite.getPosition().y < 0 || sprite.getPosition().y > SCREEN_HEIGHT)
		MarkForDeath(true);
}

void Bullet::MarkForDeath(bool mark)
{
	_kill = true;
}

bool Bullet::IsMarked() 
{
	return _kill;
}