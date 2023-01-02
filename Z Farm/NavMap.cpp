#include "NavMap.h"
#include "Utilities.h"

#include <iostream>



NavMap::NavMap()
{

}

NavMap::~NavMap()
{

}

void NavMap::GenerateNavMap(std::vector<Tile>* inTiles)
{
	ClearMap();

	int currentPlatformIndex = 0;
	bool platformStarted = false;
	int tileSize = TILE_SCALE * TILE_SIZE;

	int rowLength = SCREEN_WIDTH / tileSize;

	for (int i = 0; i < inTiles->size() - rowLength; i++)
	{
		int tileX = i % rowLength;
		int tileY = i / rowLength;
		Node tempNode = Node(sf::Vector2f(tileX * tileSize + (tileSize / 2), tileY * tileSize + (5)));
		tempNode.platformIndex = currentPlatformIndex;

		int rightTileIndex = i + 1;
		int leftTileIndex = i - 1;
		int lowerTileIndex = i + rowLength;
		int lowerRightTileIndex = rightTileIndex + rowLength;

		if (!platformStarted)
		{
			if (inTiles->at(i).collisionTag == CollisionTag::background && inTiles->at(lowerTileIndex).collisionTag == CollisionTag::level)
			{
				tempNode.type = Node::Type::leftPlatform;
				tempNode.platformIndex = currentPlatformIndex;
				platformStarted = true;
			}
		}

		if (platformStarted)
		{
			if (tileX == rowLength - 1)
			{
				if (tempNode.type == Node::Type::leftPlatform)
				{
					tempNode.type = Node::Type::soloPlatform;
				}
				else
				{
					tempNode.type = Node::Type::rightPlatform;
				}

				platformStarted = false;
			}
			else
			{
				CollisionTag rightTileTag = inTiles->at(rightTileIndex).collisionTag;
				CollisionTag lowerRightTileTag = inTiles->at(lowerRightTileIndex).collisionTag;
				Node::Type lPlatType = Node::Type::leftPlatform;
				if (rightTileTag == CollisionTag::background &&
					lowerRightTileTag == CollisionTag::level &&
					tempNode.type != lPlatType)
				{
					tempNode.type = Node::Type::platform;
					tempNode.platformIndex = currentPlatformIndex;
				}

				if (lowerRightTileTag == CollisionTag::background ||
					rightTileTag == CollisionTag::level)
				{
					if (tempNode.type == Node::Type::leftPlatform)
					{
						tempNode.type = Node::Type::soloPlatform;
					}
					else
					{
						if (tempNode.type != Node::Type::rightPlatform)
						{
							tempNode.type = Node::Type::rightPlatform;
						}
					}

					platformStarted = false;
				}
			}
		}
		if (tempNode.type != Node::Type::none)
		{
			if (tempNode.platformIndex < _map.size())
			{
				_map[tempNode.platformIndex].nodes.push_back(new Node(tempNode.nodeArea.getPosition(), tempNode.platformIndex, tempNode.type));
			}
			else
			{
				Platform newPlatform = Platform::Platform();
				newPlatform.nodes.push_back(new Node(tempNode.nodeArea.getPosition(), tempNode.platformIndex, tempNode.type));
				_map.push_back(newPlatform);
			}

			if (tempNode.type == Node::Type::rightPlatform || tempNode.type == Node::Type::soloPlatform)
			{
				currentPlatformIndex++;
			}
		}
	}

	GenerateEdges(inTiles);
}

void NavMap::ClearMap()
{
	_map.clear();
}

void NavMap::GenerateEdges(std::vector<Tile>* inTiles)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].nodes.size(); j++)
		{
			int rPlatIndex = j + 1;
			Node* curNode = _map[i].nodes[j];
			if (curNode->type == Node::Type::leftPlatform || curNode->type == Node::Type::platform)
			{
				Node::Edge edge;
				edge.cost = 1;
				edge.destinationCoords = sf::Vector2f(curNode->nodeArea.getPosition());
				edge.type = Node::Edge::Type::walk;
				_map.at(i).nodes[rPlatIndex]->edges.push_back(edge);
			}

			int lPlatIndex = j - 1;
			if (curNode->type == Node::Type::rightPlatform || curNode->type == Node::Type::platform)
			{
				Node::Edge edge;
				edge.cost = 1;
				edge.destinationCoords = sf::Vector2f(curNode->nodeArea.getPosition());
				edge.type = Node::Edge::Type::walk;
				_map.at(i).nodes[lPlatIndex]->edges.push_back(edge);
			}

			//Drop Code Here

			if (curNode->type == Node::Type::leftPlatform || curNode->type == Node::Type::rightPlatform || curNode->type == Node::Type::soloPlatform)
			{
				int a = 0;
				int b = 0;
				bool skip = false;
				switch (curNode->type)
				{
				case Node::Type::leftPlatform:
					a = 0;
					b = 0;
					break;

				case Node::Type::rightPlatform:
					a = 1;
					b = 1;
					break;

				case Node::Type::soloPlatform:
					a = 0;
					b = 1;
					break;
				}

				sf::Vector2f testPos = curNode->nodeArea.getPosition();

				int xTile = testPos.x / (TILE_SIZE * TILE_SCALE);
				int yTile = testPos.y / (TILE_SIZE * TILE_SCALE);
				int rowLength = SCREEN_WIDTH / (TILE_SCALE * TILE_SIZE);

				int tile = (yTile * rowLength) + xTile;
				int testTile = tile - 1;

				if (a == 0)
				{
					testPos.x -= (TILE_SIZE * TILE_SCALE);

					if (xTile != 0 && inTiles->at(testTile).collisionTag != CollisionTag::level)
					{
						sf::Vector2f edgePos = CalculateDropEdgePos(testPos);
						if (!(edgePos.x < 0.0f))
						{
							Node::Edge edge;
							edge.cost = 2;
							edge.destinationCoords = sf::Vector2f(edgePos);
							edge.type = Node::Edge::Type::drop;

							Node* foundNode = GetNodeAtLocation(edge.destinationCoords);

							if (foundNode != nullptr)
							{
								_map[i].nodes[j]->platformsReached[foundNode->platformIndex].b = true;
								_map.at(i).nodes[j]->edges.push_back(edge);
							}
						}
					}
				}

				testPos = curNode->nodeArea.getPosition();
				if (b == 1)
				{
					testPos.x += (TILE_SIZE * TILE_SCALE);

					testTile = tile + 1;
					if (xTile != rowLength - 1 && inTiles->at(testTile).collisionTag != CollisionTag::level)
					{
						sf::Vector2f edgePos = CalculateDropEdgePos(testPos);
						if (!(edgePos.x < 0.0f))
						{
							Node::Edge edge;
							edge.cost = 2;
							edge.destinationCoords = sf::Vector2f(edgePos);
							edge.type = Node::Edge::Type::drop;

							Node* foundNode = GetNodeAtLocation(edge.destinationCoords);

							if (foundNode != nullptr)
							{
								_map[i].nodes[j]->platformsReached[foundNode->platformIndex].b = true;
								_map.at(i).nodes[j]->edges.push_back(edge);
							}
						}
					}
				}
			}

			//Jump Edges Code Here
			std::vector<std::vector<JumpTrajectory>> jumpTrajectoriesToValidate;

			if (curNode->type != Node::Type::none)
			{
				std::vector<JumpTrajectory> navpointTrajectories;

				sf::Vector2f jumpVelocity = sf::Vector2f(4.0f, -12.0f);

				for (int i = 1; i <= NAVIGATION_JUMP_HEIGHT_DIVISIONS; i++)
				{
					float jumpHeight = (jumpVelocity.y / NAVIGATION_JUMP_HEIGHT_DIVISIONS) * i;

					for (int j = 1; j <= NAVIGATION_JUMP_SPEED_DIVISIONS; j++)
					{
						float jumpSpeed = (jumpVelocity.x / NAVIGATION_JUMP_SPEED_DIVISIONS) * j;

						navpointTrajectories.push_back(JumpTrajectory(curNode->nodeArea.getPosition(), sf::Vector2f(jumpSpeed, jumpHeight) * SCALE));
						navpointTrajectories.push_back(JumpTrajectory(curNode->nodeArea.getPosition(), sf::Vector2f(-jumpSpeed, jumpHeight) * SCALE));
					}
				}
				jumpTrajectoriesToValidate.push_back(navpointTrajectories);

				for (JumpTrajectory testJump : jumpTrajectoriesToValidate[0])
				{
					sf::RectangleShape TestRect = sf::RectangleShape(sf::Vector2f(26, 50));
					TestRect.setOrigin(13, 25);

					bool clear = true;

					for (int testPointIndex = 1; testPointIndex < testJump.pointsArray.size(); testPointIndex++)
					{
						TestRect.setPosition(testJump.pointsArray[testPointIndex]);

						if (DoesRectCollideWithLevel(TestRect, inTiles, testJump, curNode, testPointIndex <= testJump.fallingPointIndex))
							clear = false;

						if (clear)
						{
							Node* validNode = GetNodeAtLocation(testJump.pointsArray[testPointIndex]);

							if (validNode != nullptr && curNode->platformIndex != validNode->platformIndex && !curNode->platformsReached[validNode->platformIndex].b)
							{
								Node::Edge edge;
								JumpTrajectory edgeTraj = testJump;
								edgeTraj.pointsArray.resize(testPointIndex);
								edge.cost = ZEngine::Utilities::GetVectorMagnitude(edgeTraj.startVel);
								edge.destinationCoords = sf::Vector2f(validNode->nodeArea.getPosition());
								edge.JumpTrajectory = edgeTraj;
								edge.type = Node::Edge::Type::jump;
								curNode->platformsReached[validNode->platformIndex].b = true;
								_map.at(i).nodes[j]->edges.push_back(edge);
							}
						}
						else
						{
							break;
						}
					}
				}
			}


		}
	}
}

sf::Vector2f NavMap::CalculateDropEdgePos(sf::Vector2f inPos)
{
	sf::Vector2f testPos = inPos;
	Node tempNode = Node(inPos);
	std::vector<Node*> nodesToTest = std::vector<Node*>();

	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map.at(i).nodes.size(); j++)
		{
			if (_map.at(i).nodes[j]->nodeArea.getPosition().x == testPos.x)
			{
				nodesToTest.push_back(_map.at(i).nodes[j]);
			}
		}
	}

	while (testPos.y < SCREEN_HEIGHT)
	{
		for (Node* n : nodesToTest)
		{
			if (n->nodeArea.getPosition().y == testPos.y)
			{
				return testPos;
			}
		}
		testPos.y += TILE_SIZE * TILE_SCALE;
	}

	return sf::Vector2f(-1.f, -1.f);
}

bool NavMap::DoesPointCollideWithLevel(sf::Vector2f InPos, std::vector<Tile>* InTiles, JumpTrajectory InJump, Node* InCurNode)
{
	sf::Vector2f testPoint = InPos;
	int testPointXTile = testPoint.x / (TILE_SIZE * TILE_SCALE);
	int testPointYTile = testPoint.y / (TILE_SIZE * TILE_SCALE);
	int rowLength = SCREEN_WIDTH / (TILE_SCALE * TILE_SIZE);
	int testTileIndex = (testPointYTile * rowLength) + testPointXTile;

	if (testTileIndex >= InTiles->size())
		return false;

	Tile testTile = InTiles->at(testTileIndex);

	if (testTile.collisionTag == CollisionTag::level)
	{
		return true;
	}

	return false;
}

bool NavMap::DoesRectCollideWithLevel(sf::RectangleShape InRect, std::vector<Tile>* InTiles, JumpTrajectory InJump, Node* InCurNode, bool inIsDirUp)
{
	sf::Vector2f testPoint = sf::Vector2f(InRect.getGlobalBounds().left, InRect.getGlobalBounds().top);
	
	if (DoesPointCollideWithLevel(testPoint, InTiles, InJump, InCurNode))
		return true;

	testPoint = sf::Vector2f(InRect.getGlobalBounds().left + InRect.getGlobalBounds().width, InRect.getGlobalBounds().top);

	if (DoesPointCollideWithLevel(testPoint, InTiles, InJump, InCurNode))
		return true;
	
	testPoint = sf::Vector2f(InRect.getGlobalBounds().left, InRect.getGlobalBounds().top + InRect.getGlobalBounds().height);

	if (DoesPointCollideWithLevel(testPoint, InTiles, InJump, InCurNode))
		return true;

	testPoint = sf::Vector2f(InRect.getGlobalBounds().left + InRect.getGlobalBounds().width, InRect.getGlobalBounds().top + InRect.getGlobalBounds().height);

	if (DoesPointCollideWithLevel(testPoint, InTiles, InJump, InCurNode))
		return true;

	return false;
}

Node* NavMap::GetNodeAtLocation(sf::Vector2f pos)
{
	int x = pos.x;
	int y = pos.y;

	sf::Vector2f testPos = sf::Vector2f(x - (x % (TILE_SIZE * TILE_SCALE)), y - (y % (TILE_SIZE * TILE_SCALE)));
	testPos.x += TILE_SCALE * TILE_SIZE / 2;
	testPos.y += TILE_SCALE * TILE_SIZE / 2;

	for (int i = 0; i < _map.size(); i++)
	{
		std::vector<Node*> platform = _map.at(i).nodes;

		for (Node* node : platform)
		{
			if (node->nodeArea.getGlobalBounds().contains(testPos))
				return node;
		}
	}
	return nullptr;
}

Node* NavMap::GetNodeColWithRect(sf::RectangleShape InRect)
{

	for (int i = 0; i < _map.size(); i++)
	{
		std::vector<Node*> platform = _map.at(i).nodes;

		for (Node* node : platform)
		{
			if (InRect.getGlobalBounds().intersects(node->nodeArea.getGlobalBounds()))
				return node;
		}
	}
	return nullptr;
}