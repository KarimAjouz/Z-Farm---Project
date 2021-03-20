#include "Agent.h"



Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::FlipSprite()
{
	sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);
	isFlipped = !isFlipped;
}