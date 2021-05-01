#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Room.h"

namespace ZEngine
{

	class Utilities
	{
	public:
		Utilities();
		~Utilities();

		static sf::Vector2f NormaliseVector(sf::Vector2f in);
		static float GetVectorMagnitude(sf::Vector2f in);
		
		static float Random();
		static float Random(float max);
		static float Random(float min, float max);

		static float DistSq(sf::Sprite a, sf::Sprite b);
		static float MinDist(sf::Sprite a, sf::Sprite b);

		static bool CircleCollider(sf::Sprite a, sf::Sprite b);

		static bool RectCollider(sf::FloatRect a, sf::FloatRect b);

		static bool CircleIntRectCollider(sf::Sprite circle, sf::IntRect rect);

		static void SeedRandom();

		static float Lerp(float cur, float target, float inc);
		static sf::Vector2f Lerp(sf::Vector2f cur, sf::Vector2f target, float inc);

		struct Score
		{
			float i = 999;
		};

		static Node* GetNearestNode(sf::Vector2f pos, Room* room);
		static std::vector<Node*> PathFind(sf::Vector2f goal, sf::Sprite* sprite, Room* room);
		static float GenerateHeuristic(sf::Vector2f a, sf::Vector2f b);
	};

}