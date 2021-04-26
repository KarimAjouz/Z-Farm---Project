#include "Baldy.h"
#include "Definitions.h"

#include <queue>
#include <unordered_set>
#include <iostream>


Baldy::Baldy(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos, Room* myRoom) :
	_data(data),
	_animSys(&sprite, _data),
	_myRoom(myRoom)
{
	worldRef = world;

	sprite.setPosition(pos);
	sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	sprite.setOrigin(sf::Vector2f(30, 34));

	hitbox = sf::RectangleShape(sf::Vector2f(30, 54));
	hitbox.setOrigin(15, 27);
	hitbox.setPosition(sprite.getPosition());
	hitbox.setScale(1.0, 1.0f);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Blue);
	hitbox.setOutlineThickness(1.0f);

	InitAnimations();
	InitPhysics(pos);

	_animSys.SetAnimation("BaldyIdle");
	_animSys.Play();

	Repath();
}

Baldy::~Baldy()
{
}

void Baldy::Update(float dT)
{
	UpdateState();
	UpdateAnimations();

	_animSys.Update(dT);

	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	hitbox.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
		Repath();
}

void Baldy::Draw()
{
	_data->window.draw(sprite);
	_data->window.draw(hitbox);

	for (int i = 0; i < _path.size() - 1; i++)
	{
		sf::Vertex line[2];
		line[0].position = _path[i]->GetNodeLocation();
		line[0].color = sf::Color::Red;
		line[1].position = _path[i + 1]->GetNodeLocation();
		line[1].color = sf::Color::Red;

		_data->window.draw(line, 2, sf::Lines);
	}
}

void Baldy::Hit()
{
}

void Baldy::Hit(sf::Vector2f playerPos)
{
}

void Baldy::Repath()
{
	_path = PathFind(_targetPosition);
}

void Baldy::UpdateAnimations()
{
}

void Baldy::UpdateState()
{
	


}

void Baldy::InitAnimations()
{
	sf::IntRect frameRect = sf::IntRect(0, 0, 63, 67);
	sf::Vector2f frameOrigin = sf::Vector2f(30, 34);
	_animSys.AddAnimation("BaldyIdle", BALDY_IDLE, 3.4f, true, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyRun", BALDY_RUN, 1.4f, true, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyPreJump", BALDY_PREJUMP, 0.1f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyJump", BALDY_JUMP, 0.4f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyFall", BALDY_FALL, 0.2f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyLand", BALDY_LAND, 0.3f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyHit", BALDY_HIT, 1.0f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyDead", BALDY_DEAD, 0.4f, true, frameRect, frameOrigin);
}

void Baldy::InitPhysics(sf::Vector2f pos)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	bodyDef.type = b2_dynamicBody;
	body = worldRef->CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	polygonShape.SetAsBox(15 / SCALE, 31 / SCALE);

	myFixtureDef.friction = 0.4f;
	myFixtureDef.restitution = 0.2f;
	myFixtureDef.shape = &polygonShape;
	b2Fixture* baldyFixture = body->CreateFixture(&myFixtureDef);
	baldyFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemy);

}

bool Baldy::CanSeePlayer()
{
	return false;
}


std::vector<Node*> Baldy::PathFind(sf::Vector2f goal)
{
	std::vector<Node*> openSet;
	std::vector<Node*> returnSet = std::vector<Node*>();
	std::map<Node*, Node*> cameFrom;

	Node* startNode = GetNearestNode(sprite.getPosition());
	Node* goalNode = GetNearestNode(goal);

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
			returnSet.push_back(currentNode);
			return returnSet;
		}

		openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));

		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node::Edge neighbour = currentNode->edges[i];
			float tentative_gScore = gScore[currentNode].i + neighbour.cost;
			float neighbourScore = gScore[neighbour.node].i;

			if (tentative_gScore < gScore[neighbour.node].i)
			{
				cameFrom[neighbour.node] = currentNode;
				returnSet.push_back(currentNode);
				gScore[neighbour.node].i = tentative_gScore;
				fScore[neighbour.node].i = gScore[neighbour.node].i + GenerateHeuristic(neighbour.node->GetNodeLocation(), goalNode->GetNodeLocation());
				if (std::find(openSet.begin(), openSet.end(), neighbour.node) == openSet.end()) 
				{
					openSet.push_back(neighbour.node);
				}
			}
		}
	}
	return returnSet;
}

/// <summary>
/// Gets the nearest node to a location.
/// </summary>
/// <param name="pos"> The location to grab the nearest node to. </param>
/// <returns> A pointer to the node nearest to position 'pos'. </returns>
Node* Baldy::GetNearestNode(sf::Vector2f pos)
{
	//Init a node pointer and a temp to hold the distance to the neared node (keeping it squared to minimise sqrt calls)
	/*
	NOTE: I initialise distSquared as -1 because the loop will never set it to be negative.
		  This way, in the loop, I can guarantee that the first run will return a node from the level.
		  If there is no node, I can just return a nullptr and do a check whenever I call this function.
	*/
	Node* nearestNode = nullptr;
	float distSquared = -1;

	//Loop through the navMap...
	for (int i = 0; i < _myRoom->navMap.size(); i++)
	{
		//Set some temp variables to calculate the distance squared.
		sf::Vector2f tempDist = _myRoom->navMap[i].GetNodeLocation() - pos;
		float nodeDistSquared = (tempDist.x * tempDist.x) + (tempDist.y * tempDist.y);

		//If the distance squared is -1 (This is the first run of the loop), just grab this node.
		if (distSquared == -1)
		{
			distSquared = nodeDistSquared;
			nearestNode = &_myRoom->navMap[i];
		}

		//If the distance to the next node is less than the distance to the current nearest node, set the nearest node to this node.
		if (nodeDistSquared < distSquared)
		{
			distSquared = nodeDistSquared;
			nearestNode = &_myRoom->navMap[i];
		}
	}

	//Returns the nearest Node.
	return nearestNode;
}

/// <summary>
/// Generates a heuristic for the pathfinding algorithm from two position vectors.
/// </summary>
/// <param name="a"> The first position vector. </param>
/// <param name="b"> The second position vector. </param>
/// <returns></returns>
float Baldy::GenerateHeuristic(sf::Vector2f a, sf::Vector2f b)
{
	return (std::abs(a.x - b.x) / 64) + (std::abs(a.y - b.y) / 64);
}