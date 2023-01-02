#include "Node.h"

Node::Node()
{
}

Node::Node(sf::Vector2f pos) :
	platformIndex(0),
	type(Type::none)
{
	nodeArea = sf::CircleShape(16.0f);
	nodeArea.setPosition(pos);
	nodeArea.setOrigin(16.0f, 16.0f);
	nodeArea.setFillColor(sf::Color::Transparent);

	if (type == Type::platform)
		nodeArea.setFillColor(sf::Color::Green);
	else if (type == Type::leftPlatform || type == Type::rightPlatform)
		nodeArea.setFillColor(sf::Color::Magenta);
	else if (type == Type::soloPlatform)
		nodeArea.setFillColor(sf::Color::Yellow);

	nodeArea.setOutlineThickness(2.0f);

	platformsReached = std::map<int, reached>();
}

Node::Node(sf::Vector2f pos, int inIndex, Node::Type inType) :
	platformIndex(inIndex),
	type(inType)
{
	nodeArea = sf::CircleShape(16.0f);
	nodeArea.setPosition(pos);
	nodeArea.setOrigin(16.0f, 16.0f);
	nodeArea.setFillColor(sf::Color::Transparent);

	if (type == Type::platform)
		nodeArea.setOutlineColor(sf::Color::Green);
	else if (type == Type::leftPlatform || type == Type::rightPlatform)
		nodeArea.setOutlineColor(sf::Color::Magenta);
	else if (type == Type::soloPlatform)
		nodeArea.setOutlineColor(sf::Color::Yellow);

	nodeArea.setOutlineThickness(2.0f);
	platformsReached = std::map<int, reached>();
}

Node::~Node()
{

}

//void Node::GenerateNodeList(std::vector<Node*>* nodeMap, std::vector<Tile> tiles)
//{
//	bool nodePresence[14] = { false };
//
//	std::vector<Edge> es;
//
//
//	sf::Vector2f testPosition;
//	testPosition = GetNodeLocation();
//	Node* node;
//
//	//Test directly to the right. If there is a node there, make an edge.
//	testPosition.x += 64.0f;
//	node = GetNodeAtLocation(testPosition, nodeMap);
//	if(GetNodeAtLocation(testPosition, nodeMap) != nullptr)
//	{
//		edges.emplace_back(node, 0);
//		nodePresence[8] = true;
//	}
//	else if (CheckSpaceIsClear(sf::Vector2f(testPosition.x, testPosition.y), tiles)) //If there isn't a node or a solid tile there, search below for a drop node.
//	{
//		//Look one tile below.
//		testPosition.y += 64.0f;
//
//		//While we are not looking below the room, and this dropNode marker is empty...
//		while ( testPosition.y < SCREEN_HEIGHT && nodePresence[8] == false)
//		{
//			node = GetNodeAtLocation(testPosition, nodeMap);
//			//If there is a node here, add an edge.
//			if (node != nullptr)
//			{
//				edges.emplace_back(node, 1);
//				nodePresence[8] = true;
//			}
//			else
//				testPosition.y += 64.0f;
//		}
//	}
//
//	testPosition = GetNodeLocation();
//
//	//Test directly to the left. If there is a node there, make an edge.
//	testPosition.x -= 64.0f;
//	node = GetNodeAtLocation(testPosition, nodeMap);
//	if (node != nullptr)
//	{
//		edges.emplace_back(node, 0);
//		nodePresence[7] = true;
//	}
//	else if (CheckSpaceIsClear(testPosition, tiles)) //If there isn't a node or a solid tile there, search below for a drop node.
//	{
//		//Look one tile below.
//		testPosition.y += 64.0f;
//
//		//While we are not looking below the room, and this dropNode marker is empty...
//		while (testPosition.y < SCREEN_HEIGHT && nodePresence[7] == false)
//		{
//			node = GetNodeAtLocation(testPosition, nodeMap);
//			//If there is a node here, add an edge.
//			if (node != nullptr)
//			{
//				edges.emplace_back(node, 1);
//				nodePresence[7] = true;
//			}
//			else // Otherwise look one below
//				testPosition.y += 64.0f;
//		}
//	}
//
//	testPosition = GetNodeLocation();
//
//	//Test for a right jump node;
//	testPosition.x += 64.0f;
//	testPosition.y -= 64.0f;
//	node = GetNodeAtLocation(testPosition, nodeMap);
//	if (node != nullptr)
//	{
//		if (CheckSpaceIsClear(sf::Vector2f(testPosition.x - 64, testPosition.y), tiles))
//		{
//			edges.emplace_back(node, 2);
//			nodePresence[4] = true;
//		}
//	}
//	else if (CheckSpaceIsClear(sf::Vector2f(GetNodeLocation().x, GetNodeLocation().y - 64), tiles))
//	{
//		testPosition.y -= 64.0f;
//		node = GetNodeAtLocation(testPosition, nodeMap);
//		if (node != nullptr)
//		{
//			if (CheckSpaceIsClear(sf::Vector2f(testPosition.x - 64, testPosition.y), tiles))
//			{
//				edges.emplace_back(node, 4);
//				nodePresence[1] = true;
//			}
//		}
//		else
//		{
//			testPosition.x += 64.0f;
//			testPosition.y += 64.0f;
//			node = GetNodeAtLocation(testPosition, nodeMap);
//			if (node != nullptr)
//			{
//				if (CheckSpaceIsClear(sf::Vector2f(testPosition.x - 64, testPosition.y), tiles))
//				{
//					edges.emplace_back(node, 4);
//					nodePresence[5] = true;
//				}
//			}
//			else
//			{
//				testPosition.y += 64.0f;
//				node = GetNodeAtLocation(testPosition, nodeMap);
//				if (node != nullptr)
//				{
//					if (CheckSpaceIsClear(sf::Vector2f(testPosition.x - 64, testPosition.y), tiles))
//					{
//						edges.emplace_back(node, 3);
//						nodePresence[9] = true;
//					}
//				}
//				else
//				{
//					testPosition.y += 64.0f;
//					node = GetNodeAtLocation(testPosition, nodeMap);
//					if (node != nullptr)
//					{
//						if (CheckSpaceIsClear(sf::Vector2f(testPosition.x - 64, testPosition.y), tiles))
//						{
//							edges.emplace_back(node, 4);
//							nodePresence[13] = true;
//						}
//					}
//				}
//			}
//
//		}
//	}
//
//	testPosition = GetNodeLocation();
//
//	//Test for a left jump node;
//	testPosition.x -= 64.0f;
//	testPosition.y -= 64.0f;
//	node = GetNodeAtLocation(testPosition, nodeMap);
//	if (node != nullptr)
//	{
//		if (CheckSpaceIsClear(sf::Vector2f(testPosition.x + 64, testPosition.y), tiles))
//		{
//			edges.emplace_back(node, 2);
//			nodePresence[3] = true;
//		}
//	}
//	else if(CheckSpaceIsClear(sf::Vector2f(GetNodeLocation().x, GetNodeLocation().y - 64), tiles))
//	{
//		testPosition.y -= 64.0f;
//		node = GetNodeAtLocation(testPosition, nodeMap);
//		if (node != nullptr)
//		{
//			if (CheckSpaceIsClear(sf::Vector2f(testPosition.x + 64, testPosition.y), tiles))
//			{
//				edges.emplace_back(node, 4);
//				nodePresence[0] = true;
//			}
//		}
//		else
//		{
//			testPosition.x -= 64.0f;
//			testPosition.y += 64.0f;
//			node = GetNodeAtLocation(testPosition, nodeMap);
//			if (node != nullptr)
//			{
//				if (CheckSpaceIsClear(sf::Vector2f(testPosition.x + 64, testPosition.y), tiles))
//				{
//					edges.emplace_back(node, 4);
//					nodePresence[2] = true;
//				}
//			}
//			else
//			{
//				testPosition.y += 64.0f;
//				node = GetNodeAtLocation(testPosition, nodeMap);
//				if (node != nullptr)
//				{
//					if (CheckSpaceIsClear(sf::Vector2f(testPosition.x + 64, testPosition.y), tiles))
//					{
//						edges.emplace_back(node, 3);
//						nodePresence[6] = true;
//					}
//				}
//				else
//				{
//					testPosition.y += 64.0f;
//					node = GetNodeAtLocation(testPosition, nodeMap);
//					if (node != nullptr)
//					{
//						if (CheckSpaceIsClear(sf::Vector2f(testPosition.x + 64, testPosition.y), tiles))
//						{
//							edges.emplace_back(node, 4);
//							nodePresence[10] = true;
//						}
//					}
//				}
//			}
//
//		}
//	}
//}

bool Node::CheckSpaceIsClear(sf::Vector2f pos, std::vector<Tile> tiles)
{
	int xGridPos = (static_cast<int>(pos.x) % SCREEN_WIDTH) / 64;
	int yGridPos = (static_cast<int>(pos.y) % SCREEN_HEIGHT) / 64;
	if (yGridPos < 0)
		yGridPos += 10;

	if (tiles[xGridPos + (15 * yGridPos)].collisionTag == CollisionTag::level)
		return false;

	return true;
}

void Node::SetupNode(std::vector<Node*>* inNodeList, std::vector<Tile> inTiles)
{
}