#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>

class Agent
{
public:
	Agent();
	~Agent();

	virtual void Update(float dT) = 0;
	virtual void Draw() = 0;


	void FlipSprite();
	
	virtual void Hit() = 0;
	virtual void Hit(sf::Vector2f playerPos) = 0;

	sf::Sprite sprite;
	sf::RectangleShape hitbox;
	bool isFlipped;
	bool isMarked = false;

	void MarkForDeath() { isMarked = true; };

	enum class Type
	{
		alarmPig
	};

	Type type = Type::alarmPig;

	b2Body* body = nullptr;

private:
};

