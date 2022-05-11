#pragma once
#include "Agent.h"
#include "Player.h"
#include "AlertBubble.h"

class Enemy : public Agent
{
public:
	Enemy(ZEngine::GameDataRef data, b2World* world);
	~Enemy();

	bool CanSeePlayer();
	bool CanSeePlayer(sf::Vector2f* lastSeenPosRef);

	b2World* worldRef;
	sf::Vector2f dialogueOffset;
	AlertBubble alertBubble;

	ZEngine::Timer questionTimer;

	b2Body* playerBody = nullptr;

	void AssignPlayerBody();
};

