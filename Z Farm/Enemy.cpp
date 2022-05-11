#include "Enemy.h"
#include "Definitions.h"

Enemy::Enemy(ZEngine::GameDataRef data, b2World* world) :
	alertBubble(data),
	questionTimer(1.0f, false),
	worldRef(world)
{
	AssignPlayerBody();
}

Enemy::~Enemy()
{

}

bool Enemy::CanSeePlayer()
{
	bool playerVisible = false;

	b2RayCastInput input;
	input.p1 = b2Vec2(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);

	if (isFlipped)
		input.p2 = b2Vec2((sprite.getPosition().x - 16.0f) / SCALE, sprite.getPosition().y / SCALE);
	else if (!isFlipped)
		input.p2 = b2Vec2((sprite.getPosition().x + 16.0f) / SCALE, sprite.getPosition().y / SCALE);

	b2Vec2 intersectionNormal = b2Vec2(0.0f, 0.0f);

	float closestFraction = SCREEN_WIDTH * 2 / SCALE;
	input.maxFraction = closestFraction;

	for (b2Body* b = worldRef->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			b2RayCastOutput output;

			if (!f->RayCast(&output, input, 0))
				continue;

			if (output.fraction < closestFraction)
			{
				closestFraction = output.fraction;
				intersectionNormal = output.normal;

				if (static_cast<int>(f->GetUserData().pointer) == static_cast<int>(CollisionTag::player))
					playerVisible = true;
			}
		}
	}

	b2Vec2 intersectionPoint = input.p1 + closestFraction * (input.p2 - input.p1);
	return playerVisible;
}

bool Enemy::CanSeePlayer(sf::Vector2f* lastSeenPosRef)
{
	bool playerVisible = false;

	b2RayCastInput input;
	input.p1 = b2Vec2(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);

	if (isFlipped)
		input.p2 = b2Vec2((sprite.getPosition().x - 16.0f) / SCALE, sprite.getPosition().y / SCALE);
	else if (!isFlipped)
		input.p2 = b2Vec2((sprite.getPosition().x + 16.0f) / SCALE, sprite.getPosition().y / SCALE);

	b2Vec2 intersectionNormal = b2Vec2(0.0f, 0.0f);

	float closestFraction = SCREEN_WIDTH * 2 / SCALE;
	input.maxFraction = closestFraction;

	for (b2Body* b = worldRef->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			b2RayCastOutput output;

			if (!f->RayCast(&output, input, 0))
				continue;

			if (output.fraction < closestFraction)
			{
				closestFraction = output.fraction;
				intersectionNormal = output.normal;

				if (static_cast<int>(f->GetUserData().pointer) == static_cast<int>(CollisionTag::player))
					playerVisible = true;
			}
		}
	}

	b2Vec2 intersectionPoint = input.p1 + closestFraction * (input.p2 - input.p1);
	*lastSeenPosRef = sf::Vector2f(intersectionPoint.x * SCALE, intersectionPoint.y * SCALE);
	return playerVisible;
}

void Enemy::AssignPlayerBody()
{
	for (b2Body* b = worldRef->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			if (static_cast<int>(f->GetUserData().pointer) == static_cast<int>(CollisionTag::player))
				playerBody = f->GetBody();
		}
	}
}
