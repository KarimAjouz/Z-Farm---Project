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

	void UpdateAnimations();
	void UpdateState();

	ZEngine::AnimationSystem _animSys;

	void InitAnimations();
	void InitPhysics(sf::Vector2f pos);

	bool CanSeePlayer();

	std::vector<Node*> PathFind(sf::Vector2f goal);
	Node* GetNearestNode(sf::Vector2f pos);
	float GenerateHeuristic(sf::Vector2f a, sf::Vector2f b);

	struct Score
	{
		float i = 999;
	};

	sf::Vector2f _targetPosition = sf::Vector2f(900, 560);
	std::vector<Node*> _path;

};

