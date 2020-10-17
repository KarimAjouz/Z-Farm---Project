#include "Player.h"

#include "Utilities.h"



Player::Player(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data) :
	_data(data),
	gun(data)
{
	_data->assetManager.LoadTexture("Player", texPath);
	sprite.setTexture(_data->assetManager.GetTexture("Player"));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setPosition(pos);
}


Player::~Player()
{
}

void Player::Init()
{

}

void Player::Update(float dT)
{
	Move(dT);

	gun.Update(dT);

}

void Player::Draw(float dT)
{
	_data->window.draw(sprite);

	gun.Draw(dT);
}

void Player::Move(float dT)
{
	sf::Vector2f movementDir = sf::Vector2f(0.f, 0.f);

	sf::Vector2f newPos = sprite.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		movementDir.y += -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		movementDir.y +=  1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		movementDir.x += -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		movementDir.x +=  1;
	
	movementDir = ZEngine::Utilities::NormaliseVector(movementDir);

	newPos += movementDir * _speed * dT;

	sprite.setPosition(newPos);
}

sf::Vector2f Player::GetPosition()
{
	return sprite.getPosition();
}