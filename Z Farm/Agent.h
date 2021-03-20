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

	sf::Sprite sprite;
	bool isFlipped;
private:
};

