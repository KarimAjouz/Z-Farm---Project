#include "Baldy.h"
#include "Definitions.h"
#include "Utilities.h"

#include <queue>
#include <unordered_set>
#include <iostream>
#include <algorithm>


Baldy::Baldy(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos, Room* myRoom) :
	_data(data),
	_animSys(&sprite, _data),
	_myRoom(myRoom)
{
	worldRef = world;

	sprite.setPosition(pos);
	sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	sprite.setOrigin(sf::Vector2f(30, 34));

	hitbox = sf::RectangleShape(sf::Vector2f(30, 54));
	hitbox.setOrigin(15, 27);
	hitbox.setPosition(sprite.getPosition());
	hitbox.setScale(1.0, 1.0f);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Blue);
	hitbox.setOutlineThickness(1.0f);

	InitAnimations();
	InitPhysics(pos);

	_state = State::moving;
	_animSys.SetAnimation("BaldyIdle");
	_animSys.Play();

	targetNodeCircle.setFillColor(sf::Color::Magenta);
	targetNodeCircle.setRadius(5.0f);

}

Baldy::~Baldy()
{
}

void Baldy::Update(float dT)
{
	UpdateState();
	UpdateAnimations();

	_animSys.Update(dT);

	sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	hitbox.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
		Repath();
}

void Baldy::Draw()
{
	_data->window.draw(sprite);
	//_data->window.draw(hitbox);

	if (_path.size() > 1)
	{
		for (int i = 0; i < _path.size() - 1; i++)
		{
			sf::Vertex line[2];
			line[0].position = _path[i]->GetNodeLocation();
			line[0].color = sf::Color::Red;
			line[1].position = _path[i + 1]->GetNodeLocation();
			line[1].color = sf::Color::Red;

			_data->window.draw(line, 2, sf::Lines);
		}
	}
	_data->window.draw(targetNodeCircle);
}

void Baldy::Hit()
{
}

void Baldy::Hit(sf::Vector2f playerPos)
{
}

void Baldy::Repath()
{
	_path = ZEngine::Utilities::PathFind(_targetPosition, &sprite, _myRoom);
	_state = State::moving;
}

void Baldy::UpdateAnimations()
{
	switch (_state)
	{
		case State::idle:
			if (_animSys.GetCurrentAnim() != "BaldyIdle")
			{
				_animSys.SetAnimation("BaldyIdle");
				_animSys.Play();
			}
			break;
		case State::moving:
			if (_animSys.GetCurrentAnim() != "BaldyRun")
			{
				_animSys.SetAnimation("BaldyRun");
				_animSys.Play();
			}
			break;
	}
}

void Baldy::UpdateState()
{
	switch (_state)
	{
		case State::moving:
			if (SeekTarget())
				_state = State::idle;
			break;
	}

}

void Baldy::InitAnimations()
{
	sf::IntRect frameRect = sf::IntRect(0, 0, 63, 67);
	sf::Vector2f frameOrigin = sf::Vector2f(30, 34);
	_animSys.AddAnimation("BaldyIdle", BALDY_IDLE, 3.4f, true, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyRun", BALDY_RUN, 1.4f, true, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyPreJump", BALDY_PREJUMP, 0.1f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyJump", BALDY_JUMP, 0.4f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyFall", BALDY_FALL, 0.2f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyLand", BALDY_LAND, 0.3f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyHit", BALDY_HIT, 1.0f, false, frameRect, frameOrigin);
	_animSys.AddAnimation("BaldyDead", BALDY_DEAD, 0.4f, true, frameRect, frameOrigin);
}

void Baldy::InitPhysics(sf::Vector2f pos)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
	body = worldRef->CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	polygonShape.SetAsBox(15 / SCALE, 31 / SCALE);

	myFixtureDef.friction = 0.4f;
	myFixtureDef.restitution = 0.2f;
	myFixtureDef.shape = &polygonShape;
	b2Fixture* baldyFixture = body->CreateFixture(&myFixtureDef);
	baldyFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemy);

	polygonShape.SetAsBox(10 / SCALE, 10 / SCALE, b2Vec2(0, (31.0f * abs(sprite.getScale().y)) / SCALE), 0);
	myFixtureDef.isSensor = true;
	myFixtureDef.shape = &polygonShape;
	b2Fixture* footSensorFixture = body->CreateFixture(&myFixtureDef);
	footSensorFixture->GetUserData().pointer = static_cast<int>(CollisionTag::enemyFoot);

}

bool Baldy::CanSeePlayer()
{
	return false;
}




bool Baldy::SeekTarget()
{
	Node* nearestNode = ZEngine::Utilities::GetNearestNode(sprite.getPosition(), _myRoom);
	if (_path.size() > 0)
	{
		if (nearestNode == _path[_path.size() - 1])
			return true;
	}
	else
		return false;
	

	//If the nearest node is the top node in the path, remove it from the path.
	if (nearestNode == _path[0])
		_path.erase(_path.begin());

	//Get a pointer to the next node (the top node in the path)
	Node* targetNode = _path[0];

	targetNodeCircle.setPosition(targetNode->GetNodeLocation());


	//Move in the x-direction towards the node.
	if (targetNode->GetNodeLocation().x > nearestNode->GetNodeLocation().x)
		Move(1);
	else if (targetNode->GetNodeLocation().x < nearestNode->GetNodeLocation().x)
		Move(-1);

	//Decide if we need to jump.
	if (targetNode->GetNodeLocation().y < nearestNode->GetNodeLocation().y)
	{
		float jumpForce = 6.0f;
		Jump(jumpForce);
	}
	
	return false;
}

void Baldy::Move(int dir)
{
	b2Vec2 vel = body->GetLinearVelocity();

	if (dir == -1)
		_desiredVelocity = b2Max(vel.x - 0.3f, -4.0f);
	else if (dir == 1)
		_desiredVelocity = b2Min(vel.x + 0.3f, 4.0f);

	float velChange = _desiredVelocity - vel.x;
	float impulse = body->GetMass() * velChange; //disregard time factor

	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}

void Baldy::Jump(float force)
{
	if (!_jumping && footContacts > 0 && _jumpTimeout < 0)
	{
		float impulse = body->GetMass() * force;
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.0f));
		body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true);
		_jumpTimeout = 15;
		//_state = State::jumping;
	}
	else if (_jumpTimeout >= 0)
		_jumpTimeout--;
}
