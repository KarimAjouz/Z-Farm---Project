#include "AlarmPig.h"

#include "Definitions.h"


AlarmPig::AlarmPig(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos) :
	_data(data),
	_animSys(&sprite, _data)
{
	InitAnimations();

	worldRef = world;
	sprite.setPosition(pos);
	sprite.setScale(sf::Vector2f(2.0f, 2.0f));
	sprite.setOrigin(sf::Vector2f(20, 15));
	
	hitbox = sf::RectangleShape(sf::Vector2f(12, 12));
	hitbox.setOrigin(6, 6);
	hitbox.setPosition(sprite.getPosition());
	hitbox.setScale(2.0f, 2.0f);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Blue);
	hitbox.setOutlineThickness(1.0f);

	InitPhysics(pos);

	_animSys.SetAnimation("PigIdle");
	_animSys.Play();
}

AlarmPig::~AlarmPig()
{
}

void AlarmPig::Update(float dT)
{
	UpdateState();
	UpdateAnimations();

	_animSys.Update(dT);

	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	hitbox.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 12));

}

void AlarmPig::Draw()
{
	_data->window.draw(sprite);
	//_data->window.draw(line);
}

void AlarmPig::UpdateState()
{
	switch (_state)
	{
	case State::idle:
		if (CanSeePlayer())
			_state = State::alarmed;
		break;
	case State::hit:
		if (_animSys.GetCurrentAnim() == "PigHit" && _animSys.Complete())
			DestroyPig();
		break;
	case State::alarmed:

		break;
	}
}

void AlarmPig::UpdateAnimations()
{
	switch (_state)
	{
		case State::idle:
			if (_animSys.GetCurrentAnim() != "PigIdle")
			{
				_animSys.SetAnimation("PigIdle");
				_animSys.Play();
			}
			break;
		case State::hit:
			if (_animSys.GetCurrentAnim() != "PigHit")
			{
				_animSys.SetAnimation("PigHit");
				_animSys.Play();
			}
			break;
		case State::alarmed:
			if (_animSys.GetCurrentAnim() != "PigAlarm")
			{
				_animSys.SetAnimation("PigAlarm");
				_animSys.Play();
			}
			break;
	}

}

void AlarmPig::InitAnimations()
{
	sf::IntRect frameRect = sf::IntRect(0, 0, 34, 28);
	sf::Vector2f frameOrigin = sf::Vector2f(20, 12);
	_animSys.AddAnimation("PigIdle", PIG_IDLE, 1.1f, true, frameRect, frameOrigin);
	_animSys.AddAnimation("PigHit", PIG_DEATH, 1.1f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("PigAlarm", PIG_ALARM, 0.6f, true, frameRect, frameOrigin);
}

void AlarmPig::InitPhysics(sf::Vector2f pos)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	bodyDef.type = b2_dynamicBody;
	body = worldRef->CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape polygonShape;
	b2CircleShape circleShape;
	circleShape.m_radius = 17 / SCALE;
	circleShape.m_p = b2Vec2(0, 17 / 2 / SCALE);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;

	myFixtureDef.friction = 0.4f;
	myFixtureDef.restitution = 0.5f;
	myFixtureDef.shape = &circleShape;
	b2Fixture* pigFixture = body->CreateFixture(&myFixtureDef);
	pigFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemy);
}

void AlarmPig::DestroyPig()
{
	//_worldRef->DestroyBody(body);
	isMarked = true;
}

void AlarmPig::Hit()
{
	if (_state != State::hit)
	{
		_state = State::hit;
	}
}

void AlarmPig::Hit(sf::Vector2f playerPos)
{
	if (_state != State::hit)
	{
		if (playerPos.x < sprite.getPosition().x)
		{
			if (isFlipped)
				FlipSprite();

			body->ApplyLinearImpulseToCenter(b2Vec2(3.0f, -3.0f), true);
		}

		if (playerPos.x > sprite.getPosition().x)
		{
			if (!isFlipped)
				FlipSprite();

			body->ApplyLinearImpulseToCenter(b2Vec2(-3.0f, -3.0f), true);
		}

		_state = State::hit;
	}
}

bool AlarmPig::CanSeePlayer()
{
	bool playerVisible = false;

	b2RayCastInput input;
	input.p1 = b2Vec2(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);

	if (!isFlipped)
		input.p2 = b2Vec2((sprite.getPosition().x - 16.0f) / SCALE, sprite.getPosition().y / SCALE);
	else if (isFlipped)
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

				if(static_cast<int>(f->GetUserData().pointer) == static_cast<int>(CollisionTag::player))
					playerVisible = true;
			}
		}
	}

	b2Vec2 intersectionPoint = input.p1 + closestFraction * (input.p2 - input.p1);

	//line.setPosition(intersectionPoint.x * SCALE, intersectionPoint.y * SCALE);
	//line.setSize(sf::Vector2f((input.p1.x - intersectionPoint.x) * SCALE, 2.0f));


	return playerVisible;
}