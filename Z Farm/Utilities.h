#pragma once
#include <SFML/Graphics.hpp>

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

		static bool CircleCollider(sf::Sprite a, sf::Sprite b);

	};

}