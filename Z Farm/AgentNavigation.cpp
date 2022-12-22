#include "AgentNavigation.h"

#include "Room.h"
#include "Node.h"

#include "Utilities.h"

#include <iostream>

std::vector<Node*> AgentNavigation::GeneratePath(sf::Vector2f goal, sf::Sprite* sprite, Room* room)
{
	std::vector<Node*> openSet;
	std::vector<Node*> returnSet;
	//std::map<Node*, Node*> cameFrom;

	Node* startNode = ZEngine::Utilities::GetNearestNode(sprite->getPosition(), room);
	Node* goalNode = ZEngine::Utilities::GetNearestNode(goal, room);

	openSet.push_back(startNode);

	float h = ZEngine::Utilities::GenerateHeuristic(startNode->GetNodeLocation(), goalNode->GetNodeLocation());

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
			Node* n = goalNode;
			returnSet.push_back(currentNode);
			/*while (cameFrom[n] != startNode)
			{
				returnSet.push_back(cameFrom[n]);
				n = cameFrom[n];
			}*/
			//std::reverse(returnSet.begin(), returnSet.end());
			return returnSet;
		}

		openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));

		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node::Edge neighbour = currentNode->edges[i];
			Node* neighbouringNode = ZEngine::Utilities::GetNearestNode(neighbour.destinationCoords, room);

			if (neighbouringNode == nullptr)
			{
				std::cout << "ERROR: AgentNavigation::GeneratePath --> neighbouringNode is invalid!" << std::endl;
				return std::vector<Node*>();
			}

			float tentative_gScore = gScore[currentNode].i + neighbour.cost;

			float neighbourScore = gScore[neighbouringNode].i;

			if (tentative_gScore < gScore[neighbouringNode].i)
			{
				//cameFrom[neighbour.node] = currentNode;
				returnSet.push_back(neighbouringNode);
				gScore[neighbouringNode].i = tentative_gScore;
				fScore[neighbouringNode].i = gScore[neighbouringNode].i + ZEngine::Utilities::GenerateHeuristic(neighbouringNode->GetNodeLocation(), goalNode->GetNodeLocation());
				if (std::find(openSet.begin(), openSet.end(), neighbouringNode) == openSet.end())
				{
					openSet.push_back(neighbouringNode);
				}
			}
		}
	}
	return std::vector<Node*>();
}
