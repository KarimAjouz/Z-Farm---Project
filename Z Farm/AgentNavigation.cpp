#include "AgentNavigation.h"

#include "Room.h"
#include "Node.h"

#include "Utilities.h"

#include <iostream>

AgentNavigation::AgentNavigation()
{
}

AgentNavigation::~AgentNavigation()
{
	
}

//void AgentNavigation::Init()
//{
//	Component::Init();
//}

void AgentNavigation::GeneratePath(sf::Vector2f goal, sf::Sprite* sprite, Room* room)
{
	std::vector<Node*> openSet;
	std::vector<Node*> returnSet;

	std::map<Node*, Node*> cameFrom;

	Node* startNode = ZEngine::Utilities::GetNearestNode(sprite->getPosition(), room);
	Node* goalNode = ZEngine::Utilities::GetNearestNode(goal, room);

	openSet.push_back(startNode);

	float h = GenerateHeuristic(startNode->GetNodeLocation(), goalNode->GetNodeLocation());

	std::map<Node*, Score> gScore;
	gScore[startNode].i = 0;

	std::map<Node*, Score> fScore;
	fScore[startNode].i = h;

	while (!openSet.empty())
	{
		Node* currentNode = openSet[0];

		//Sets the current node to be equal to the minimum fScore node in the open set
		for (int i = 0; i < openSet.size(); i++)
			if (fScore[openSet[i]].i < fScore[currentNode].i)
				currentNode = openSet[i];

		//Return true if a path is found.
		if (currentNode == goalNode)
		{
			ReconstructPath(cameFrom, currentNode);
			return;
		}

		openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));

		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node::Edge neighbour = currentNode->edges[i];
			Node* neighbouringNode = ZEngine::Utilities::GetNearestNode(neighbour.destinationCoords, room);

			if (neighbouringNode == nullptr)
			{
				std::cout << "ERROR: AgentNavigation::GeneratePath --> neighbouringNode is invalid!" << std::endl;
				Path = std::vector<Node*>();
				return;
			}

			float tentative_gScore = gScore[currentNode].i + neighbour.cost;

			if (tentative_gScore < gScore[neighbouringNode].i)
			{
				Node* nextNode = ZEngine::Utilities::GetNearestNode(currentNode->edges[i].destinationCoords, room);
				cameFrom[nextNode] = currentNode;
				gScore[neighbouringNode].i = tentative_gScore;
				fScore[neighbouringNode].i = gScore[neighbouringNode].i + GenerateHeuristic(neighbouringNode->GetNodeLocation(), goalNode->GetNodeLocation());

				if (std::find(openSet.begin(), openSet.end(), nextNode) == openSet.end())
				{
					openSet.push_back(nextNode);
				}
			}
		}
	}
	std::cout << "WARNING: AgentNavigation::GeneratePath --> Path not allocated!" << std::endl;
	Path = std::vector<Node*>();
}

/// <summary>
	/// Generates a heuristic for the pathfinding algorithm from two position vectors.
	/// </summary>
	/// <param name="a"> The first position vector. </param>
	/// <param name="b"> The second position vector. </param>
	/// <returns></returns>
float AgentNavigation::GenerateHeuristic(sf::Vector2f a, sf::Vector2f b)
{
	return (std::abs(a.x - b.x) / (TILE_SCALE * TILE_SIZE)) + (std::abs(a.y - b.y) / (TILE_SCALE * TILE_SIZE));

	return 0.0f;
}

void AgentNavigation::ReconstructPath(std::map<Node*, Node*> InCameFrom, Node* InCurrent)
{
	Path = std::vector<Node*>();
	Node* currentPathStep = InCurrent;

	while (InCameFrom[currentPathStep] != nullptr)
	{
		currentPathStep = InCameFrom[currentPathStep];
		Path.push_back(currentPathStep);
	}

	if (Path.size() == 0)
	{
		std::cout << "WARNING: AgentNavigation::ReconstructPath --> Generated Path is empty!" << std::endl;
		return;
	}

	std::reverse(Path.begin(), Path.end());
}

Node::Edge AgentNavigation::GetEdge(Node* currentNode, Node* nextNode, Room* room)
{
	for (Node::Edge edge : currentNode->edges)
	{
		if (ZEngine::Utilities::GetNearestNode(edge.destinationCoords, room) == nextNode)
			return edge;
	}
	return Node::Edge();
}
