#pragma once
#include "Agent.h"
#include "Game.h"
#include "Gun.h"
#include "SaveDataManager.h"
#include "Timer.h"
#include "PlayerAnimationComponent.h"
#include "Level.h"
#include "Timer.h"
#include "RopeSegment.h"



#include <box2d.h>

#include <SFML/Graphics.hpp>

class Player
	: 
	public ZEngine::Agent
{
public:
	Player(sf::Vector2f pos, ZEngine::GameDataRef InData, BalanceSheet* b, b2World* worldRef, sf::Vector2f* viewTargetRef, Level* levelRef);
	~Player();

	void Update(float dT);
	void Draw();


	int footContacts = 0;

	void SetView();

	void Hit();
	void Hit(sf::Vector2f enemyPos);
	void EquipSword();

	void Stab();
	bool Jump();
	void Interact();

	void SetInputManagerState(class GameState_Gameplay* InGameplayRef);

	//void SetInteractable(RopeSegment* InRopeSegment);

	sf::Vector2f GetInputAxis() { return m_InputManager->GetInputAxis(); }
	
	PlayerAnimationComponent* GetAnimationComponent() { return m_AnimationComponent; }
	class PlayerPhysicsComponent* GetPhysicsComponent() { return m_PhysicsComponent; }
	InputManager* GetInputManager() { return m_InputManager; }


	void SetTraversalState(class TraversalState* InNewTraversalState);

	class PlayerState* GetTraversalState() { return m_TraversalState; }

	void HandleInput(sf::Event* InputEvent);

private:
	enum class EPlayerState
	{
		PS_Idle,
		PS_Running,
		PS_jumping,
		PS_falling,
		PS_windUp,
		PS_attack,
		PS_hit,
		PS_dying,
		PS_latched
	};

	/// #BeginComponents
	PlayerAnimationComponent* m_AnimationComponent;
	InputManager* m_InputManager;
	class PlayerPhysicsComponent* m_PhysicsComponent;

	// #EndComponents


	// #BeginStateMachines
	class PlayerState* m_TraversalState;

	// #EndStateMachines


	bool _swordActive = false;

	b2World* _worldRef;
	sf::Vector2i _wasd = sf::Vector2i();
	float _desiredVelocity = 0;
	

	ZEngine::Timer _stabDelay;

	int forceMult = 5;
	//ZEngine::GameDataRef _data;
	
	sf::IntRect _colBox = sf::IntRect(25, 16, 18, 12);

	sf::RectangleShape _lStab = sf::RectangleShape(sf::Vector2f(24, 12));
	sf::RectangleShape _rStab = sf::RectangleShape(sf::Vector2f(24, 12));


	sf::Vector2f* _viewTargetRef;
	Level* _levelRef;

	//b2Body* _playerBody = nullptr;
	b2Fixture* _footFixture = nullptr;
	b2Joint* _latchedJoint = nullptr;

	int _jumpTimeout = 0;
	bool _jumping = false;

	void HandleInputs(sf::Event* InEvent);
	void UpdatePhysics(float dT);
	
	void UpdateTraversalState(float dT);
	void UpdateAnimations(float dT);

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos);


	void LatchToInteractable();
	void JumpFromLatchable();

	bool _bIsLatched;

	//RopeSegment* _interactable;
	std::vector<sf::Event> _inputEvents;

	//PlayerState* m_State;
};

