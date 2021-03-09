#include "Player.h"

#include "Utilities.h"

/// <summary>
/// Constructs the player object, setting its texture.
/// </summary>
/// <param name="texPath"> The filepath for the player texture. </param>
/// <param name="pos"> The position to spwan the player in. </param>
Player::Player(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data) :
	_data(data),
	gun(data),
	damageTimer(3.0f, false),
	health(100.0f),
	_knockbackAmt(sf::Vector2f(0.0f, 0.0f))
{
	_data->assetManager.LoadTexture("Player", texPath);
	sprite.setTexture(_data->assetManager.GetTexture("Player"));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(0.5f, 0.5f);
	sprite.setPosition(pos);
	damageTimer.Start();
}


Player::~Player()
{
}

void Player::Update(float dT)
{
	Move(dT);

	gun.Update(dT);

	if (damageTimer.Complete() && sprite.getColor().a != 255.0f)
		sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 255.0f));
}

void Player::Draw()
{
	_data->window.draw(sprite);

	gun.Draw();
}

/// <summary>
/// Handles player movement, also normalises the speed so that diagonal movement isn't faster than omni-directional movement.
/// </summary>
void Player::Move(float dT)
{
	sf::Vector2f movement = sf::Vector2f(0.f, 0.f);
	sf::Vector2f newPos = sprite.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		movement.y += -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		movement.y +=  1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		movement.x += -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		movement.x +=  1;
	

	movement = ZEngine::Utilities::NormaliseVector(movement);
	movement += _knockbackAmt;
	newPos += movement * _speed * dT;

	sprite.setPosition(newPos);


	if (ZEngine::Utilities::GetVectorMagnitude(_knockbackAmt) < 1.0f)
		_knockbackAmt = sf::Vector2f(0.0f, 0.0f);
	else
		_knockbackAmt *= 0.6f;
}

/// <summary>
/// Returns the position of the sprite in the window.
/// </summary>
/// <returns> Returns the sprites position. </returns>
sf::Vector2f Player::GetPosition()
{
	return sprite.getPosition();
}

/// <summary>
/// Handles the player recieving damage.
/// </summary>
/// <param name="dam"></param>
/// <returns> Returns true if the player received damage, false if not. </returns>
bool Player::TakeDamage(float dam, sf::Vector2f zombiePosition)
{
	if (damageTimer.Complete())
	{
		health -= dam;

		AugmentKnockback(zombiePosition);

		sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 0.5f * 255.0f));
		damageTimer.Start();
		
		return true;
	}

	return false;
}

/// <summary>
/// Adds knockback force to the player.
/// </summary>
/// <param name="amt"></param>
void Player::AugmentKnockback(sf::Vector2f zombiePosition)
{
	sf::Vector2f temp = sprite.getPosition() - zombiePosition;
	temp = ZEngine::Utilities::NormaliseVector(temp);

	temp = temp * 10.0f;

	_knockbackAmt += temp;
}