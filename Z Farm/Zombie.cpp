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
	_health(10.0f),
	_maxHealth(_health),
	_playerRef(playerRef),
	_healthBar(data, UI_RELOADBAR, "Ammobar", sf::Vector2f(pos.x - 16.0f, pos.y - 20.0f)),
	damage(60.0f),
	_walk(1.0f, true, _data, "SkeletonWalk", SKELE_WALK, sf::IntRect(0, 0, 22, 33), &sprite, sf::Vector2f(8, 17)),
	_attackWindUp(0.8f, false, _data, "SkeletonWindUp", SKELE_WIND_UP, sf::IntRect(0, 0, 43, 37), &sprite, sf::Vector2f(11, 21)),
	_attack(0.5f, false, _data, "SkeletonAttack", SKELE_ATTACK, sf::IntRect(0, 0, 43, 37), &sprite, sf::Vector2f(11, 21)),
	_attackReset(1.0f, false, _data, "SkeletonReset", SKELE_ATTACK_RESET, sf::IntRect(0, 0, 43, 37), &sprite, sf::Vector2f(11, 21)),
	_takingDamage(0.8f, false, _data, "SkeletonTakingDamage", SKELE_DAMAGE, sf::IntRect(0, 0, 30, 32), &sprite, sf::Vector2f(14, 16)),
	_dying(1.0f, false, _data, "SkeletonDying", SKELE_DEATH, sf::IntRect(0, 0, 33, 32), &sprite, sf::Vector2f(19, 16)),
	_isFlipped(false),
	_curAnim(&_walk)
{
	_healthBar.ReScaleWidth(0.5f);
	_healthBar.ResizeForeground(_health / _maxHealth);
	_healthBar.Centralise();

	sprite.setScale(2.0f, 2.0f);
	sprite.setPosition(pos);
	_curAnim->Play();
	UpdateAnimations();

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

	UpdateState();
	UpdateAnimations();

	_curAnim->Update(dT);
}

void Zombie::Draw()
{
	_data->window.draw(sprite);
	_data->window.draw(r);
	_healthBar.Draw();
}

/// <summary>
/// Moves the zombie towards the player, also handles any knockback movement.
/// </summary>
void Zombie::Move(float dT)
{
	sf::Vector2f movement = _playerRef->GetPosition() - sprite.getPosition();
	if (_state == walking)
		movement = ZEngine::Utilities::NormaliseVector(movement);
	else
		movement = sf::Vector2f();

	movement = movement + _knockbackAmt;

	movement = movement * dT * _speed;
	movement += sprite.getPosition();
	sprite.setPosition(movement);

	if (ZEngine::Utilities::GetVectorMagnitude(_knockbackAmt) < 1.0f)
		_knockbackAmt = sf::Vector2f(0.0f, 0.0f);
	else
		_knockbackAmt *= 0.9f;

	_healthBar.Move(sf::Vector2f(movement.x, movement.y - (sprite.getLocalBounds().height / 2) - 10.0f));
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
	{
		_health = 0.0f;
		_state = dying;
	}
	else
		_state = takingDamage;

	_healthBar.ResizeForeground(_health / _maxHealth);

}

/// <summary>
/// Marks the entity for death so the engine knows to delete them when the frame ends.
/// </summary>
void Zombie::MarkForDeath()
{
	_kill = true;
}

/// <summary>
/// Returns if the entity is to be gotten rid of at the end of the frame.
/// </summary>
/// <returns></returns>
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

	temp = temp * amt;

	_knockbackAmt += temp;
}

/// <summary>
/// Handles the state system logic.
/// </summary>
void Zombie::UpdateState()
{
	sf::FloatRect colRect;

	colRect = sf::FloatRect(sprite.getPosition().x, _attackZone.top + sprite.getPosition().y, _attackZone.width, _attackZone.height);

	if (_isFlipped)
		colRect.left -= 60;
	else
		colRect.left += 40;

	switch (_state)
	{
	case walking:
		if ((_playerRef->GetPosition().x < sprite.getPosition().x) && !_isFlipped || (_playerRef->GetPosition().x > sprite.getPosition().x) && _isFlipped)
			FlipSprite();

		if (ZEngine::Utilities::RectCollider(colRect, _playerRef->sprite.getGlobalBounds()))
			_state = attackWindUp;

		break;
	case attackWindUp:
		if (_curAnim->complete)
		{
			if(ZEngine::Utilities::RectCollider(colRect, _playerRef->sprite.getGlobalBounds()))
				_playerRef->TakeDamage(damage, sprite.getPosition());

			_state = attack;
		}
		break;
	case attack:
		if (_curAnim->complete)
			_state = attackReset;
		break;
	case attackReset:
		if (_curAnim->complete)
			_state = walking;
		break;
	case takingDamage:
		if (_curAnim->complete)
			_state = walking;
		break;
	case dying:
		if (_curAnim->complete)
			MarkForDeath();
		break;
	default:
		break;
	}

}

/// <summary>
/// Decides which animation to switch to depending on the state the entity is in.
/// </summary>
void Zombie::UpdateAnimations()
{
	std::string temp = _curAnim->animName;

	switch (_state)
	{
		case walking:
			if (_curAnim->animName != _walk.animName)
				_curAnim = &_walk;
			break;
		case attackWindUp:
			if (_curAnim->animName != _attackWindUp.animName)
				_curAnim = &_attackWindUp;
			break;
		case attack:
			if (_curAnim->animName != _attack.animName)
				_curAnim = &_attack;
			break;
		case attackReset:
			if (_curAnim->animName != _attackReset.animName)
				_curAnim = &_attackReset;
			break;
		case takingDamage:
			if (_curAnim->animName != _takingDamage.animName)
				_curAnim = &_takingDamage;
			break;
		case dying:
			if (_curAnim->animName != _dying.animName)
				_curAnim = &_dying;
			break;
		default:
			break;
	}

	if (temp != _curAnim->animName)
		_curAnim->Play();
}

//Flips the sprite visually.
void Zombie::FlipSprite()
{
	_isFlipped = !_isFlipped;
	sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);
}