#pragma once

// Includes
#include "Component.h"

// Library Includes
#include "SFML/Graphics.hpp"

// Core Includes
#include <vector>

// Forward Declarations ------------------------------------------------------------------------------------------------------->
class Room;
class Node;

struct Score
{
	float i = 999;
};

class AgentNavigation : public ZEngine::Component
{
public:
	AgentNavigation();
	~AgentNavigation();

	virtual void Init() override;

	std::vector<Node*> GeneratePath(sf::Vector2f goal, sf::Sprite* sprite, Room* room);

};

