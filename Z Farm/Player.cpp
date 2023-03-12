#include "Player.h"
#include <iostream>

/// <summary>
/// Constructs the player object, setting its texture.
/// </summary>
/// <param name="texPath"> The filepath for the player texture. </param>
/// <param name="pos"> The position to spwan the player in. </param>
Player::Player(sf::Vector2f pos, ZEngine::GameDataRef data, BalanceSheet* b, b2World* worldRef, sf::Vector2f* viewTargetRef, Level* levelRef) :
	_data(data),
	_state(State::idle),
	_worldRef(worldRef),
	_viewTargetRef(viewTargetRef),
	_levelRef(levelRef),
	_stabDelay(0.1f, false)
{
	InitAnimations();

	sprite.setPosition(pos);
	sprite.setScale(2.0f, 2.0f);
	sprite.setOrigin(32, 20);

	type = Agent::Type::player;
	InitPhysics(pos);

	_animSystem.SetAnimation("PlayerIdle");
	_animSystem.Play();

	_lStab.setOrigin(24, 12);
	_rStab.setOrigin(24, 12);

	SetView();
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
	_data->GameWindow.draw(sprite);
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
			if(yVel > -7.0f)
				_playerBody->SetGravityScale(3.0f);

			if (yVel > 0)
			{
				_state = State::falling;
			}
			break;
		case Player::State::falling:
			if (footContacts > 0)
			{
				if (!_swordActive)
					_animSystem.SetAnimation("PlayerLand");
				else
					_animSystem.SetAnimation("PlayerLandSword");

				_animSystem.Play();
				_state = State::idle;
				_playerBody->SetGravityScale(1.0f);

			}
			break;
		case Player::State::windUp:
			break;
		case Player::State::attack:
			if (_animSystem.GetCurrentAnim() == "PlayerStab" && _animSystem.Complete())
				_state = State::idle;
			break;
		case Player::State::hit:
			break;
		case Player::State::dying:
			if (_animSystem.GetCurrentAnim() == "PlayerDeath" && _animSystem.Complete())
			{
				_state = State::idle;
				_playerBody->SetTransform(b2Vec2(200.0f / SCALE, 400.0f / SCALE), 0.0f);
				sprite.setPosition(200, 400);
				SetView();
			}
			break;
		default:
			break;
	}


	_lStab.setPosition(sf::Vector2f(sprite.getPosition().x - 36.0f, sprite.getPosition().y + _lStab.getOrigin().y + 4.0f));
	_rStab.setPosition(sf::Vector2f(sprite.getPosition().x + 60.0f, sprite.getPosition().y + _rStab.getOrigin().y + 4.0f));
}

/// <summary>
/// Decides which animation to switch to depending on the state the entity is in.
/// </summary>
void Player::UpdateAnimations(float dT)
{
	// Check to see if we need to use the sword animations or the non-sword animations.
	if (_swordActive)
	{
		switch (_state)
		{
		case State::idle:
			if (_animSystem.GetCurrentAnim() == "PlayerIdleSword" && _animSystem.Complete())
			{
				_animSystem.SetAnimation("PlayerIdleSword");
				_animSystem.Play();
			}
			else if ((_animSystem.GetCurrentAnim() != "PlayerIdleSword" && _animSystem.GetCurrentAnim() != "PlayerLandSword"))
			{
				_animSystem.SetAnimation("PlayerIdleSword");
				_animSystem.Play();
			}
			break;
		case State::running:

			if ((_wasd.x < 0 && !isFlipped) || (_wasd.x > 0 && isFlipped))
				FlipSprite();

			if (_animSystem.GetCurrentAnim() == "PlayerLandSword" && _animSystem.Complete())
			{
				_animSystem.SetAnimation("PlayerRunSword");
				_animSystem.Play();
			}
			else if ((_animSystem.GetCurrentAnim() != "PlayerRunSword" && _animSystem.GetCurrentAnim() != "PlayerLandSword"))
			{
				_animSystem.SetAnimation("PlayerRunSword");
				_animSystem.Play();
			}
			break;
		case State::jumping:
			if (_animSystem.GetCurrentAnim() != "PlayerJumpSword")
			{
				_animSystem.SetAnimation("PlayerJumpSword");
				_animSystem.Play();
			}
			break;
		case State::falling:
			if (_animSystem.GetCurrentAnim() != "PlayerFallSword")
			{
				_animSystem.SetAnimation("PlayerFallSword");
				_animSystem.Play();
			}

			break;
		case State::attack:
			if (_animSystem.GetCurrentAnim() != "PlayerStab")
			{
				_animSystem.SetAnimation("PlayerStab");
				_animSystem.Play();
			}

			if (_stabDelay.Complete())
				TestStab();

			break;
		case State::dying:
			if (_animSystem.GetCurrentAnim() != "PlayerDeath")
			{
				_animSystem.SetAnimation("PlayerDeath");
				_animSystem.Play();
			}
			break;
		}
	}
	else
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
		case State::dying:
			if (_animSystem.GetCurrentAnim() != "PlayerDeath")
			{
				_animSystem.SetAnimation("PlayerDeath");
				_animSystem.Play();
			}
			break;
		}
	}


	_animSystem.Update(dT);
}

void Player::Hit()
{
	_state = State::dying;
}

void Player::Hit(sf::Vector2f enemyPos)
{
	_state = State::dying;
}

void Player::EquipSword()
{
	_swordActive = true;
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


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && footContacts > 0 && _jumpTimeout < 0)
			_jumping = true;
		else
			_jumping = false;
	}
}

void Player::UpdatePhysics()
{
	b2Vec2 vel = _playerBody->GetLinearVelocity();

	switch (_wasd.x)
	{
	case -1:
		_desiredVelocity = b2Max(vel.x - 0.3f, -5.0f);
		break;
	case 0:
		_desiredVelocity = vel.x * 0.95f;
		break;
	case 1:
		_desiredVelocity = b2Min(vel.x + 0.3f, 5.0f);
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
	_animSystem.AddAnimation("PlayerIdle",      PLAYER_IDLE,             0.5f, true,  frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerRun",       PLAYER_RUN,              0.5f, true,  frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerJump",      PLAYER_JUMP,             0.3f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerFall",      PLAYER_FALL,             0.1f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerLand",      PLAYER_LAND,             0.3f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerDeath",     PLAYER_DEATH,            0.4f, false, frameRect, frameOrigin);

	_animSystem.AddAnimation("PlayerIdleSword", PLAYER_IDLE_SWORD,       0.5f, true,  frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerRunSword",  PLAYER_RUN_SWORD,        0.5f, true,  frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerJumpSword", PLAYER_JUMP_SWORD,       0.3f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerFallSword", PLAYER_FALL_SWORD,       0.1f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerLandSword", PLAYER_LAND_SWORD,       0.2f, false, frameRect, frameOrigin);

	_animSystem.AddAnimation("PlayerStab",      PLAYER_STAB_ATTACK,      0.3f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerUpSlash",   PLAYER_UPSLASH_ATTACK,   0.3f, false, frameRect, frameOrigin);
	_animSystem.AddAnimation("PlayerDownSlash", PLAYER_DOWNSLASH_ATTACK, 0.3f, false, frameRect, frameOrigin);
}

void Player::InitPhysics(sf::Vector2f pos)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	bodyDef.type = b2_dynamicBody;
	_playerBody = _worldRef->CreateBody(&bodyDef);
	_playerBody->SetFixedRotation(true);


	b2PolygonShape polygonShape;
	//polygonShape.SetAsBox(_colBox.width / SCALE, _colBox.height / SCALE);
	b2CircleShape circleShape;
	circleShape.m_radius = _colBox.width / SCALE;
	circleShape.m_p = b2Vec2(0, _colBox.height / 2 / SCALE);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;

	myFixtureDef.restitution = 0.1f;
	myFixtureDef.shape = &circleShape;

	myFixtureDef.filter.categoryBits = _entityCategory::AGENTS;
	myFixtureDef.filter.maskBits = _entityCategory::LEVEL | _entityCategory::OBSTACLES | _entityCategory::AGENTS | _entityCategory::DAMAGE;

	b2Fixture* playerFixture = _playerBody->CreateFixture(&myFixtureDef);
	playerFixture->GetUserData().pointer = static_cast<int>(CollisionTag::player);


	//add foot sensor fixture
	polygonShape.SetAsBox(10 / SCALE, 10 / SCALE, b2Vec2(0, (static_cast<float>(_colBox.height) * abs(sprite.getScale().y)) / SCALE), 0);
	myFixtureDef.isSensor = true;
	myFixtureDef.shape = &polygonShape;

	myFixtureDef.filter.categoryBits = _entityCategory::LEVEL;
	myFixtureDef.filter.maskBits = _entityCategory::LEVEL;

	b2Fixture* footSensorFixture = _playerBody->CreateFixture(&myFixtureDef);
	footSensorFixture->GetUserData().pointer = static_cast<int>(CollisionTag::playerFoot);


	//Prepare the stab sensors
	myFixtureDef.filter.categoryBits = _entityCategory::DAMAGE;
	myFixtureDef.filter.maskBits = _entityCategory::OBSTACLES | _entityCategory::AGENTS;

	//add right stab sensor 
	polygonShape.SetAsBox(10 / SCALE, 3 / SCALE, b2Vec2(48 / SCALE, 8 / SCALE), 0);
	myFixtureDef.isSensor = true;
	b2Fixture* rightStab = _playerBody->CreateFixture(&myFixtureDef);
	rightStab->GetUserData().pointer = static_cast<int>(CollisionTag::playerSword);


	//add left stab sensor
	polygonShape.SetAsBox(10 / SCALE, 3 / SCALE, b2Vec2(-48 / SCALE, 8 / SCALE), 0);
	myFixtureDef.isSensor = true;
	b2Fixture* leftStab = _playerBody->CreateFixture(&myFixtureDef);
	leftStab->GetUserData().pointer = static_cast<int>(CollisionTag::playerSword);

}

void Player::SetView()
{
	
}

void Player::Stab()
{
	if (_swordActive && (_state == State::idle || _state == State::running))
	{
		_state = State::attack;
		_stabDelay.Start();
	}
}

void Player::TestStab()
{
	if (isFlipped)
	{
		for (int i = 0; i < _levelRef->GetObstacles().size(); i++)
		{
			if (_lStab.getGlobalBounds().intersects(_levelRef->GetObstacles().at(i)->hitbox.getGlobalBounds()))
				_levelRef->GetObstacles().at(i)->Hit(sprite.getPosition());
		}
	}
	else if (!isFlipped)
	{
		for (int i = 0; i < _levelRef->GetObstacles().size(); i++)
		{
			if (_rStab.getGlobalBounds().intersects(_levelRef->GetObstacles().at(i)->hitbox.getGlobalBounds()))
				_levelRef->GetObstacles().at(i)->Hit(sprite.getPosition());
		}
	}

}