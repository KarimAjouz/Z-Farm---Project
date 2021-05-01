#pragma once
#include "Agent.h"

class Enemy : public Agent
{
public:
	Enemy();
	~Enemy();

	bool CanSeePlayer();
};

