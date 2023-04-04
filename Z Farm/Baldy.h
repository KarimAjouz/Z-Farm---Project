//#pragma once
//
//#include "Enemy.h"
//#include "AnimationSystem.h"
//#include "Room.h"
//#include "AgentNavigation.h"
//
//class Baldy : public Enemy
//{
//public:
//	Baldy(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f pos, Room* myRoom);
//	~Baldy();
//
//	void Update(float dT);
//	void Draw();
//
//	void Hit();
//	void Hit(sf::Vector2f playerPos);
//
//	void Repath(sf::Vector2f pos);
//
//	bool move;
//private:
//	ZEngine::GameDataRef _data;
//	Room* _myRoom;
//
//	//Generic State for deciding animations
//	enum class AnimState
//	{
//		idle,
//		moving,
//		guard,
//		attack,
//		death,
//		preJump,
//		jumping,
//		falling,
//		landing
//	};
//
//	//Specific BaldyState handles primary AI decisions
//	enum class BaldyAIState
//	{
//		passive,
//		questioning,
//		alert,
//		returning
//	};
//
//	std::string _AIStateStrings[4] = { "passive", "questioning", "alert", "returning" };
//
//	enum class BaldyState
//	{
//		moving,
//		idle,
//		wary,
//		attacking
//	};
//
//	std::string _StateStrings[4] = { "moving", "idle", "wary", "attacking" };
//
//
//	AnimState _animState;
//	BaldyAIState _AIState;
//	BaldyState _state;
//
//	ZEngine::Timer _watchTimer;
//	ZEngine::Timer _resetTimer;
//	ZEngine::Timer _questionTimer;
//
//	sf::Vector2f _lastSeenPlayerPos;
//
//	void UpdateAnimations();
//	void UpdateState();
//
//	ZEngine::AnimationSystem _animSys;
//
//	void InitAnimations();
//	void InitPhysics(sf::Vector2f pos);
//
//	bool _alert = false;
//	float _jumpForce = 9.81f;
//
//
//
//
//	sf::Vector2f _targetPosition = sf::Vector2f(900, 560);
//
//
//	bool SeekTarget(sf::Vector2f TargetPos);
//	sf::CircleShape targetNodeCircle;
//
//
//	//float _desiredVelocity = 0.0f;
//	float _curSpeed = 0.0f;
//	float _walkSpeed = 4.0f;
//	float _runSped = 6.0f;
//	bool _jumping = false;
//	int _jumpTimeout = 0;
//
//	void Move(int dir);
//	void Jump(sf::Vector2f force);
//
//	void Patrol();
//	void StartWatch();
//	void ReturnHome();
//
//	ZEngine::Timer _attackCooldown;
//	ZEngine::Timer _attackDelay;
//	std::map<Agent*, int> _nearbyAgents;
//
//	float _MaxAttackTriggerDistanceSquared = 1400.f;
//
//	void BeginAttack(int dir);
//
//	void TestKick();
//
//	AgentNavigation* _navComponent;
//
//};
//
