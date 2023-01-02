#include "Utilities.h"

#include <math.h>
#include <time.h>
#include <iostream>
#include <cstdlib>

namespace ZEngine
{
	Utilities::Utilities()
	{
		std::srand((unsigned)std::time(0));
	}

	Utilities::~Utilities()
	{
	}

	sf::Vector2f Utilities::NormaliseVector(sf::Vector2f in)
	{
		if (in.x == 0.0f && in.y == 0.0f)
			return in;

		float mag = GetVectorMagnitude(in);
		return sf::Vector2f(in.x / mag, in.y / mag);
	}

	float Utilities::GetVectorMagnitude(sf::Vector2f in)
	{
		 return std::sqrt((in.x * in.x) + (in.y * in.y));
	}

	float Utilities::GetVectorMagnitudeSquared(sf::Vector2f in)
	{
		return (in.x * in.x) + (in.y * in.y);
	}

	float Utilities::Random()
	{
		float r = static_cast<float>(rand());
		r = r / RAND_MAX;
		return r;
	}

	float Utilities::Random(float max)
	{
		float r = static_cast<float>(rand());
		r = (r / RAND_MAX) * max;
		return r;
	}

	float Utilities::Random(float min, float max)
	{
		float r = static_cast<float>(rand());
		r = ((r / RAND_MAX) * (max - min)) + min;
		return r;
	}

	float Utilities::DistSq(sf::Sprite a, sf::Sprite b)
	{
		return ((a.getPosition().x - b.getPosition().x) * (a.getPosition().x - b.getPosition().x)) + ((a.getPosition().y - b.getPosition().y) * (a.getPosition().y - b.getPosition().y));
	}

	float Utilities::MinDist(sf::Sprite a, sf::Sprite b)
	{
		return (a.getLocalBounds().width * a.getScale().x / 2) + (b.getLocalBounds().width * b.getScale().x / 2);
	}

	bool Utilities::CircleCollider(sf::Sprite a, sf::Sprite b)
	{
		float distSq = DistSq(a, b);

		float minDistSq = MinDist(a, b);

		minDistSq = minDistSq * minDistSq;

		if (distSq < minDistSq)
			return true;
		else
			return false;
	}

	bool Utilities::RectCollider(sf::FloatRect a, sf::FloatRect b)
	{
		if (a.intersects(b))
			return true;
		
		return false;
	}

	void Utilities::SeedRandom()
	{
		srand(time(0));
	}

	float Utilities::Lerp(float cur, float target, float inc)
	{
		float ret = cur;
		ret += ((target - cur) * inc);
		return ret;
	}

	sf::Vector2f Utilities::Lerp(sf::Vector2f cur, sf::Vector2f target, float inc)
	{
		sf::Vector2f ret = cur;
		ret += ((target - cur) * inc);
		return ret;
	}

	/// <summary>
/// Gets the nearest node to a location.
/// </summary>
/// <param name="pos"> The location to grab the nearest node to. </param>
/// <returns> A pointer to the node nearest to position 'pos'. </returns>
	Node* Utilities::GetNearestNode(sf::Vector2f pos, Room* room)
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
		for (int i = 0; i < room->GetNavMap()->GetMap().size(); i++)
		{
			for (int j = 0; j < room->GetNavMap()->GetMap()[i].nodes.size(); j++)
			{
				//Set some temp variables to calculate the distance squared.
				sf::Vector2f tempDist = room->GetNavMap()->GetMap()[i].nodes[j]->GetNodeLocation() - pos;
				float nodeDistSquared = (tempDist.x * tempDist.x) + (tempDist.y * tempDist.y);

				//If the distance squared is -1 (This is the first run of the loop), just grab this node.
				if (distSquared == -1)
				{
					distSquared = nodeDistSquared;
					nearestNode = room->GetNavMap()->GetMap()[i].nodes[j];
				}

				//If the distance to the next node is less than the distance to the current nearest node, set the nearest node to this node.
				if (nodeDistSquared < distSquared)
				{
					distSquared = nodeDistSquared;
					nearestNode = room->GetNavMap()->GetMap()[i].nodes[j];

				}
			}
		}

		//Returns the nearest Node.
		return nearestNode;
	}
}