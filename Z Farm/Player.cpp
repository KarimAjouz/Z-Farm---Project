#include "Player.h"
#include <iostream>

/// <summary>
/// Constructs the player object, setting its texture.
/// </summary>
/// <param name="texPath"> The filepath for the player texture. </param>
/// <param name="pos"> The position to spwan the player in. </param>
Player::Player(sf::Vector2f pos, ZEngine::GameDataRef data, BalanceSheet* b, b2World* worldRef) :
	_data(data),
	_state(State::idle),
	_worldRef(worldRef)
{
	InitAnimations();

	sprite.setPosition(pos);
	sprite.setScale(2.0f, 2.0f);
	sprite.setOrigin(32, 20);


	InitPhysics(pos, _worldRef);

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
	float yVel = _playerBody->GetLinearVelocity().y;
	if (abs(yVel) < 0.1f)
		yVel = 0.0f;

	switch (_state)
	{
		case Player::State::idle:
			if (_wasd.x != 0)
				_state = State::running;
			break;
		case Player::State::running:
			if (_wasd.x == 0)
			_state = State::idle;
			break;
		case Player::State::jumping:
			if (yVel > 0)
				_state = State::falling;
			break;
		case Player::State::falling:
			if (footContacts > 0)
			{
				_animSystem.SetAnimation("PlayerLand");
				_animSystem.Play();
				_state = State::idle;
			}
			break;
		case Player::State::windUp:
			break;
		case Player::State::attack:
			break;
		case Player::State::hit:
			break;
		case Player::State::dying:
			break;
		default:
			break;
	}
}

/// <summary>
/// Decides which animation to switch to depending on the state the entity is in.
/// </summary>
void Player::UpdateAnimations(float dT)
{
 	switch (_state)
	{
	case State::idle:
		if (_animSystem.GetCurrentAnim() == "PlayerLand" && _animSystem.Complete())
		{
			_animSystem.SetAnimation("PlayerIdle");
			_animSystem.Play();
		}
		else if ((_animSystem.GetCurrentAnim() != "PlayerIdle" && _animSystem.GetCurrentAnim() != "PlayerLand"))
		{
			_animSystem.SetAnimation("PlayerIdle");
			_animSystem.Play();
		}
		break;
	case State::running:

		if ((_wasd.x < 0 && !isFlipped) || (_wasd.x > 0 && isFlipped))
			FlipSprite();

		if (_animSystem.GetCurrentAnim() == "PlayerLand" && _animSystem.Complete())
		{
			_animSystem.SetAnimation("PlayerRun");
			_animSystem.Play();
		}
		else if ((_animSystem.GetCurrentAnim() != "PlayerRun" && _animSystem.GetCurrentAnim() != "PlayerLand"))
		{
			_animSystem.SetAnimation("PlayerRun");
			_animSystem.Play();
		}
		break;
	case State::jumping:
		if (_animSystem.GetCurrentAnim() != "PlayerJump")
		{
			_animSystem.SetAnimation("PlayerJump");
			_animSystem.Play();
		}
		break;
	case State::falling:
		if (_animSystem.GetCurrentAnim() != "PlayerFall")
		{
			_animSystem.SetAnimation("PlayerFall");
			_animSystem.Play();
		}

		break;
	}

	_animSystem.Update(dT);
}

void Player::HandleInputs()
{
	b2Vec2 vel = _playerBody->GetLinearVelocity();
	_wasd = sf::Vector2i();

	if (_state == State::idle || _state == State::running || _state == State::jumping || _state == State::falling)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_wasd.x -= 1;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_wasd.x += 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_wasd.y = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_wasd.y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && footContacts > 0 && _jumpTimeout < 0)
		_jumping = true;
	else
		_jumping = false;
	
}

void Player::UpdatePhysics()
{
	b2Vec2 vel = _playerBody->GetLinearVelocity();

	switch (_wasd.x)
	{
		case -1:
			_desiredVelocity = b2Max(vel.x - 0.1f, -5.0f);
			break;
		case 0:
			_desiredVelocity = vel.x * 0.95f;
			break;
		case 1:
			_desiredVelocity = b2Min(vel.x + 0.1f, 5.0f);
			break;
	}

	float velChange = _desiredVelocity - vel.x;
	float impulse = _playerBody->GetMass() * velChange; //disregard time factor

	_playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0), _playerBody->GetWorldCenter(), true);

	if (_jumping && footContacts > 0 && _jumpTimeout < 0)
	{
		float impulse = _playerBody->GetMass() * 10;
		_playerBody->SetLinearVelocity(b2Vec2(_playerBody->GetLinearVelocity().x, 0.0f));
		_playerBody->ApplyLinearImpulse(b2Vec2(0, -impulse), _playerBody->GetWorldCenter(), true);
		_jumpTimeout = 15;
		_state = State::jumping;
	}
	else if (_jumpTimeout >= 0)
		_jumpTimeout--;


	sprite.setPosition(_playerBody->GetPosition().x * SCALE, _playerBody->GetPosition().y * SCALE);
}

void Player::InitAnimations()
{
	sf::IntRect frameRect = sf::IntRect(0, 0, 64, 40);
	sf::Vector2f frameOrigin = sf::Vector2f(32, 20);
	_animSystem.AddAnimation("PlayerIdle", PLAYER_IDLE, 0.5f, true, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerRun", PLAYER_RUN, 0.5f, true, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerJump", PLAYER_JUMP, 0.3f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerFall", PLAYER_FALL, 0.1f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerLand", PLAYER_LAND, 0.2f, false, frameRect, frameOrigin);
}

void Player::InitPhysics(sf::Vector2f pos, b2World* worldRef)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	bodyDef.type = b2_dynamicBody;
	_playerBody = worldRef->CreateBody(&bodyDef); 
	_playerBody->SetFixedRotation(true);
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(_colBox.width / SCALE, _colBox.height / SCALE);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;

	//fixtureDef.friction = 0.8f;
	myFixtureDef.restitution = 0.0f;
	myFixtureDef.shape = &polygonShape;
	_playerBody->CreateFixture(&myFixtureDef);

	//add foot sensor fixture
	polygonShape.SetAsBox(0.3, 0.3, b2Vec2(0, (static_cast<float>(_colBox.height) * abs(sprite.getScale().y) / 2) / SCALE), 0);
	myFixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = _playerBody->CreateFixture(&myFixtureDef);
	footSensorFixture->GetUserData().pointer = static_cast<int>(CollisionTag::playerFoot);
}