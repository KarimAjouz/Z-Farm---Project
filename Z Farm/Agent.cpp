#include "Agent.h"



Agent::Agent() :
	isFlipped(false),
	type(Type::UNDEFINED)
{
}


Agent::~Agent()
{
	if(worldRef)
		worldRef->DestroyBody(body);

}

void Agent::FlipSprite()
{
	sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);
	isFlipped = !isFlipped;
}