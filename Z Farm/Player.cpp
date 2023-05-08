#include "Player.h"
#include "Utilities.h"
#include <iostream>

#include "PlayerPhysicsComponent.h"
#include "EquipmentComponent.h"

#include "TraversalState.h"
#include "EquipmentState.h"
#include "GameState_Gameplay.h"
#include "IdleState.h"
#include "SwordState.h"

/// <summary>
/// Constructs the player object, setting its texture.
/// </summary>
/// <param name="texPath"> The filepath for the player texture. </param>
/// <param name="pos"> The position to spwan the player in. </param>
Player::Player(sf::Vector2f pos, ZEngine::GameDataRef InData, BalanceSheet* b, b2World* InWorldRef, sf::Vector2f* viewTargetRef, Level* levelRef) :
	Agent(InData, InWorldRef),
	//m_TraversalState(new IdleState),
	_viewTargetRef(viewTargetRef),
	_levelRef(levelRef),
	_stabDelay(0.1f, false),
	m_InputManager()
{
	InitAnimations();

	m_Sprite.setPosition(pos);
	m_Sprite.setScale(2.0f, 2.0f);
	m_Sprite.setOrigin(32, 20);

	SetTraversalState(new IdleState);

	m_AnimationComponent = new PlayerAnimationComponent(GetSprite(), InData);
	m_PhysicsComponent = new PlayerPhysicsComponent(InData, InWorldRef, this);
	m_EquipmentComponent = new EquipmentComponent(InData, 2);
	SetEquipmentState(new EquipmentState());

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
	m_InputManager->HandleInputEvents(m_Data->GameWindow);

	m_TraversalState->Update(dT, *this);
	UpdatePhysics(dT);
	UpdateAnimations(dT);
}

void Player::Draw()
{
	Agent::Draw();
}

void Player::HandleContactBegin(PhysicsUserData* InCollidingUserData, ECollisionTag InMyCollidedFixture)
{
	if (InMyCollidedFixture == ECollisionTag::CT_PlayerFoot)
	{
		if (InCollidingUserData->CollisionTag == CT_Box || InCollidingUserData->CollisionTag == CT_Level)
			footContacts++;
	}
}

void Player::HandleContactEnd(PhysicsUserData* InCollidingUserData, ECollisionTag InMyCollidedFixture)
{
	if (InMyCollidedFixture == ECollisionTag::CT_PlayerFoot)
	{
		if (InCollidingUserData->CollisionTag == CT_Box || InCollidingUserData->CollisionTag == CT_Level)
			footContacts--;
	}
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
	SetEquipmentState(new SwordState);
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

	PlayerPhysicsComponent* physicsComp = dynamic_cast<PlayerPhysicsComponent*>(m_PhysicsComponent);

	if (physicsComp->Jump())
	{
		return true;
	}
	return false;
}

void Player::FlipSprite()
{
	ZEngine::Agent::FlipSprite();

	m_EquipmentState->FlipEquipment();
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

		if (m_EquipmentState && m_AnimationComponent && InNewTraversalState->GetTraversalType() != ETraversalType::TT_Attack)
		{
			m_AnimationComponent->SetAnimation(m_TraversalState->GetTraversalType(), m_EquipmentState->GetEquipmentType());
			m_AnimationComponent->Play();
		}
	}
}

void Player::SetEquipmentState(EquipmentState* InNewEquipmentState)
{
	if (InNewEquipmentState != NULL)
	{
		delete m_EquipmentState;
		m_EquipmentState = InNewEquipmentState;
		m_EquipmentState->Enter(*this);

		if (m_TraversalState && m_AnimationComponent)
		{
			m_AnimationComponent->SetAnimation(m_TraversalState->GetTraversalType(), m_EquipmentState->GetEquipmentType());
			m_AnimationComponent->Play();
		}
	}
}

void Player::HandleInput(sf::Event* InputEvent)
{
	TraversalState* traversalState = dynamic_cast<TraversalState*>(m_TraversalState->HandleInput(*this, InputEvent));

	TraversalState* EquipmentChosenState = dynamic_cast<TraversalState*>(m_EquipmentState->HandleInput(*this, InputEvent));

	if (EquipmentChosenState != NULL)
	{
		std::cout << "WE NEW JUMPIN NOW TEAM " << std::endl;
		SetTraversalState(EquipmentChosenState);
		return;
	}

	if (traversalState != NULL)
	{
		std::cout << "WE NEW JUMPIN NOW TEAM " << std::endl;
		SetTraversalState(traversalState);
	}
}