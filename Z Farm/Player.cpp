#include "Player.h"


/// <summary>
/// Constructs the player object, setting its texture.
/// </summary>
/// <param name="texPath"> The filepath for the player texture. </param>
/// <param name="pos"> The position to spwan the player in. </param>
Player::Player(sf::Vector2f pos, ZEngine::GameDataRef data, BalanceSheet* b, b2World* worldRef) :
	_data(data),
	_state(idle)
{
	InitPhysics(pos, worldRef);

	sprite.setPosition(pos);
	sprite.setScale(2.0f, 2.0f);

	InitAnimations();
	_animSystem.SetAnimation("PlayerIdle");
	_animSystem.Play();
}


Player::~Player()
{
}

void Player::Update(float dT)
{
	HandleInputs();
	UpdatePhysics();

	UpdateState();
	UpdateAnimations(dT);
}

void Player::Draw()
{
	_data->window.draw(sprite);
}


/// <summary>
/// Handles the state system logic.
/// </summary>
void Player::UpdateState()
{
	if (_wasd.x != 0)
		_state = running;
	else if (_wasd.x == 0)
		_state = idle;
}

/// <summary>
/// Decides which animation to switch to depending on the state the entity is in.
/// </summary>
void Player::UpdateAnimations(float dT)
{
	switch (_state)
	{
	case idle:
		if (_animSystem.GetCurrentAnim() != "PlayerIdle")
		{
			_animSystem.SetAnimation("PlayerIdle");
			_animSystem.Play();
		}
		break;
	case running:

		if ((_wasd.x < 0 && !isFlipped) || (_wasd.x > 0 && isFlipped))
			FlipSprite();

		if (_animSystem.GetCurrentAnim() != "PlayerRun")
		{
			_animSystem.SetAnimation("PlayerRun");
			_animSystem.Play();
		}
		break;
	}

	_animSystem.Update(dT);
}

void Player::HandleInputs()
{
	_wasd = b2Vec2_zero;
	if (_state == idle || _state == running)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_wasd.x = -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_wasd.x = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_wasd.y = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_wasd.y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (_playerBody->GetLinearVelocity().y == 0.0f)
		{
			float impulse = _playerBody->GetMass() * 1;
			_playerBody->ApplyLinearImpulse(b2Vec2(0, -impulse), _playerBody->GetWorldCenter(), true);
		}
	}
	
}

void Player::UpdatePhysics()
{
	_playerBody->ApplyForceToCenter(b2Vec2(_wasd.x * forceMult, 0.0f), true);

	sprite.setPosition(_playerBody->GetPosition().x * SCALE, _playerBody->GetPosition().y * SCALE);
}

void Player::InitAnimations()
{
	sf::IntRect frameRect = sf::IntRect(0, 0, 64, 40);
	sf::Vector2f frameOrigin = sf::Vector2f(32, 20);
	_animSystem.AddAnimation("PlayerIdle", PLAYER_IDLE, 0.5f, true, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerRun", PLAYER_RUN, 0.5f, true, frameRect, frameOrigin);
}

void Player::InitPhysics(sf::Vector2f pos, b2World* worldRef)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	bodyDef.type = b2_dynamicBody;
	_playerBody = worldRef->CreateBody(&bodyDef); 

	b2PolygonShape playerShape;
	playerShape.SetAsBox(_colBox.width / SCALE, _colBox.height / SCALE);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.8f;
	fixtureDef.shape = &playerShape;
	_playerBody->CreateFixture(&fixtureDef);
}