#include "AlarmPig.h"

#include "Definitions.h"


AlarmPig::AlarmPig(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f pos) :
	_data(data),
	_worldRef(worldRef),
	_animSys(&sprite, _data)
{
	InitAnimations();

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

	sprite.setPosition(_body->GetPosition().x * SCALE, _body->GetPosition().y * SCALE);
	hitbox.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 12));



}

void AlarmPig::Draw()
{
	_data->window.draw(sprite);

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
	_body = _worldRef->CreateBody(&bodyDef);
	_body->SetFixedRotation(true);

	b2PolygonShape polygonShape;
	b2CircleShape circleShape;
	circleShape.m_radius = 17 / SCALE;
	circleShape.m_p = b2Vec2(0, 17 / 2 / SCALE);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;

	myFixtureDef.friction = 0.4f;
	myFixtureDef.restitution = 0.5f;
	myFixtureDef.shape = &circleShape;
	b2Fixture* playerFixture = _body->CreateFixture(&myFixtureDef);
	playerFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemy);
}

void AlarmPig::DestroyPig()
{
	isMarked = true;
	_worldRef->DestroyBody(_body);
}

void AlarmPig::Hit()
{
	if(_state != State::hit)
		_state = State::hit;
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

	float closestFraction = 320.0f / SCALE;
	input.maxFraction = closestFraction;

	for (b2Body* b = _worldRef->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			b2RayCastOutput output;

			if (!f->RayCast(&output, input, 0))
				continue;

			if (output.fraction < closestFraction && static_cast<int>(f->GetUserData().pointer) == static_cast<int>(CollisionTag::player))
			{
				closestFraction = output.fraction;
				intersectionNormal = output.normal;

				playerVisible = true;
			}
		}
	}

	b2Vec2 intersectionPoint = input.p1 + closestFraction * (input.p2 - input.p1);


	return playerVisible;
}