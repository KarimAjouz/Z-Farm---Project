#include "Node.h"

Node::Node(sf::Vector2f pos)
{
	nodeArea.setPosition(pos);
	nodeArea.setRadius(10.0f);
	nodeArea.setOrigin(10.0f, 10.0f);
	nodeArea.setFillColor(sf::Color::Transparent);
	nodeArea.setOutlineColor(sf::Color::Green);
	nodeArea.setOutlineThickness(1.0f);
}

Node::~Node()
{

}

void Node::GenerateNodeList(std::vector<Node>* nodeMap, std::vector<Tile> tiles)
{
	bool lNode = false;
	bool rNode = false;

	//Here we are gonna test to see if there is a left and/or right node.
	//For every node in the Node Map...
	for (int i = 0; i < nodeMap->size(); i++)
	{
		//If the node is not this node...
		if (&nodeMap->at(i) != this)
		{
			//Get the relative location to this node.
			sf::Vector2f locationDifference = nodeMap->at(i).GetNodeLocation() - GetNodeLocation();
			
			//If the node is directly to the left or right of this node...
			if (locationDifference.y == 0.0f && std::abs(locationDifference.x) == 64.0f)
			{
				//Figure out which it was and set the according flag.
				if (locationDifference.x < 0)
					lNode = true;
				else if (locationDifference.x > 0)
					rNode = true;

				//Create and push back a new edge
				Edge edge;
				edge.cost = 1;
				edge.node = &nodeMap->at(i);
				edges.push_back(edge);
			}
		}
	}

	//Now we're going to check for our jump nodes.
	//For every node in the Node map...
	for (int i = 0; i < nodeMap->size(); i++)
	{
		//If the node is not this node...
		if (&nodeMap->at(i) != this)
		{
			//Get the relative location to this node.
			sf::Vector2f locationDifference = nodeMap->at(i).GetNodeLocation() - GetNodeLocation();

			//If there are no left/right nodes... 
			if (!lNode)
			{
				//Search for a left jump node on the same level.
				if (locationDifference.y == 0 && (locationDifference.x == -128.0f || locationDifference.x == -192.0f || locationDifference.x == -256.0f))
					edges.push_back(MakeEdge(&nodeMap->at(i), (std::abs(locationDifference.x) / 64) + 2));

			}

			if (!rNode)
			{
				//Search for a right jump node on the same level.
				if (locationDifference.y == 0 && (locationDifference.x == 128.0f || locationDifference.x == 192.0f || locationDifference.x == 256.0f))
					edges.push_back(MakeEdge(&nodeMap->at(i), (std::abs(locationDifference.x) / 64) + 2));
			}

			//Check for jump nodes one level up...
			if (locationDifference.y == 64.0f && std::abs(locationDifference.x) <= 192.0f && locationDifference.x != 0.0f)
				edges.push_back(MakeEdge(&nodeMap->at(i), (std::abs(locationDifference.x) / 64) + 3));

			//Check for jump nodes two levels up...
			if (locationDifference.y == 128.0f && std::abs(locationDifference.x) <= 128.0f && locationDifference.x != 0.0f)
				edges.push_back(MakeEdge(&nodeMap->at(i), (std::abs(locationDifference.x) / 64) + 4));

			//Check for jump nodes two levels up...
			if (locationDifference.y == 192.0f && std::abs(locationDifference.x) == 64.0f)
				edges.push_back(MakeEdge(&nodeMap->at(i), 4));
		}
	}

	//Finally, we check for drop nodes.
	//For every node in the Node map...
	for (int i = 0; i < nodeMap->size(); i++)
	{
		//If the node is not this node...
		if (&nodeMap->at(i) != this)
		{
			//Get the relative location to this node.
			sf::Vector2f locationDifference = nodeMap->at(i).GetNodeLocation() - GetNodeLocation();

			//Check for nodes below us and within 3 tiles either side.
			if (locationDifference.y < 0.0f && std::abs(locationDifference.x) <= 192.0f && locationDifference.x != 0.0f)
				edges.push_back(MakeEdge(&nodeMap->at(i), (std::abs(locationDifference.x) / 64) + 1));

		}
	}

}

Node::Edge Node::MakeEdge(Node* node, int cost)
{
	Edge edge;
	edge.cost = cost;
	edge.node = node;
	return edge;
}