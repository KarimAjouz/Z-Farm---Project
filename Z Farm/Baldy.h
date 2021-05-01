#pragma once

#include "Agent.h"
#include "AnimationSystem.h"
#include "Room.h"

class Baldy : public Agent
{
public:
	Baldy(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f pos, Room* myRoom);
	~Baldy();

	void Update(float dT);
	void Draw();

	void Hit();
	void Hit(sf::Vector2f playerPos);

	void Repath();

	bool move;
private:
	ZEngine::GameDataRef _data;
	Room* _myRoom;

	enum class State
	{
		idle,
		moving,
		guard,
		attack,
		death,
		jumping,
		falling
	};

	State _state;

	void UpdateAnimations();
	void UpdateState();

	ZEngine::AnimationSystem _animSys;

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos);

	bool CanSeePlayer();




	sf::Vector2f _targetPosition = sf::Vector2f(900, 560);
	std::vector<Node*> _path;


	bool SeekTarget();
	sf::CircleShape targetNodeCircle;


	float _desiredVelocity = 0.0f;
	bool _jumping = false;
	int _jumpTimeout = 0;

	void Move(int dir);
	void Jump(float force);

};

