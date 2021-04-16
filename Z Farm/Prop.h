#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "box2d.h"

class Prop
{
public:
	Prop();
	~Prop();

	virtual void Update(float dT) = 0;
	virtual void Draw() = 0;

	enum class Type
	{
		spike
	};

	Type type = Type::spike;

	sf::Sprite sprite;
	sf::RectangleShape hitBox;


	virtual void InitPhysics() = 0;

private:
};

