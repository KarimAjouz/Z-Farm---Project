#include "Player.h"

#include "Utilities.h"

/// <summary>
/// Constructs the player object, setting its texture.
/// </summary>
/// <param name="texPath"> The filepath for the player texture. </param>
/// <param name="pos"> The position to spwan the player in. </param>
Player::Player(std::string texPath, sf::Vector2f pos, ZEngine::GameDataRef data, SaveDataManager::SaveData saveData, BalanceSheet* b, std::vector<Bullet*>* bullets) :
	_data(data),
	gun(data, saveData, b, bullets),
	damageTimer(3.0f, false),
	health(100.0f),
	_knockbackAmt(sf::Vector2f(0.0f, 0.0f)),
	dead(saveData.isDead),
	_healthBar(_data, UI_RELOADBAR, "Ammobar", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f)),
	_idleAnim(0.6f, true, data, "PlayerIdle", PLAYER_IDLE, sf::IntRect(0, 0, 231, 190), &sprite, sf::Vector2f(108, 100)),
	_walkAnim(0.6f, true, data, "PlayerWalk", PLAYER_WALK, sf::IntRect(0, 0, 231, 190), &sprite, sf::Vector2f(108, 100)),
	_windUpAnim(0.4f, false, data, "PlayerWindUp", PLAYER_WIND_UP, sf::IntRect(0, 0, 231, 190), &sprite, sf::Vector2f(108, 100)),
	_attackAnim(0.4f, false, data, "PlayerAttack", PLAYER_ATTACK, sf::IntRect(0, 0, 231, 190), &sprite, sf::Vector2f(108, 100)),
	_hitAnim(0.4f, false, data, "PlayerHit", PLAYER_HIT, sf::IntRect(0, 0, 231, 190), &sprite, sf::Vector2f(108, 100)),
	_dyingAnim(0.4f, false, data, "PlayerDeath", PLAYER_DEATH, sf::IntRect(0, 0, 231, 190), &sprite, sf::Vector2f(108, 100)),
	_dashAnim(1.0f, false, data, "PlayerDash", PLAYER_DASH, sf::IntRect(0, 0, 231, 190), &sprite, sf::Vector2f(108, 100)),
	_curAnim(&_idleAnim)
{
	damageTimer.Start();

	_healthBar.Centralise();
	_healthBar.ReScaleWidth(5.0f);
	_healthBar.Move(sf::Vector2f(SCREEN_WIDTH / 2, 50.0f));
	_healthBar.ResizeForeground(1.0f);

	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(pos);
	_curAnim->Play();
	UpdateAnimations();
}


Player::~Player()
{
}

void Player::Update(float dT)
{
	Move(dT);
	UpdateState();
	UpdateAnimations();
	gun.Update(dT);

	if (damageTimer.Complete() && sprite.getColor().a != 255.0f)
		sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 255.0f));

	_curAnim->Update(dT);

}

void Player::Draw()
{
	_data->window.draw(sprite);

	_healthBar.Draw();

	gun.Draw();
}

/// <summary>
/// Handles player movement, also normalises the speed so that diagonal movement isn't faster than omni-directional movement.
/// </summary>
void Player::Move(float dT)
{
	sf::Vector2f movement = sf::Vector2f(0.f, 0.f);
	sf::Vector2f newPos = sprite.getPosition();

	if (_state == walking || _state == idle)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			movement.y += -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			movement.y += 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			movement.x += -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			movement.x += 1;

		if (movement.x == 1 && _isFlipped || movement.x == -1 && !_isFlipped)
			FlipSprite();

		if (movement.x != 0.0f || movement.y != 0.0f)
			_state = walking;
		else
			_state = idle;
	}


	

	movement = ZEngine::Utilities::NormaliseVector(movement);
	movement += _knockbackAmt;
	newPos += movement * _speed * dT;

	if(!dead)
		sprite.setPosition(newPos);


	if (ZEngine::Utilities::GetVectorMagnitude(_knockbackAmt) < 1.0f)
		_knockbackAmt = sf::Vector2f(0.0f, 0.0f);
	else
		_knockbackAmt *= 0.6f;
}

void Player::Attack()
{
	_state = attackWindUp;
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
	if (damageTimer.Complete() && !dead)
	{
		health -= dam;

		_healthBar.ResizeForeground(health / 100.0f);

		if (health <= 0.0f)
			_state = dying;

		AugmentKnockback(zombiePosition);
		damageTimer.Start();
		
		_state = takingDamage;

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

void Player::Respawn()
{
	// Reset the healthbar back to maximum.
	_healthBar.ResizeForeground(1.0f);

	sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	health = 100.0f;
	dead = false;
}

/// <summary>
/// Handles the state system logic.
/// </summary>
void Player::UpdateState()
{
	switch (_state)
	{
	case attackWindUp:
		if (_curAnim->complete)
		{
			_state = attacking;
			gun.Shoot(_data, sprite.getPosition() - sprite.getOrigin() + _attackLocation);
		}
		break;
	case attacking:
		if (_curAnim->complete)
			_state = idle;
		break;
	case takingDamage:
		if (_curAnim->complete)
			_state = walking;
		break;
	case dying:
		if (_curAnim->complete)
			dead = true;
		break;
	case dashing:
		break;
	default:
		break;
	}

}

/// <summary>
/// Decides which animation to switch to depending on the state the entity is in.
/// </summary>
void Player::UpdateAnimations()
{
	std::string temp = _curAnim->animName;

	switch (_state)
	{
	case idle:
		if (_curAnim->animName != _idleAnim.animName)
			_curAnim = &_idleAnim;
		break;
	case walking:
		if (_curAnim->animName != _walkAnim.animName)
			_curAnim = &_walkAnim;
		break;
	case attackWindUp:
		if (_curAnim->animName != _windUpAnim.animName)
			_curAnim = &_windUpAnim;
		break;
	case attacking:
		if (_curAnim->animName != _attackAnim.animName)
			_curAnim = &_attackAnim;
		break;
	case takingDamage:
		if (_curAnim->animName != _hitAnim.animName)
			_curAnim = &_hitAnim;
		break;
	case dying:
		if (_curAnim->animName != _dyingAnim.animName)
			_curAnim = &_dyingAnim;
		break;
	case dashing:
		if (_curAnim->animName != _dashAnim.animName)
			_curAnim = &_dashAnim;
		break;
	default:
		break;
	}

	if (temp != _curAnim->animName)
		_curAnim->Play();
}


//Flips the sprite visually.
void Player::FlipSprite()
{
	_isFlipped = !_isFlipped;
	sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);
}