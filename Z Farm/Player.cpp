#include "Player.h"
#include "Utilities.h"
#include <iostream>

#include "PlayerPhysicsComponent.h"

#include "TraversalState.h"
#include "GameState_Gameplay.h"
#include "IdleState.h"

/// <summary>
/// Constructs the player object, setting its texture.
/// </summary>
/// <param name="texPath"> The filepath for the player texture. </param>
/// <param name="pos"> The position to spwan the player in. </param>
Player::Player(sf::Vector2f pos, ZEngine::GameDataRef InData, BalanceSheet* b, b2World* worldRef, sf::Vector2f* viewTargetRef, Level* levelRef) :
	Agent(InData),
	//m_State(new IdleState),
	_worldRef(worldRef),
	_viewTargetRef(viewTargetRef),
	_levelRef(levelRef),
	_stabDelay(0.1f, false),
	m_InputManager()
{
	InitAnimations();

	m_Sprite.setPosition(pos);
	m_Sprite.setScale(2.0f, 2.0f);
	m_Sprite.setOrigin(32, 20);

	m_AnimationComponent = new PlayerAnimationComponent(GetSprite(), InData);

	m_TraversalState = new IdleState();
	m_TraversalState->Enter(*this);

	m_PhysicsComponent = new PlayerPhysicsComponent(InData, worldRef, this);



	type = ZEngine::AgentType::AT_Player;
	InitPhysics(pos);

	//m_AnimationComponent->SetAnimation("PlayerIdle");
	//m_AnimationComponent->Play();

	_lStab.setOrigin(24, 12);
	_rStab.setOrigin(24, 12);

	SetView();
}


Player::~Player()
{
}

void Player::Update(float dT)
{
	m_PhysicsComponent->Update(dT);
	m_InputManager->HandleInputEvents(m_data->GameWindow);

	m_TraversalState->Update(dT, *this);
	UpdatePhysics(dT);
	UpdateAnimations(dT);

}

void Player::Draw()
{
	m_data->GameWindow.draw(m_Sprite);

	/*if (_interactable != nullptr)
	{
		sf::CircleShape circleInteract;
		circleInteract.setRadius(3.0f);
		circleInteract.setOrigin(sf::Vector2f(3.0f, 3.0f));
		circleInteract.setPosition(_interactable->sprite.getPosition());
		circleInteract.setFillColor(sf::Color::Cyan);
		circleInteract.setOutlineColor(sf::Color::Cyan);
		circleInteract.setOutlineThickness(1.0f);

		_data->GameWindow.draw(circleInteract);
	}*/
}


/// <summary>
/// Handles the state system logic.
/// </summary>
//void Player::UpdateState()
//{
//	float yVel = _playerBody->GetLinearVelocity().y;
//	if (abs(yVel) < 0.1f)
//		yVel = 0.0f;
//
//	switch (_state)
//	{
//		case Player::State::jumping:
//			if(yVel > -7.0f)
//				_playerBody->SetGravityScale(3.0f);
//
//			if (yVel > 0)
//			{
//				_state = State::falling;
//			}
//			break;
//		case Player::State::falling:
//			if (footContacts > 0)
//			{
//				if (!_swordActive)
//					m_AnimationComponent->SetAnimation("PlayerLand");
//				else
//					m_AnimationComponent->SetAnimation("PlayerLandSword");
//
//				m_AnimationComponent->Play();
//				_state = State::idle;
//				_playerBody->SetGravityScale(1.0f);
//
//			}
//			break;
//		case Player::State::windUp:
//			break;
//		case Player::State::attack:
//			if (m_AnimationComponent->GetCurrentAnim() == "PlayerStab" && m_AnimationComponent->Complete())
//				_state = State::idle;
//			break;
//		case Player::State::hit:
//			break;
//		case Player::State::dying:
//			if (m_AnimationComponent->GetCurrentAnim() == "PlayerDeath" && m_AnimationComponent->Complete())
//			{
//				_state = State::idle;
//				_playerBody->SetTransform(b2Vec2(200.0f / SCALE, 400.0f / SCALE), 0.0f);
//				m_Sprite.setPosition(200, 400);
//				SetView();
//			}
//			break;
//		default:
//			break;
//	}
//
//
//	_lStab.setPosition(sf::Vector2f(m_Sprite.getPosition().x - 36.0f, m_Sprite.getPosition().y + _lStab.getOrigin().y + 4.0f));
//	_rStab.setPosition(sf::Vector2f(m_Sprite.getPosition().x + 60.0f, m_Sprite.getPosition().y + _rStab.getOrigin().y + 4.0f));
//}

/// <summary>
/// Decides which animation to switch to depending on the state the entity is in.
/// </summary>
void Player::UpdateAnimations(float dT)
{
	//// Check to see if we need to use the sword animations or the non-sword animations.
	//if (_swordActive)
	//{
	//	switch (_state)
	//	{
	//	case State::idle:
	//		if (m_AnimationComponent->GetCurrentAnim() == "PlayerIdleSword" && m_AnimationComponent->Complete())
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerIdleSword");
	//			m_AnimationComponent->Play();
	//		}
	//		else if ((m_AnimationComponent->GetCurrentAnim() != "PlayerIdleSword" && m_AnimationComponent->GetCurrentAnim() != "PlayerLandSword"))
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerIdleSword");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	case State::running:

	//		if ((_wasd.x < 0 && !isFlipped) || (_wasd.x > 0 && isFlipped))
	//			FlipSprite();

	//		if (m_AnimationComponent->GetCurrentAnim() == "PlayerLandSword" && m_AnimationComponent->Complete())
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerRunSword");
	//			m_AnimationComponent->Play();
	//		}
	//		else if ((m_AnimationComponent->GetCurrentAnim() != "PlayerRunSword" && m_AnimationComponent->GetCurrentAnim() != "PlayerLandSword"))
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerRunSword");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	case State::jumping:
	//		if (m_AnimationComponent->GetCurrentAnim() != "PlayerJumpSword")
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerJumpSword");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	case State::falling:
	//		if (m_AnimationComponent->GetCurrentAnim() != "PlayerFallSword")
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerFallSword");
	//			m_AnimationComponent->Play();
	//		}

	//		break;
	//	case State::attack:
	//		if (m_AnimationComponent->GetCurrentAnim() != "PlayerStab")
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerStab");
	//			m_AnimationComponent->Play();
	//		}

	//		if (_stabDelay.Complete())
	//			TestStab();

	//		break;
	//	case State::dying:
	//		if (m_AnimationComponent->GetCurrentAnim() != "PlayerDeath")
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerDeath");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	}
	//}
	//else
	//{
	//	switch (_state)
	//	{
	//	case State::idle:
	//		if (m_AnimationComponent->GetCurrentAnim() == "PlayerLand" && m_AnimationComponent->Complete())
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerIdle");
	//			m_AnimationComponent->Play();
	//		}
	//		else if ((m_AnimationComponent->GetCurrentAnim() != "PlayerIdle" && m_AnimationComponent->GetCurrentAnim() != "PlayerLand"))
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerIdle");
	//			m_AnimationComponent->Play();
	//		}

	//		break;
	//	case State::running:

	//		if ((_wasd.x < 0 && !isFlipped) || (_wasd.x > 0 && isFlipped))
	//			FlipSprite();

	//		if (m_AnimationComponent->GetCurrentAnim() == "PlayerLand" && m_AnimationComponent->Complete())
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerRun");
	//			m_AnimationComponent->Play();
	//		}
	//		else if ((m_AnimationComponent->GetCurrentAnim() != "PlayerRun" && m_AnimationComponent->GetCurrentAnim() != "PlayerLand"))
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerRun");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	case State::jumping:
	//		if (m_AnimationComponent->GetCurrentAnim() != "PlayerJump")
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerJump");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	case State::falling:
	//		if (m_AnimationComponent->GetCurrentAnim() != "PlayerFall")
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerFall");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	case State::dying:
	//		if (m_AnimationComponent->GetCurrentAnim() != "PlayerDeath")
	//		{
	//			m_AnimationComponent->SetAnimation("PlayerDeath");
	//			m_AnimationComponent->Play();
	//		}
	//		break;
	//	}
	//}


	m_AnimationComponent->Update(dT);
}

void Player::Hit()
{
	//_state = State::dying;
}

void Player::Hit(sf::Vector2f enemyPos)
{
	//_state = State::dying;
}

void Player::EquipSword()
{
	//_swordActive = true;
}

//
//void Player::HandleInputs(sf::Event* InEvent)
//{
//	PlayerState* State = m_State->HandleInput(*this, InEvent);
//	if (m_State != NULL)
//	{
//		delete m_State;
//		m_State = State;
//	}
//}

void Player::UpdatePhysics(float dT)
{
	m_PhysicsComponent->Update(dT);
}

void Player::InitAnimations()
{

}

void Player::InitPhysics(sf::Vector2f pos)
{
	////Prepare the stab sensors
	//myFixtureDef.filter.categoryBits = _entityCategory::DAMAGE;
	//myFixtureDef.filter.maskBits = _entityCategory::OBSTACLES | _entityCategory::AGENTS;

	////add right stab sensor 
	//polygonShape.SetAsBox(10 / SCALE, 3 / SCALE, b2Vec2(48 / SCALE, 8 / SCALE), 0);
	//myFixtureDef.isSensor = true;
	//b2Fixture* rightStab = _playerBody->CreateFixture(&myFixtureDef);
	//rightStab->GetUserData().pointer = static_cast<int>(CollisionTag::playerSword);


	////add left stab sensor
	//polygonShape.SetAsBox(10 / SCALE, 3 / SCALE, b2Vec2(-48 / SCALE, 8 / SCALE), 0);
	//myFixtureDef.isSensor = true;
	//b2Fixture* leftStab = _playerBody->CreateFixture(&myFixtureDef);
	//leftStab->GetUserData().pointer = static_cast<int>(CollisionTag::playerSword);

}

void Player::SetView()
{
	
}

void Player::Stab()
{
	//if (_swordActive && (_state == State::idle || _state == State::running))
	//{
	//	_state = State::attack;
	//	_stabDelay.Start();
	//}
}

bool Player::Jump()
{
	if (footContacts <= 0 || _jumpTimeout > 0)
		return false;

	if (m_PhysicsComponent->Jump())
	{
		return true;
	}
	return false;
}

void Player::SetInputManagerState(GameState_Gameplay* InGameplayRef)
{
	m_InputManager = new InputManager(this, InGameplayRef);
}

//void Player::Interact()
//{
//	if (_interactable == nullptr)
//		return;
//
//	if (_bIsLatched)
//		JumpFromLatchable();
//	else
//		LatchToInteractable();
//}
//
//void Player::SetInteractable(RopeSegment* InRopeSegment)
//{
//	_interactable = InRopeSegment;
//}
//
//void Player::LatchToInteractable()
//{
//	if (_interactable == nullptr)
//		return;
//
//	b2Vec2 playerVelocity = _playerBody->GetLinearVelocity();
//
//	// Make joint between player & interactable
//	b2RevoluteJointDef myJointDef = b2RevoluteJointDef();
//	
//	myJointDef.bodyA = _playerBody;
//	myJointDef.bodyB = _interactable->body;
//	
//	b2Vec2 testPosition = b2Vec2(_interactable->sprite.getPosition().x / SCALE, _interactable->sprite.getPosition().y / SCALE);
//	b2Vec2 jointPosAnchorB = _interactable->body->GetPosition();
//
//	myJointDef.localAnchorB.Set(0, 0);
//
//	if (myJointDef.bodyB == nullptr)
//	{
//		std::cout << "Error: Player::LatchToInteractable --> bodyB is invalid!" << std::endl;
//		return;
//	}
//
//	myJointDef.collideConnected = false;
//	myJointDef.localAnchorA.Set(0, 0);
//
//	b2Joint* revoluteJoint = _worldRef->CreateJoint(&myJointDef);
//	_latchedJoint = revoluteJoint;
//	_wasd.x = 0;
//	_bIsLatched = true;
//	_state = State::latched;
//	_interactable->body->ApplyLinearImpulseToCenter(b2Vec2(10 * playerVelocity.x, 0), true);
//}
//
//void Player::JumpFromLatchable()
//{
//	_worldRef->DestroyJoint(_latchedJoint);
//	_state = State::jumping;
//	_jumping = true;
//}

void Player::SetTraversalState(TraversalState* InNewTraversalState)
{
	if (InNewTraversalState != NULL)
	{
		delete m_TraversalState;
		m_TraversalState = InNewTraversalState;
		m_TraversalState->Enter(*this);
	}
}

void Player::HandleInput(sf::Event* InputEvent)
{
	PlayerState* traversalState = m_TraversalState->HandleInput(*this, InputEvent);
	if (traversalState != NULL)
	{
		delete m_TraversalState;
		m_TraversalState = traversalState;
		m_TraversalState->Enter(*this);
	}
}