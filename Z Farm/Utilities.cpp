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

	bool Utilities::CircleCollider(sf::Sprite a, sf::Sprite b)
	{
		float distSq = ((a.getPosition().x - b.getPosition().x) * (a.getPosition().x - b.getPosition().x)) + ((a.getPosition().y - b.getPosition().y) * (a.getPosition().y - b.getPosition().y));

		float minDistSq = (a.getLocalBounds().width / 2) + (b.getLocalBounds().width / 2);
		minDistSq = minDistSq * minDistSq;

		if (distSq < minDistSq)
			return true;
		else
			return false;
	}
}