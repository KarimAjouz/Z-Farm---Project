#include "Obstacle.h"
#include "Definitions.h"


Obstacle::Obstacle()
{

}

Obstacle::~Obstacle()
{

}

void Obstacle::InitPhysics(sf::IntRect collisionBox, bool collider, bool isDynamic, b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((sprite.getPosition().x + collisionBox.left) / SCALE, (sprite.getPosition().y + collisionBox.top) / SCALE);

	if (isDynamic)
		bodyDef.type = b2_dynamicBody;
	else if (!isDynamic)
		bodyDef.type = b2_staticBody;

	body = world->CreateBody(&bodyDef);

	//Define, set, and add the primary fixture for the spike
	b2PolygonShape fixtureShape;
	fixtureShape.SetAsBox(collisionBox.width / SCALE, collisionBox.height / SCALE);
	b2FixtureDef myFixtureDef;

	if (collider)
	{
		myFixtureDef.density = 1.0f;
		myFixtureDef.isSensor = false;

		myFixtureDef.filter.categoryBits = _entityCategory::OBSTACLES;
		myFixtureDef.filter.maskBits =_entityCategory::LEVEL | _entityCategory::OBSTACLES | _entityCategory::AGENTS | _entityCategory::DAMAGE;
	}
	else
	{
		myFixtureDef.isSensor = true;
	}

	myFixtureDef.shape = &fixtureShape;
	b2Fixture* mainFixture = body->CreateFixture(&myFixtureDef);
}