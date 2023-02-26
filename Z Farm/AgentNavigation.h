#pragma once

// Includes
#include "Component.h"
#include "Node.h"

// Library Includes
#include "SFML/Graphics.hpp"

// Core Includes
#include <vector>

// Forward Declarations ------------------------------------------------------------------------------------------------------->
class Room;

struct Score
{
	float i = INT_MAX;
};

class AgentNavigation /*: public ZEngine::Component*/
{
public:
	AgentNavigation(ZEngine::GameDataRef InData);
	~AgentNavigation();

	//virtual void Init() override;

	void GeneratePath(sf::Vector2f goal, sf::Sprite* sprite, Room* room);
	float GenerateHeuristic(sf::Vector2f a, sf::Vector2f b);

	std::vector<Node*> Path;

	void ReconstructPath(std::map<Node*, Node*> InCameFrom, Node* InCurrent);

	Node::Edge GetEdge(Node* currentNode, Node* nextNode, Room* room);

	void DebugDrawEdge(Node::Edge edge, Node* node);

	ZEngine::GameDataRef _data;
};

